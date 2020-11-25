#include "ShiftLeft.h"
#include <iostream>
#include <string>

ShiftLeft::ShiftLeft(){}
ShiftLeft::ShiftLeft(const ShiftLeft& other){}
ShiftLeft::~ShiftLeft(){}

std::string ShiftLeft::shiftLeft2(std::string binaryNum){
	if (binaryNum.length() == 32){
		binaryNum = binaryNum.substr(2,31) + "00";
	}
	if (binaryNum.length() == 26){
		binaryNum = binaryNum.substr(2,25) + "00";
	}

	return(binaryNum);
}