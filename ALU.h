#ifndef __ALU_H__
#define __ALU_H__

#include <bitset>


class ALU{

	public:
		ALU();
		~ALU();
		int compute(int term1, int term2, std::string control);
		int add(int term1, int term2);
		int add4(int term);


};

#endif