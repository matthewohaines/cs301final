#include "MainControlUnit.h"
#include <iostream>
#include <string>

MainControlUnit::MainControlUnit(){}
MainControlUnit::MainControlUnit(const MainControlUnit& other){}
MainControlUnit::~MainControlUnit(){}

void MainControlUnit::setControls(int opcode){
	op = opcode;
	// std::cout << "opcode = " << op << std::endl;

	if (opcode == 0) { // R-Type Control Values (000000)
		regDst = 1;
		ALUSrc = 0;
		memToReg = 0;
		regWrite = 1;
		memRead = 0;
		memWrite = 0;
		branch = 0;
		jump = 0;
		ALUOp = 2 ; //10
	}

	if (opcode == 35) { // LW Control Values (100011)
		regDst = 0;
		ALUSrc = 1;
		memToReg = 1;
		regWrite = 1;
		memRead = 1;
		memWrite = 0;
		branch = 0;
		jump = 0;
		ALUOp = 0 ; // 00
	}

	if (opcode == 43) { // SW Control Values (101011)
		regDst = -1;
		ALUSrc = 1;
		memToReg = -1;
		regWrite = 0;
		memRead = 0;
		memWrite = 1;
		branch = 0;
		jump = 0;
		ALUOp = 0; // 00
	}


	if (opcode == 4) { //BEQ Control Values (000100)
		regDst = -1;
		ALUSrc = 0;
		memToReg = 0;
		regWrite = 0;
		memRead = 0;
		memWrite = 0;
		branch = 1;
		jump = 0;
		ALUOp = 1; // 01
	}

	if (opcode == 2) {//Jump Control Values (000010)
		regDst = -1;
		ALUSrc = 0;
		memToReg = -1;
		regWrite = 0;
		memRead = 0;
		memWrite = 0;
		branch = 0;
		jump = 1;
		ALUOp = -1; // -1
	}

	if (opcode == 8) { //ADDI Control Values (001000)
		regDst = 0;
		ALUSrc = 1;
		memToReg = 0;
		regWrite = 1;
		memRead = 0;
		memWrite = 0;
		branch = 0;
		jump = 0;
		ALUOp = 3; // 11
	}
}

int MainControlUnit::getRegDst() {return(regDst);}
int MainControlUnit::getJump() {return(jump);}
int MainControlUnit::getBranch() {return(branch);}
int MainControlUnit::getMemRead() {return(memRead);}
int MainControlUnit::getMemToReg() {return(memToReg);}
int MainControlUnit::getALUOp() {return(ALUOp);}
int MainControlUnit::getMemWrite() {return(memWrite);}
int MainControlUnit::getALUSrc() {return(ALUSrc);}
int MainControlUnit::getRegWrite() {return(regWrite);}

void MainControlUnit::printInput(){
	std::cout << "Control input: " << std::endl;
	std::cout << std::hex << "\topcode = " << op << std::endl;
	std::cout << std::endl;
}

void MainControlUnit::printOutput(){
	std::cout << "Control output: " << std::endl;
	std::cout << std::hex << "\tRegDst = 0x" << regDst << std::endl;
	std::cout << std::hex << "\tjump = 0x" << jump << std::endl;
	std::cout << std::hex << "\tbranch = 0x" << branch << std::endl;
	std::cout << std::hex << "\tmemRead = 0x" << memRead << std::endl;
	std::cout << std::hex << "\tmemToReg = 0x" << memToReg << std::endl;
	std::cout << std::hex << "\tALUOp = 0x" << ALUOp << std::endl;  // this will work if ALUOp is an int
	std::cout << std::hex << "\tmemWrite = 0x" << memWrite << std::endl;
	std::cout << std::hex << "\tALUSrc = 0x" << ALUSrc << std::endl;
	std::cout << std::hex << "\tregWrite = 0x" << regWrite << std::endl;
	std::cout << std::endl;
}