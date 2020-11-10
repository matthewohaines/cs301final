#ifndef __ALU_H__
#define __ALU_H__

using namespace std;

class ALU{

	public:
		ALU();
		~ALU();
		int compute(int term1, int term2, int control);
		int add(int term1, int term2);
		int add4(int term);


	private:
		int inputOne;
		int inputTwo;
		int theControl;


};

#endif