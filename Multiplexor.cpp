#include "Multiplexor.h"


	Multiplexor::Multiplexor() {}

	Multiplexor::~Multiplexor() {}

	int Multiplexor::getResult(int input1, int input2, int control)
	{
		if (control == 0)
		{
			return input1;
		}

		return input2;
	}
