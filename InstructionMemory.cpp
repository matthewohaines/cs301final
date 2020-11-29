#include "InstructionMemory.h"

InstructionMemory::InstructionMemory(string Program_input, bool debug_mode) {
  debug = debug_mode;
  // instrMem = new ASM(Program_input);

  ASMParser *parser;

  parser = new ASMParser(Program_input);

  if(parser->isFormatCorrect() == false){
    cerr << "Format of input file is incorrect " << endl;
    exit(1);
  }

  Instruction i;

  maxAddress = 0x400000;

  //Iterate through instructions, printing each encoding.
  i = parser->getNextInstruction();
  while( i.getOpcode() != UNDEFINED){
    // cout << i.getString() << endl;
    // cout << i.getEncoding() << endl;

    // map(address, instruction)
    instMem[maxAddress] = i;

    i = parser->getNextInstruction();
    maxAddress += 4;
  }

  delete parser;
}

InstructionMemory::~InstructionMemory() {
  // delete instrMem;
}

bool InstructionMemory::decode(int address) {
  if (address >= maxAddress) {
    return false;
  }


  PCount = address;
  // currInstr = instrMem->getBinaryInstAt(address);
  currInstr = instMem[address].getEncoding();

  // cout << "CurrInstr = " << currInstr << endl << endl;

  opcode = bitset<6>(currInstr.substr(0, 6)).to_ulong();        // (Inst[31-26])
  rs = bitset<5>(currInstr.substr(6, 5)).to_ulong();            // (Inst[25-21])
  rt = bitset<5>(currInstr.substr(11, 5)).to_ulong();           // (Inst[20-16])
  rd = bitset<5>(currInstr.substr(16, 5)).to_ulong();           // (Inst[15-11])
  shamt = bitset<5>(currInstr.substr(21, 5)).to_ulong();        // (Inst[10-6])
  funct = bitset<6>(currInstr.substr(26, 6)).to_ulong();        // (Inst[5-0]
  immediate = bitset<16>(currInstr.substr(16, 16)).to_ulong();  // (Inst[15-0])
  jumpAddress = bitset<26>(currInstr.substr(6, 26)).to_ulong(); // (Inst[25-0])

  return true;
}

void InstructionMemory::printMIPSInst(int address) {
  // instrMem->printMIPSInst(address);
  cout << std::hex << "MIPS instruction at address 0x" << address << ": " << endl;
  cout << "\t" << instMem[address].getMIPS() << endl << endl;
}

void InstructionMemory::printBinaryInst(int address) {
  // instrMem->printBinaryInst(address);
  cout << std::hex << "Binary encoding of instruction at address 0x" << address << ": " << endl;
  cout << "\t" << instMem[address].getEncoding() << endl << endl;
}

void InstructionMemory::printInput() {
  cout << "input:" << endl;
  cout << std::hex << "\tPCount = 0x" << PCount << endl;
}

void InstructionMemory::printOutput() {
  cout << "output:" << endl;

  if (debug == true) {
    cout << "In binary: " << endl;
    cout << "\topcode = " << currInstr.substr(0, 6) << endl;       // (Inst[31-26])
    cout << "\trs = " << currInstr.substr(6, 5) << endl;           // (Inst[25-21])
    cout << "\trd = " << currInstr.substr(11, 5) << endl;          // (Inst[20-16])
    cout << "\trs = " << currInstr.substr(16, 5) << endl;          // (Inst[15-11])
    cout << "\tshmat = " << currInstr.substr(21, 5) << endl;       // (Inst[10-6])
    cout << "\tfunct = " << currInstr.substr(26, 6) << endl;       // (Inst[5-0]
    cout << "\timmediate = " << currInstr.substr(16, 16) << endl;  // (Inst[15-0])
    cout << "\tjumpAddress = " << currInstr.substr(6, 26) << endl; // (Inst[25-0])
    cout << "-----------------------" << endl;
    cout << "In hexadecimal: " << endl;
  }

  // cout << "\topcode = 0x" << opcode << endl;
  // cout << "\trs = 0x" << rs << endl;
  // cout << std::dec << "\timmediate = " << immediate << endl;
  // cout << std::dec <<"\tjumpAddress = " << jumpAddress << endl;
  cout << std::hex << "\topcode = 0x" << opcode << endl;
  cout << std::hex << "\trs = 0x" << rs << endl;
  cout << std::hex << "\trt = 0x" << rt << endl;
  cout << std::hex << "\trd = 0x" << rd << endl;
  cout << std::hex << "\tshamt = 0x" << shamt << endl;
  cout << std::hex << "\tfunct = 0x" << funct << endl;
  cout << std::hex << "\timmediate = 0x" << immediate << endl;
  cout << std::hex << "\tjumpAddress = 0x" << jumpAddress << endl;
  cout << endl;
}

void InstructionMemory::printInstructionMemory() {
  cout << "address  : binary encoding                  : MIPS instruction" << endl;
  for (map<int, Instruction>::iterator it = instMem.begin(); it != instMem.end(); ++it) {
    cout << hex << "0x" << it->first << " : " << it->second.getEncoding()
         << " : " << it->second.getMIPS() << endl;
  }
}


// bool InstructionMemory::isStringBinaryNum(string s)
//   // Returns true if s represents a valid decimal integer
// {
//   int len = s.length();
//   if (len == 0) return false;
//   for (int i = 0; i < len; i++) {
//     if (( s.at(i) != '0' ) && ( s.at(i) != '1' ))
//       return false;
//   }
// 	return true;
// }


// int InstructionMemory::cvtNumString2Number(string s)
//   // Converts a string to an integer.  Assumes s is something like "-231" and produces -231
// {
//   if (!isStringBinaryNum(s))
//   {
// 	  cerr << "Non-binary string passed to cvtNumString2Number"
// 		  << endl;
// 	  return 0;
//   }
//   int k = 1;
//   int val = 0;
//   for (int i = s.length()-1; i >= 0; i--)
//   {
// 	  char c = s.at(i);
// 	  val = val + k*((int)(c - '0'));
// 	  k = k*10;
//   }

//   return val;
// }