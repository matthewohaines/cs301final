#include "ShiftLeft.h"
#include <iostream>
#include <string>

ShiftLeft::ShiftLeft(){}
ShiftLeft::ShiftLeft(const ShiftLeft& other){}
ShiftLeft::~ShiftLeft(){}

void ShiftLeft::shiftLeft2(int binaryNum){
	input = binaryNum;
	output = binaryNum * 4; // same as shifting left twice in binary
}

void ShiftLeft::printInput(){
	cout << "Input:" << endl;
	cout << hex << "\t0x" << input << endl;
}
void ShiftLeft::printOutput(){
	cout << "Output:" << endl;
	cout << hex << "\t0x" << output << endl << endl;
}