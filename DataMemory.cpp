#include "DataMemory.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>

DataMemory::DataMemory(std::string memoryInput){
	std::string key;
	std::string value;
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

void DataMemory::readingAndWritingData(std::string inputAddress, int readControl, int writeControl, int inputWriteInfo){
	memRead = readControl;
	memWrite = writeControl;
	writeData = inputWriteInfo;
	address = inputAddress;

	if (memRead == 1){

	}

	if(memWrite == 1){

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