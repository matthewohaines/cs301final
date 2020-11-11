#ifndef __ASM_H__
#define __ASM_H__

using namespace std;

#include "ASMParser.h"
// #include <iostream>

using namespace std;

class ASM{
 public:
  map<int, pair<string, int>> instructionMemory; // map for addresses and their
                          // corresponding MIPS Instruction and binary encoding

  ASM(string filename); // constructo initallized instTable

  int getBinaryInstAt(int address) { return instructionMemory[address].second; };
  void print(int address);

 private:




};

#endif