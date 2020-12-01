#include "DataMemory.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>

DataMemory::DataMemory(std::string memoryInput){
	// int key;
	// int value;
	// char col;
	// std::ifstream infile;

	// infile.open(memoryInput);

	// while(infile >> key >> col >> value && col == ':'){
	// 	memory[key] = value;
	// }


	ifstream infile;
	infile.open(memoryInput);
	string line;
	string addr;
	string value;
	while (getline(infile, line))
	{
		removeWhitespace(line);

		// get rid of comments (could contain ":")
		string::size_type idx = line.find('#');
		if (idx != string::npos)
			line = line.substr(0,idx);

		// looking for ":" to find parameters
		string::size_type idx1 = line.find(':');
		if (idx1 != string::npos) {
			addr = line.substr(0,idx1);
			value = line.substr(idx1 + 1);

			unsigned int i;
			int j;
			// needed an unsigned int otherwise bigger hex values were not converted right
			unsigned int theData;
			int data;
			stringstream addressNum; // using stringstream to convert string to int
			stringstream hexInt;
			addressNum << hex << addr;
			addressNum >> i;
			j = static_cast<int>(i);
			hexInt << hex << value;
			hexInt >> theData;
			data = static_cast<int>(theData);

			memory[j] = data;
		}
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
	// std::map<int,int>::key_compare keycomp = memory.key_comp();
	// std::map<int,int>::iterator it = memory.begin();

	// while(keycomp((*it++).first, address));


	try {
		if (memRead == 1){
			readData = memory.at(address);
		}

		if(memWrite == 1){
			memory.at(address) = writeData;
		}
	}
	catch (...) {
		cerr << hex << "Error: Trying to access address 0x" << address
		     << " which is not contained in the memory file!" << endl;
		exit(1);
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

bool DataMemory::isWhitespace(char c)
{
	return (c == ' '|| c == '\t');
}

string DataMemory::removeWhitespace(string str)
{
  int count = 0; // non-whitespace characters

  // iterate through string, if we have a non-whitespace character, put it at
  // position count and increment count.
  for (int i = 0; i < str.length(); i++)
  {
    if (!isWhitespace(str.at(i)))
    {
      str.at(count++) = str.at(i);
    }
  }

  return str.substr(0, count);
}