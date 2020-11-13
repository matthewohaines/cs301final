#ifndef __ASM_H__
#define __ASM_H__

#include "ASMParser.h"
// #include <iostream>

using namespace std;

class ASM{
 public:
  map<int, pair<string, string>> instructionMemory; // map for addresses and their
                          // corresponding MIPS Instruction and binary encoding

  // constructor
  // initalized instructionMemory
  ASM(string filename);

  // int getBinaryInstAt(int address);
  string getBinaryInstAt(int address) { return instructionMemory[address].second; };

  void printMIPSInst(int address);
  void printBinaryInst(int address);

};

#endif