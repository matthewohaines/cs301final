#ifndef __DataMemory_H__
#define __DataMemory_H__

#include <iostream>
#include <string>
#include <map>

class DataMemory{
private:
	std::map<int,int> memory;
	std::string dataMemory;
	int address;
	int writeData;
	int readData;
	int memWrite; 
	int memRead;

public:
	DataMemory(std::string memoryInput);
	DataMemory(const DataMemory& other);
	~DataMemory();

	void readingAndWritingData(int input_address, int readControl, int writeControl, int inputWriteInfo);
	int getReadData();

	void printInput();
	void printOutput();
	void printMemory();

};
#endif