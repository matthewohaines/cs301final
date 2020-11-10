#ifndef __ALU_H__
#define __ALU_H__

using namespace std;

class ALU{

	public:
		ALU(int term1, int term2, int control);
		~ALU();
		int compute();


	private:
		int inputOne;
		int inputTwo;
		int theControl;


};

#endif