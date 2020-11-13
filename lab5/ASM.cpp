#include "ASM.h"
#include <iostream>

using namespace std;

/*
 * This file reads in a MIPS assembly file specified at the command line.
 * If the file is correct syntactically, each instruction in the file
 * will be translated into its 32 bit MIPS binary encoding and entered into the
 * instructionMemory map
 *
 */

ASM::ASM(string filename) {
  ASMParser *parser;

  parser = new ASMParser(filename);

  if(parser->isFormatCorrect() == false){
    cerr << "Format of input file is incorrect " << endl;
    exit(1);
  }

  Instruction i;

  int address = 0x400000;

  //Iterate through instructions, printing each encoding.
  i = parser->getNextInstruction();
  while( i.getOpcode() != UNDEFINED){
    // cout << i.getString() << endl;
    // cout << i.getEncoding() << endl;

    // map(curr address get binary encoding.)
    instructionMemory[address] = pair(i.getMIPS(), i.getEncoding());

    i = parser->getNextInstruction();
    address += 4;
  }
}

// string ASM::getBinaryInstAt(int address) {
//   return instructionMemory[address].second;
// }

void ASM::printMIPSInst(int address) {
  // cout << std::hex << "Instruction at address 0x" << address << " (MIPS): "
  //      << instructionMemory[address].first << endl;
  // cout << instructionMemory[address].first << std::hex
  //      << " (MIPS instruction at address 0x" << address << ")" << endl;

  cout << std::hex << "MIPS instruction at address 0x" << address << ": " << endl;
  cout << "\t" << instructionMemory[address].first << endl;
}

void ASM::printBinaryInst(int address) {
  // cout << std::hex << "Instruction at address 0x" << address << "(binary encoding): "
  //      << instructionMemory[address].second << endl;
  // cout << instructionMemory[address].second << std::hex
  //      << " (Binary encoding of instruction at address 0x" << address << ")" << endl;

  cout << std::hex << "Binary encoding of instruction at address 0x" << address << ": " << endl;
  cout << "\t" << instructionMemory[address].second << endl;
}

// int ASM::getBinaryInstAt(hex address)
// {
//   return
// }

// ASM::~ASM()
// {
//   delete parser;
// }

// int main(int argc, char *argv[])
// {
//   ASMParser *parser;

//   if(argc < 2){
//     cerr << "Need to specify an assembly file to translate."<<endl;
//     exit(1);
//   }

//   parser = new ASMParser(argv[1]);

//   if(parser->isFormatCorrect() == false){
//     cerr << "Format of input file is incorrect " << endl;
//     exit(1);
//   }

//   Instruction i;

//   //Iterate through instructions, printing each encoding.
//   i = parser->getNextInstruction();
//   while( i.getOpcode() != UNDEFINED){
//     // cout << i.getString() << endl;
//     cout << i.getEncoding() << endl;
//     i = parser->getNextInstruction();
//   }

//   delete parser;
// }
