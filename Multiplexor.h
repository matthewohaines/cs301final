#ifndef __MULTIPLEXOR_H__
#define __MULTIPLEXOR_H__

using namespace std;

class Multiplexor{

	public:
		Multiplexor(int input1, int input2, int control);
		~Multiplexor();
		int getResult();

	private:
		int inputOne;
		int inputTwo;
		int theControl;


};

#endif