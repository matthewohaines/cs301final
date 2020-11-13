#ifndef __INSTRUCTIONMEMORY_H__
#define __INSTRUCTIONMEMORY_H__

#include <iostream>
#include "lab5/ASM.h"

using namespace std;

class InstructionMemory{
 public:
  // Constructor & deconstructor
  InstructionMemory(string Program_input);
  ~InstructionMemory();

  // returns binary encoding of instruction at address
  string decode(int address);

  //////////////////////////////////////////////////////////////////////////////
  // getters
  // return string of binary encoding
  string getOpcode() { return opcode; };
  string getRs() { return rs; };
  string getRt() { return rt; };
  string getRd() { return rd; };
  string getShamt() { return shamt; };
  string getFunct() { return funct; };
  string getImm() { return immediate; };
  string getJumpAddress() { return jumpAddress; };

  void printMIPSInst(int address);
  void printBinaryInst(int address);

 private:
  // string assemblyFile;

  ASM *instrMem;         // instance of ASM
  // string currInstr;

  InstType instrType;    // Type of instruction
  string opcode;         // (Inst[31-26])
  string rs;             // (Inst[25-21])
  string rt;             // (Inst[20-16])
  string rd;             // (Inst[15-11])
  string shamt;          // (Inst[10-6])
  string funct;          // (Inst[5-0]
  string immediate;      // (Inst[15-0])
  string jumpAddress;    // (Inst[25-0])


};

#endif