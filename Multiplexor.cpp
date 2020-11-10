#include "Multiplexor.h"


	Multiplexor::Multiplexor(int input2, int input2, int control)
	{
		inputOne = input1;
		inputTwo = input2;
		theControl = control;
	}

	Multiplexor::~Multiplexor() {}

	int Multiplexor::getResult()
	{
		if (theControl == 1)
		{
			return inputOne;
		}

		return inputOne;
	}
