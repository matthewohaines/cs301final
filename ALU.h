#ifndef __ALU_H__
#define __ALU_H__

#include <iostream>
using namespace std;


class ALU{
    private:
    	std::string control;
    	int input1;
    	int input2;
    	int result;
    	const static int zero = 0;

    	int add(int term1, int term2);
		int add4(int term);
		int subtract(int term1, int term2);
		int slt(int term1, int term2);
	public:
		ALU(std::string theControl, int theinput1, int theinput2);
		~ALU();
		void compute(int term1, int term2, std::string operation);
		int getALUResult();
		int getALUControl();
		int getZero();
		void printInputs();
		void printOutputs();

};

#endif