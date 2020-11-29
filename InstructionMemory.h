#ifndef __INSTRUCTIONMEMORY_H__
#define __INSTRUCTIONMEMORY_H__

#include <iostream>
#include <bitset>
#include "lab5/ASMParser.h"
#include "lab5/Instruction.h"

using namespace std;

class InstructionMemory{
 public:
  // Constructor & deconstructor
  InstructionMemory(string Program_input, bool debug_mode);
  ~InstructionMemory();

  // returns binary encoding of instruction at address
  bool decode(int address);

  //////////////////////////////////////////////////////////////////////////////
  // getters
  // return string of binary encoding
  int getOpcode() { return opcode; };
  int getRs() { return rs; };
  int getRt() { return rt; };
  int getRd() { return rd; };
  int getShamt() { return shamt; };
  int getFunct() { return funct; };
  int getImm() { return immediate; };
  int getJumpAddress() { return jumpAddress; };
  int getMaxAddress() { return maxAddress; };

  void printMIPSInst(int address);
  void printBinaryInst(int address);

  void printInput();
  void printOutput();

  void printInstructionMemory();


 private:
  bool debug;

  int PCount;            // input PCount set everytime decode is called
  string currInstr;      // current instruction
  int maxAddress;        // first address that does not contain an instruction

  // ASM *instrMem;         // instance of ASM
  map<int, Instruction> instMem; // map for addresses and their
                                 // corresponding instruction


  int opcode;         // (Inst[31-26])
  int rs;             // (Inst[25-21])
  int rt;             // (Inst[20-16])
  int rd;             // (Inst[15-11])
  int shamt;          // (Inst[10-6])
  int funct;          // (Inst[5-0]
  int immediate;      // (Inst[15-0])
  int jumpAddress;    // (Inst[25-0])

  // // Returns true if s represents a valid binary integer
  // bool isStringBinaryNum(string s);

  // // Converts a string to an integer.  Assumes s is something like "101" and produces 5
  // int  cvtNumString2Number(string s);

};

#endif