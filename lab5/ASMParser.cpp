#include "ASMParser.h"

ASMParser::ASMParser(string filename)
  // Specify a text file containing MIPS assembly instructions. Function
  // checks syntactic correctness of file and creates a list of Instructions.
{
  Instruction i;
  myFormatCorrect = true;

  myAddress = 0x400000;

  // first iteration through file to find labels and their addresses
  ifstream in1;
  in1.open(filename.c_str());
  if(in1.bad()){
    myFormatCorrect = false;
  }
  else{
    string line;
    while(getline(in1, line)){
      // get rid of comments (could contain ":")
      string::size_type idx = line.find('#');
      if (idx != string::npos)
	      line = line.substr(0,idx);

      // check if the line is blank (don't want to increment myAddress)
      bool emptyLine = true;
      int size = line.length();
      for (int i = 0; i < size; i ++){
        if (!isWhitespace(line.at(i))){
          emptyLine = false;
          break;
        }
      }

      if(!emptyLine){
        // looking for ":" to find labels
        string::size_type idx1 = line.find(':');
        if (idx1 != string::npos) {
          string label = line.substr(0,idx1);
          // add label and its address to the symbolTable map
          symbolTable[label] = myAddress;
        }
        myAddress += 4;
      }
    }
  }

  myAddress = 0x400000; // looping through file again, start at address 0x400000

  ifstream in;
  in.open(filename.c_str());
  if(in.bad()){
    myFormatCorrect = false;
  }
  else{
    string line;
    while( getline(in, line)){
      string opcode("");
      string operand[80];
      int operand_count = 0;

      // locate the start of a comment and remove it
      string::size_type idx = line.find('#');
      if (idx != string::npos)
        line = line.substr(0,idx);

      // Remove any labels (using :'s not in comments). This should deal with
      // lines with just labels leaving all whitespace which is skipped.
      string::size_type idx1 = line.find(':');
      if (idx1 != string::npos) {
        line = line.substr(idx1 + 1);
      }

      // check if the line is blank (all whitespace)
      bool emptyLine = true;
      int size = line.length();
      for (int i = 0; i < size; i ++){
        if (!isWhitespace(line.at(i))){
          emptyLine = false;
          break;
        }
      }

      // only look at lines that have assembly code instructions
      if (!emptyLine){
        getTokens(line, opcode, operand, operand_count);

        if(opcode.length() == 0 && operand_count != 0){
          // No opcode but operands
          myFormatCorrect = false;
          break;
        }

        Opcode o = opcodes.getOpcode(opcode);
        if(o == UNDEFINED){
          // invalid opcode specified
          myFormatCorrect = false;
          break;
        }

        // string mipsInstrustion = opcode + "\t";
        // for (int i = 0; i < operand_count; i ++) {
        //   mipsInstrustion += operand[i] + " ";
        // }

        bool success = getOperands(i, o, operand, operand_count, line);
        if(!success){
          myFormatCorrect = false;
          break;
        }

        string encoding = encode(i);
        i.setEncoding(encoding);

        myInstructions.push_back(i);

        myAddress += 4;
      }
    }
  }

  myIndex = 0;
}


Instruction ASMParser::getNextInstruction()
  // Iterator that returns the next Instruction in the list of Instructions.
{
  if(myIndex < (int)(myInstructions.size())){
    myIndex++;
    return myInstructions[myIndex-1];
  }

  Instruction i;
  return i;

}

