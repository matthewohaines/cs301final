#ifndef __INSTRUCTIONMEMORY_H__
#define __INSTRUCTIONMEMORY_H__

using namespace std;

#include <iostream>
#include "lab5/ASM.h"

class InstructionMemory{
 public:
  InstructionMemory(string Program_input);
  ~InstructionMemory();

  int decode(int address);

  string getOpcode() { return opcode; };
  string getRs() { return rs; };
  string getRt() { return rt; };
  string getRd() { return rd; };
  string getShamt() { return shamt; };
  string getFunct() { return funct; };
  string getImm() { return immediate; };
  string getJumpAddress() { return jumpAddress; };

 private:
  string assemblyFile;
  ASM *instrMem;
  string currInstr;
  InstType instrType;
  string opcode;         //(Inst[31-26])
  string rs;
  string rt;
  string rd;
  string shamt;          //(Inst[10-6])
  string funct;          //(Inst[5-0]
  string immediate;      //(Inst[15-0])
  string jumpAddress;    //(Inst[25-0])


};

#endif