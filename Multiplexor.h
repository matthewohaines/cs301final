#ifndef __MULTIPLEXOR_H__
#define __MULTIPLEXOR_H__

#include<iostream>
using namespace std;

class Multiplexor{

	private:
		int in1;
		int in2;
		int ctrl;
		int result;

	public:
		Multiplexor();
		~Multiplexor();
		int getResult(int input1, int input2, int control);
		void printInputs();
		void printOutput();


};

#endif