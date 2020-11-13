#ifndef __ShiftLeft_H__
#define __ShiftLeft_H__

#include <iostream>
#include <string>

class ShiftLeft{
public:
	ShiftLeft();
	ShiftLeft(const ShiftLeft& other);
	~ShiftLeft();

	std::string shiftLeft2(std::string binaryNum);
};
#endif