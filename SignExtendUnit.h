#ifndef __SignExtendUnit_H__
#define __SignExtendUnit_H__

#include <iostream>
#include <string>
#include <iomanip>
#include <bitset>

using namespace std;

class SignExtendUnit{
private:
	int input;
	int output;
	std::string bitNumber;

public:
	SignExtendUnit(); //Default Constructor
	SignExtendUnit(const SignExtendUnit& other); //Copy Constructor
	~SignExtendUnit(); //Deconstructor

	void signExtend(int number);
	int getSignExtended() { return output; };
	void printInput();
	void printOutput();
};

#endif