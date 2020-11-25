#include "SignExtendUnit.h"
#include <iostream>
#include <string>

SignExtendUnit::SignExtendUnit(){}
SignExtendUnit::SignExtendUnit(const SignExtendUnit& other){}
SignExtendUnit::~SignExtendUnit(){}

std::string SignExtendUnit::signExtend(std::string binaryNumber){
	if (binaryNumber.at(0) == '0'){
		bitNumber = "0000000000000000" + binaryNumber;
	}

	if (binaryNumber.at(0) == '1'){
		bitNumber = "1111111111111111" + binaryNumber;
	}

	return(bitNumber);
}