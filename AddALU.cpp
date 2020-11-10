#include "AddALU.h"


	AddALU::AddALU(int term2, int term2)
	{
		termOne = term1;
		termTwo = term2;
	}

	AddALU::~AddALU() {}

	int AddALU::add()
	{
		int result = termOne + termTwo;
		return result;
	}

	int AddALU::add4()
	{
		int result = termOne + 4;
		return result;
	}