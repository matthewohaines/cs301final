#include "ALU.h"


/* the ALU is given two terms and a control, 
depending on what this control is, 
a certain function will be operated on these two terms */
#include<iostream>
using namespace std;

	ALU::ALU(){}

	ALU::~ALU() {}

	void ALU::compute(int term1, int term2, int operation)
	{ // a bunch of ints representing output for ALU on diagram
		if (operation == 2)  // if ALUop is 10, r-type instruciton, so either add or sub
		{
			result =  add(term1, term2);
		}

		if (operation == 6) 
		{
			result =  subtract(term1, term2);
		}

		if (operation == 7) 
		{
			result =  slt(term1, term2);
		}

		// if (operation == "lw") 
		// {
		// 	result = add(term1, term2);
		// }

		// if (operation == "sw")
		// {
		// 	result = add(term1, term2);
		// }

		// if (operation == "beq")
		// {
		// 	if (subtract(term1, term2) == 0)
		// 	{ 
		// 		result = 1;
		// 	}
		// 	 result =  0;

		// }
		return;
	}

	int ALU::getALUResult()
	{
		return result;
	}

	int ALU::getZero()
	{
		return zero;
	}

	void ALU::printInputs()
	{
		cout << control << ", " << input1 << ", "  << input2 << endl;
	}

	void ALU::printOutputs()
	{
		cout << result << ", " << zero << endl;
	}

/*----------HELPER METHODS---------------*/

	int ALU::add(int term1, int term2)
	{
		return term1 + term2;
	}

	int ALU::add4(int term)
	{
		return term + 4;
	}

	int ALU::subtract(int term1, int term2)
	{
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






















