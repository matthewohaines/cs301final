#include "ALU.h"
#include <bitset>


	ALU::ALU(){}

	ALU::~ALU() {}

	int ALU::compute(int term1, int term2, std::string control){
		if (control == "100000")
		{
			return add(term1, term2);
		}

		if (control == "001000")
		{
			return term1 + term2;
		}
		return 0;
	}

	int ALU::add(int term1, int term2){
		return term1 + term2;
	}

	int ALU::add4(int term){
		return term + 4;
	}