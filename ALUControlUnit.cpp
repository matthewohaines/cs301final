#include "ALUControlUnit.h"
#include <iostream>
#include <string>

ALUControlUnit::ALUControlUnit(){}
ALUControlUnit::ALUControlUnit(const ALUControlUnit& other){}
ALUControlUnit::~ALUControlUnit(){}

void ALUControlUnit::setALUControl(std::string ALUOpcode, int function){
	ALUOp = ALUOpcode;
	instruction = function;

	if (ALUOp.compare("10") == 0){
		if(instruction == 32){
			ALUControl = 2;
		}
		if(instruction == 43){
			ALUControl = 6;
		}
		if(instruction == 42){
			ALUControl = 7;
		}

	}
		
	if(ALUOp.compare("00") == 0){
		ALUControl = 2;
	}

	if(ALUOp.compare("01") == 0){
		ALUControl = 6;
	}
	
	if(ALUOp.compare("11") == 0){
		ALUControl = 2;
	}

	if(ALUOp.compare("-1") == 0){
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
	std:cout << std::hex << "\tALU Control = " << ALUControl << std::endl;
	std::cout << std::endl;
}
