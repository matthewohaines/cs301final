#include "MainControlUnit.h"
#include <iostream>
#include <string>

MainControlUnit::MainControlUnit(){}
MainControlUnit::MainControlUnit(const MainControlUnit& other){}
MainControlUnit::~MainControlUnit(){}

void MainControlUnit::setControls(std::string opcode){
	if (opcode.compare("000000") == 0) // R-Type Control Values 
		regDst = 1;
		ALUSrc = 0;
		memToReg = 0;
		regWrite = 1;
		memRead = 0;
		memWrite = 0;
		branch = 0;
		jump = 0;
		ALUOp = "10";
	

	if (opcode.compare("100011") == 0) // LW Control Values 
		regDst = 0;
		ALUSrc = 1;
		memToReg = 1;
		regWrite = 1;
		memRead = 1;
		memWrite = 0;
		branch = 0;
		jump = 0;
		ALUOp = "00";
	

	if (opcode.compare("101011") == 0) // SW Control Values 
		regDst = -1;
		ALUSrc = 1;
		memToReg = -1;
		regWrite = 0;
		memRead = 0;
		memWrite = 1;
		branch = 0;
		jump = 0;
		ALUOp = "00";
	

	if (opcode.compare("000100") == 0) //BEQ Control Values
		regDst = -1;
		ALUSrc = 0;
		memToReg = 0;
		regWrite = 0;
		memRead = 0;
		memWrite = 0;
		branch = 1;
		jump = 0;
		ALUOp = "01";
	
	if (opcode.compare("000010") == 0) //Jump Control Values 
		regDst = -1;
		ALUSrc = 0;
		memToReg = -1;
		regWrite = 0;
		memRead = 0;
		memWrite = 0;
		branch = 0;
		jump = 1;
		ALUOp = "-1";


	if (opcode.compare("001000") == 0) //ADDI Control Values
		regDst = 0;
		ALUSrc = 1;
		memToReg = 0;
		regWrite = 1;
		memRead = 0;
		memWrite = 0;
		branch = 0;
		jump = 0;
		ALUOp = "11";
}

int MainControlUnit::getRegDst() {return(regDst);}
int MainControlUnit::getJump() {return(jump);}
int MainControlUnit::getBranch() {return(branch);}
int MainControlUnit::getMemRead() {return(memRead);}
int MainControlUnit::getMemToReg() {return(memToReg);}
std::string MainControlUnit::getALUOp() {return(ALUOp);}
int MainControlUnit::getMemWrite() {return(memWrite);}
int MainControlUnit::getALUSrc() {return(ALUSrc);}
int MainControlUnit::getRegWrite() {return(regWrite);}
