#ifndef __ALUControlUnit_H__
#define __ALUControlUnit_H__

#include <iostream>
#include <string>

class ALUControlUnit{
	private:
		int ALUOp;
		int instruction;
		int ALUControl;


	public:
		ALUControlUnit();
		ALUControlUnit(const ALUControlUnit& other);
		~ALUControlUnit();

		void setALUControl(int ALUOpcode, int function);
		int getALUControl();

		void printInput();
		void printOutput();


};
#endif 