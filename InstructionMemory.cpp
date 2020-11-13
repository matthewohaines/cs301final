// using namespace std;

#include "InstructionMemory.h"

InstructionMemory::InstructionMemory(string Program_input) {
  // assemblyFile = Program_input;
  instrMem = new ASM(Program_input);
}

InstructionMemory::~InstructionMemory() {
  delete instrMem;
}

string InstructionMemory::decode(int address) {
  // cout here?
  return instrMem->getBinaryInstAt(address);
}

void InstructionMemory::printMIPSInst(int address) {
  instrMem->printMIPSInst(address);
}

void InstructionMemory::printBinaryInst(int address) {
  instrMem->printBinaryInst(address);
}