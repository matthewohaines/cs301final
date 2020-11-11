// using namespace std;

#include "InstructionMemory.h"

InstructionMemory::InstructionMemory(string Program_input) {
  assemblyFile = Program_input;
  instrMem = new ASM(assemblyFile);
}

InstructionMemory::~InstructionMemory() {
  delete instrMem;
}

int InstructionMemory::decode(int address) {
  return instrMem->getBinaryInstAt(address);
}