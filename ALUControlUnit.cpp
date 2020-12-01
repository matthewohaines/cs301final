#include "ALUControlUnit.h"
#include <iostream>
#include <string>

ALUControlUnit::ALUControlUnit(){}
ALUControlUnit::ALUControlUnit(const ALUControlUnit& other){}
ALUControlUnit::~ALUControlUnit(){}

void ALUControlUnit::setALUControl(int ALUOpcode, int function){
	ALUOp = ALUOpcode;
	instruction = function;

	if (ALUOp == 2){
		if(instruction == 32){
			ALUControl = 2;
		}
		if(instruction == 34){
			ALUControl = 6;
		}
		if(instruction == 42){
			ALUControl = 7;
		}

	}

	if(ALUOp == 0){
		ALUControl = 2;
	}

	if(ALUOp == 1){
		ALUControl = 6;
	}

	if(ALUOp == 3){
		ALUControl = 2;
	}

	if(ALUOp == -1){
		ALUControl = 6;
	}
}

int ALUControlUnit::getALUControl(){
	return(ALUControl);
}

void ALUControlUnit::printInput(){
	std::cout << "Control input: " << std::endl;
	std::cout << std::hex << "\tfunction = " << instruction << std::endl;
	std::cout << "\tALU Opcode = " << ALUOp << std::endl;
	std::cout << std::endl;
}

void ALUControlUnit::printOutput(){
	std::cout << "Control output: " << std::endl;
	std::cout << std::hex << "\tALU Control = " << ALUControl << std::endl;
	std::cout << std::endl;
}
