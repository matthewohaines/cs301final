#ifndef __PCCOUNTER_H__
#define __PCCOUNTER_H__

#include <iostream>
using namespace std;


class PCCounter{
	private:
		int count;


	public:
		PCCounter();
		~PCCounter();
		int getCount();
		int setCount(int theCount);


};

#endif