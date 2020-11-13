#include "ALU.h"


/* the ALU is given two terms and a control, 
depending on what this control is, 
a certain function will be operated on these two terms */
#include<iostream>
using namespace std;

	ALU::ALU(){}

	ALU::~ALU() {}

	int ALU::setALUControl(int term1, int term2, std::string operation){ // a bunch of ints representing output for ALU on diagram
		if (operation == "add")  // if ALUop is 10, r-type instruciton, so either add or sub
		{
			return add(term1, term2);
		}

		if (operation== "addi") 
		{
			return add(term1, term2);
		}

		if (operation == "sub") 
		{
			return subtract(term1, term2);
		}

		if (operation == "slt") 
		{
			return slt(term1, term2);
		}

		if (operation == "lw") 
		{
			/* code */
		}

		if (operation == "sw")
		{

		}

		if (operation == "beq")
		{
			/* code */
		}

		if (operation == "j")
		{
			/* code */
		}
		return 0;
	}

	int ALU::add(int term1, int term2){
		return term1 + term2;
	}

	int ALU::add4(int term){
		return term + 4;
	}

	int ALU::subtract(int term1, int term2){
		return term1 - term2;
	}

	int ALU::slt(int term1, int term2)
	{
		if (term1 < term2)
		{
			return 1;
		}
		return 0;
	}






















