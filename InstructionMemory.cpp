// using namespace std;

#include "InstructionMemory.h"

InstructionMemory::InstructionMemory(string Program_input, bool debug_mode) {
  debug = debug_mode;
  instrMem = new ASM(Program_input);
}

InstructionMemory::~InstructionMemory() {
  delete instrMem;
}

string InstructionMemory::decode(int address) {
  PCount = address;
  currInstr = instrMem->getBinaryInstAt(address);

  opcode = bitset<6>(currInstr.substr(0, 6)).to_ulong();        // (Inst[31-26])
  rs = bitset<5>(currInstr.substr(6, 5)).to_ulong();            // (Inst[25-21])
  rt = bitset<5>(currInstr.substr(11, 5)).to_ulong();           // (Inst[20-16])
  rd = bitset<5>(currInstr.substr(16, 5)).to_ulong();           // (Inst[15-11])
  shamt = bitset<5>(currInstr.substr(21, 5)).to_ulong();        // (Inst[10-6])
  funct = bitset<6>(currInstr.substr(26, 6)).to_ulong();        // (Inst[5-0]
  immediate = bitset<16>(currInstr.substr(16, 16)).to_ulong();  // (Inst[15-0])
  jumpAddress = bitset<26>(currInstr.substr(6, 26)).to_ulong(); // (Inst[25-0])

  return currInstr;
}

void InstructionMemory::printMIPSInst(int address) {
  instrMem->printMIPSInst(address);
}

void InstructionMemory::printBinaryInst(int address) {
  instrMem->printBinaryInst(address);
}

void InstructionMemory::printInput() {
  cout << "Instruction memory input:" << endl;
  cout << std::hex << "\tPCount = 0x" << PCount << endl << endl;
}

void InstructionMemory::printOutput() {
  cout << "Instruction memory output:" << endl;

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