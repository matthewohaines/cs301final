#include "DataMemory.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>

DataMemory::DataMemory(std::string memoryInput){
	int key;
	int value;
	char col;
	std::ifstream infile;

	infile.open(memoryInput);

	while(infile >> key >> col >> value && col == ':'){
		memory[key] = value;
	}

	infile.close();
}

DataMemory::DataMemory(const DataMemory& other){}
DataMemory::~DataMemory(){}

void DataMemory::readingAndWritingData(int inputAddress, int readControl, int writeControl, int inputWriteInfo){
	memRead = readControl;
	memWrite = writeControl;
	writeData = inputWriteInfo;
	address = inputAddress;
	std::map<int,int>::key_compare keycomp = memory.key_comp();
	std::map<int,int>::iterator it = memory.begin();

	while(keycomp((*it++).first, address));

	if (memRead == 1){
		readData = memory.at(address);
	}

	if(memWrite == 1){
		memory.at(address) = writeData;
	}
}

int DataMemory::getReadData(){
	return(readData);
}

void DataMemory::printInput(){
	std::cout << "Data Memory input: " << std::endl;
	std::cout << "Input address: " << address << std::endl;
	std::cout << "Memory Write Control: " << memWrite << std::endl;
	std::cout << "Memory Read Control: " << memRead << std::endl;
}
void DataMemory::printOutput(){
	std::cout << "Data Memory output: " << std::endl;
	std::cout << readData << std::endl;
	std::cout << writeData << std::endl;
}
void DataMemory::printMemory(){
	std::cout << dataMemory << std::endl;
}