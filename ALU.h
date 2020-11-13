#ifndef __ALU_H__
#define __ALU_H__

#include <iostream>
using namespace std;


class ALU{

	public:
		ALU();
		~ALU();
		int setALUControl(int term1, int term2, std::string operation);
		int getALUControl();
		int add(int term1, int term2);
		int add4(int term);
		int subtract(int term1, int term2);
		int slt(int term1, int term2);


};

#endif