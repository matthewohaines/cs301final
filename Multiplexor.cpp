#include "Multiplexor.h"
#include<iostream>
using namespace std;

Multiplexor::Multiplexor() {}

Multiplexor::~Multiplexor() {}

	int Multiplexor::getResult(int input1, int input2, int control)
	{
		in1 = input1;
		in2 = input2;
		ctrl = control;

		if (control == 0)
		{
			result = input1;
			return input1;
		}

			result = input2;
			return input2;
	}	

	void Multiplexor::printInputs()
	{
		cout << in1 << ", " << in2 << ", " << ctrl << endl;
	}

	void Multiplexor::printOutput()
	{
		cout << result << endl;
	}