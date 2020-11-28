#ifndef __ShiftLeft_H__
#define __ShiftLeft_H__

#include <iostream>
#include <string>

using namespace std;

class ShiftLeft{
 public:
	ShiftLeft();
	ShiftLeft(const ShiftLeft& other);
	~ShiftLeft();

	void shiftLeft2(int binaryNum);
	int getResult() { return output; };
	void printInput();
	void printOutput();

 private:
	int input;
	int output;

};
#endif