#ifndef __ALU_H__
#define __ALU_H__



class ALU{

	public:
		ALU();
		~ALU();
		int setALUControl(int term1, int term2, std::string ALUop);
		int getALUControl();
		int add(int term1, int term2);
		int add4(int term);


};

#endif