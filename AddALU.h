#ifndef __ADDALU_H__
#define __ADDALU_H__

using namespace std;

class AddALU{

	public:
		AddALU(int term1, int term2);
		~AddALU();
		int add();
		int add4();

	private:
		int termOne;
		int termTwo;


};

#endif