void ASMParser::getTokens(string line,
			       string &opcode,
			       string *operand,
			       int &numOperands)
  // Decomposes a line of assembly code into strings for the opcode field and operands,
  // checking for syntax errors and counting the number of operands.
  // Comments and labels are now assumed to be taken out in ASMParser method.
{
  int len = line.length();
  opcode = "";
  numOperands = 0;

  if (len == 0) return;
  int p = 0; // position in line

  // line.at(p) is whitespace or p >= len
  while (p < len && isWhitespace(line.at(p)))
	  p++;
  // opcode starts
  while (p < len && !isWhitespace(line.at(p)))
  {
	  opcode = opcode + line.at(p);
	  p++;
  }
  //    for(int i = 0; i < 3; i++){
  int i = 0;
  while(p < len){
    while ( p < len && isWhitespace(line.at(p)))
	    p++;

    // operand may start
    bool flag = false;
    while (p < len && !isWhitespace(line.at(p)))
	  {
	    if(line.at(p) != ','){
	      operand[i] = operand[i] + line.at(p);
	      flag = true;
	      p++;
	    }
	    else{
	      p++;
	      break;
	    }
	  }
    if(flag == true){
	    numOperands++;
    }
    i++;
  }


  string::size_type idx = operand[numOperands-1].find('(');
  string::size_type idx2 = operand[numOperands-1].find(')');

  if (idx == string::npos || idx2 == string::npos ||
	  ((idx2 - idx) < 2 )){ // no () found
  }
  else{ // split string
    string offset = operand[numOperands-1].substr(0,idx);
    string regStr = operand[numOperands-1].substr(idx+1, idx2-idx-1);

    operand[numOperands-1] = offset;
    operand[numOperands] = regStr;
    numOperands++;
  }



    // ignore anything after the whitespace after the operand
    // We could do a further look and generate an error message
    // but we'll save that for later.
    return;
}

bool ASMParser::isNumberString(string s)
  // Returns true if s represents a valid decimal integer
{
  int len = s.length();
  if (len == 0) return false;
  if ((isSign(s.at(0)) && len > 1) || isDigit(s.at(0)))
  {
	  // check remaining characters
	  for (int i=1; i < len; i++)
	  {
	    if (!isdigit(s.at(i))) return false;
	  }
	  return true;
  }
  // cout << "isNumberString returned false" << endl;
  // for jump instruction, label won't be a number...
  return false;
}


int ASMParser::cvtNumString2Number(string s)
  // Converts a string to an integer.  Assumes s is something like "-231" and produces -231
{
  if (!isNumberString(s))
  {
	  cerr << "Non-numberic string passed to cvtNumString2Number"
		  << endl;
	  return 0;
  }
  int k = 1;
  int val = 0;
  for (int i = s.length()-1; i>0; i--)
  {
	  char c = s.at(i);
	  val = val + k*((int)(c - '0'));
	  k = k*10;
  }
  if (isSign(s.at(0)))
  {
	  if (s.at(0) == '-') val = -1*val;
  }
  else
  {
	  val = val + k*((int)(s.at(0) - '0'));
  }
  return val;
}


bool ASMParser::getOperands(Instruction &i, Opcode o,
			    string *operand, int operand_count, string mips_inst)
  // Given an Opcode, a string representing the operands, and the number of operands,
  // breaks operands apart and stores fields into Instruction.
{

  if(operand_count != opcodes.numOperands(o))
    return false;

  int rs, rt, rd, imm;
  imm = 0;
  rs = rt = rd = NumRegisters;

  int rs_p = opcodes.RSposition(o);
  int rt_p = opcodes.RTposition(o);
  int rd_p = opcodes.RDposition(o);
  int imm_p = opcodes.IMMposition(o);

  if(rs_p != -1){
    rs = registers.getNum(operand[rs_p]);
    if(rs == NumRegisters)
      return false;
  }

  if(rt_p != -1){
    rt = registers.getNum(operand[rt_p]);
    if(rt == NumRegisters)
      return false;

  }

  if(rd_p != -1){
    rd = registers.getNum(operand[rd_p]);
    if(rd == NumRegisters)
      return false;

  }

  if(imm_p != -1){
    if(isNumberString(operand[imm_p])){  // does it have a numeric immediate field?
      imm = cvtNumString2Number(operand[imm_p]);
      if(((abs(imm) & 0xFFFF0000)<<1))  // too big a number to fit
	      return false;
    }
    else{
      if(opcodes.isIMMLabel(o)){  // Can the operand be a label?
	      // Assign the immediate field an address

        // is operand[imm_p] a hex value?
        if(operand[imm_p].substr(0, 2).compare("0x") == 0){
          std::stringstream ss;
          ss << std::hex << operand[imm_p].substr(2);
          ss >> imm;
        }
        else{ // operand[imm_p] must be a label
          imm = symbolTable[operand[imm_p]];
          if (imm == 0) // not a valid label
            return false;
        }

        // check if branch instruction and we need to calculate offset
        if(opcodes.getInstType(o) == ITYPE){ // must be branch instruction
          // cout << "offset = address - (PC + 4)" << endl;
          // cout << "\taddress = " << imm << endl;
          // cout << "\tPC + 4 = " << myAddress + 4 << endl;
          imm = imm - (myAddress + 4); // offset = address - (PC + 4)
          // cout << "\toffset = " << imm << endl;
        }
        // addresses and offsets are both divided by 4
        imm = imm / 4;

      }
      else  // There is an error
	      return false;
    }
  }

  i.setValues(o, rs, rt, rd, imm, mips_inst);

  return true;
}


