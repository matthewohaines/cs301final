#ifndef __ALUControlUnit_H__
#define __ALUControlUnit_H__

#include <iostream>
#include <string>

class ALUControlUnit{
	private:
		std::string ALUOp;
		int instruction;
		int ALUControl;


	public:
		ALUControlUnit();
		ALUControlUnit(const ALUControlUnit& other);
		~ALUControlUnit();

		void setALUControl(std::string ALUOpcode, int function, int op);
		int getALUControl();

		void printInput();
		void printOutput();


};
#endif 