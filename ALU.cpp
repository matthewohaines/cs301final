#include "ALU.h"



	ALU::ALU(){}

	ALU::~ALU() {}

	int ALU::compute(int term1, int term2, std::string ALUop){ // a bunch of ints representing output for ALU on diagram
		if (ALUop == "10")  // if ALUop is 10, r-type instruciton, so either add or sub
		{
			return add(term1, term2);
		}

		if (ALUop == "00") // if ALUop is "00", then either LW or SW
		{
			//code
		}

		if (ALUop == "01") // if ALUop is 01, then BEQ
		{
			/* code */
		}

		if (ALUop == "-1") // if ALUop is -1, then jump instruction
		{
			/* code */
		}

		if (ALUop == "11") //if ALU op is "11", then it is ADDI instruction
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