string ASMParser::encode(Instruction i)
  // Given a valid instruction, returns a string representing the 32 bit MIPS binary encoding
  // of that instruction.
{
  Opcode op = i.getOpcode();
  InstType type = opcodes.getInstType(op);

  string str = "";
  str += opcodes.getOpcodeField(op);

  if(type == RTYPE) {
    str += encodeRTYPE(i, op);
  }
  else if (type == ITYPE){
    str += encodeITYPE(i, op);
  }
  else {
    str += encodeJTYPE(i, op);
  }

  return str;
}

string ASMParser::encodeRTYPE(Instruction i, Opcode op)
  // Given a valid RTYPE instruction, returns a string representing the last
  // 26 bits of the MIPS binary encoding of that instruction.
{
  string str = "";

  int RSpos = opcodes.RSposition(op);
  int RTpos = opcodes.RTposition(op);
  int RDpos = opcodes.RDposition(op);
  int Shamt = opcodes.IMMposition(op);

  if(RSpos >= 0){
    str += bitset<5>(i.getRS()).to_string();
  }
  else
    str += "00000";

  if(RTpos >= 0){
    str += bitset<5>(i.getRT()).to_string();
  }
  else
    str += "00000";

  if(RDpos >= 0){
    str += bitset<5>(i.getRD()).to_string();
  }
  else
    str += "00000";

  if(Shamt >= 0){
    str += bitset<5>(i.getImmediate()).to_string();
  }
  else
    str += "00000";

  str += opcodes.getFunctField(op);

  return str;
}

string ASMParser::encodeITYPE(Instruction i, Opcode op)
  // Given a valid ITYPE instruction, returns a string representing the last
  // 26 bits of the MIPS binary encoding of that instruction.
{
  string str = "";

  int RSpos = opcodes.RSposition(op);
  int RTpos = opcodes.RTposition(op);
  int IMMpos = opcodes.IMMposition(op);

  if(RSpos >= 0){
    str += bitset<5>(i.getRS()).to_string();
  }
  else
    str += "00000";

  if(RTpos >= 0){
    str += bitset<5>(i.getRT()).to_string();
  }
  else
    str += "00000";

  if(IMMpos >= 0){
    // cout << "immediate value: " << i.getImmediate() << endl;
    str += bitset<16>(i.getImmediate()).to_string();
    // cout << "converted to binary: " << bitset<16>(i.getImmediate()) << endl;
  }
  else  // shouldn't reach this case, but just in case
    str += "0000000000000000";

  return str;
}

string ASMParser::encodeJTYPE(Instruction i, Opcode op)
  // Given a valid JTYPE instruction, returns a string representing the last
  // 26 bits of the MIPS binary encoding of that instruction.
{
  string str = "";

  int IMMpos = opcodes.IMMposition(op);

  if(IMMpos >= 0){
    str += bitset<26>(i.getImmediate()).to_string();
  }
  else  // should never reach this, but just in case, defalts to 0x100000
    str += "00000100000000000000000000";

  return str;
}