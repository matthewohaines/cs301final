#ifndef __MainControlUnit_H__
#define __MainControlUnit_H__

#include <iostream>
#include <string>

class MainControlUnit{
	private:
		int regDst;
		int jump;
		int branch; 
		int memRead;
		int memToReg;
		std::string ALUOp;
		int memWrite;
		int ALUSrc;
		int regWrite;

	public:
		MainControlUnit(); //Default Constructor 
		MainControlUnit(const MainControlUnit& other); //Copy Constructor 
		~MainControlUnit(); //Deconstructor

		void setControls(std::string opcode); //Sets all variables based on the given opcode

		int getRegDst();
		int getJump();
		int getBranch();
		int getMemRead();
		int getMemToReg();
		std::string getALUOp();
		int getMemWrite();
		int getALUSrc();
		int getRegWrite();


};

#endif
