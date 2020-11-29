#ifndef __DataMemory_H__
#define __DataMemory_H__

#include <iostream>
#include <string>
#include <map>

class DataMemory{
private:
	std::map<std::string,int> memory;
	std::string dataMemory;
	std::string address;
	int writeData;
	int readData;
	int memWrite; 
	int memRead;

public:
	DataMemory(std::string memoryInput);
	DataMemory(const DataMemory& other);
	~DataMemory();

	void readingAndWritingData(std::string input_address, int readControl, int writeControl, int inputWriteInfo);
	int getReadData();

	void printInput();
	void printOutput();
	void printMemory();

};
#endif