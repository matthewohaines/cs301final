#ifndef __MainControlUnit_H__
#define __MainControlUnit_H__

#include <iostream>
#include <string>

class MainControlUnit{
	private:
		int op;

		int regDst;
		int jump;
		int branch;
		int memRead;
		int memToReg;
		int ALUOp;
		int memWrite;
		int ALUSrc;
		int regWrite;

	public:
		MainControlUnit(); //Default Constructor
		MainControlUnit(const MainControlUnit& other); //Copy Constructor
		~MainControlUnit(); //Deconstructor

		void setControls(int opcode); //Sets all variables based on the given opcode

		int getRegDst();
		int getJump();
		int getBranch();
		int getMemRead();
		int getMemToReg();
		int getALUOp();
		int getMemWrite();
		int getALUSrc();
		int getRegWrite();

		void printInput();
		void printOutput();
};

#endif
