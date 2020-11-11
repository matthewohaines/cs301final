#ifndef __SignExtendUnit_H__
#define __SignExtendUnit_H__

#include <iostream>
#include <string>

class SignExtendUnit{
private:
	std::string bitNumber;

public:
	SignExtendUnit(); //Default Constructor 
	SignExtendUnit(const SignExtendUnit& other); //Copy Constructor
	~SignExtendUnit(); //Deconstructor

	std::string signExtend(std::string binaryNumber);
};

#endif