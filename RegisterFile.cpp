#include "RegisterFile.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


bool RegisterFile::isitWhitespace(char c)
{
	return (c == ' '|| c == '\t');
}

string RegisterFile::removetheWhitespace(string str)
{
  int count = 0; // non-whitespace characters

  // iterate through string, if we have a non-whitespace character, put it at
  // position count and increment count.
  for (size_t i = 0; i < str.length(); i++)
  {
    if (!isitWhitespace(str.at(i)))
    {
      str.at(count++) = str.at(i);
    }
  }

  return str.substr(0, count);
}

bool RegisterFile::isColon(char c)
{
	return (c == ':');
}


RegisterFile::RegisterFile(string filename)
{
	// std::ifstream infile (filename); // get first two numbers, set as i, then for array[i], store the hex values
	ifstream infile;
	infile.open(filename);
	string line;
	string regNum;
	string value;
	// int i;
	// unsigned int theData;
	// int data;
	// stringstream hexInt;
	// stringstream registerInt;
	while (getline(infile, line))
	{
		removetheWhitespace(line);

		// cout << "line = " << line << endl;

		// get rid of comments (could contain ":")
		string::size_type idx = line.find('#');
		if (idx != string::npos)
			line = line.substr(0,idx);

		// looking for ":" to find parameters
		string::size_type idx1 = line.find(':');
		if (idx1 != string::npos) {
			regNum = line.substr(0,idx1);
			value = line.substr(idx1 + 1);

			int i;
			// needed an unsigned int otherwise bigger hex values were not converted right
			unsigned int theData;
			int data;
			stringstream hexInt;
			stringstream registerInt;
			registerInt << regNum;
			registerInt >> i;
			hexInt << hex << value;
			hexInt >> theData;
			data = static_cast<int>(theData);

			registerArray[i] = data;
		}

		// int index = 0;
		// string registerNumber;
		// while (line.at(index) != ':')
		// {
		// 	registerNumber += line.at(index);
		// 	index++;
		// }

		// stringstream registerInt(registerNumber);
		// int i;
		// registerInt >> i;

		// index ++;  // increment past colon
		// string registerData;
		// while( index < line.size())
		// {
		// 	registerData += line.at(index);
		// 	index++;
		// }

		// string hexString = "0x" + registerData;
		// // stringstream hexInt(hexString);
		// stringstream hexInt;
		// int theData;
		// hexInt << hex << registerData;
		// hexInt >> theData;

		// cout << registerData << endl;
		// cout << "hexString = " << hexString << endl;
		// cout << hex << theData << endl;

		// registerArray[i] = theData;
	}
	infile.close();
}

RegisterFile::~RegisterFile(){}

void RegisterFile::readRegisters(int readReg1, int readReg2)
{
	readData1 = registerArray[readReg1];
	readData2 = registerArray[readReg2];
}

int RegisterFile::getReadData1()
{
	return readData1;
}

int RegisterFile::getReadData2()
{
	return readData2;
}


void RegisterFile::writeBack(int regWrite, int writeRegister, int writeData)
{
	if (regWrite == 1)
	{
		registerArray[writeRegister]  = writeData;
	}
	return;
}

void RegisterFile::printReadInputs()
{
	cout << readRegister1 << ", " << readRegister2 << endl;
}

void RegisterFile::printReadOutputs()
{
	cout << regWrite << ", " << writeRegister << ", " << writeData << endl;
}

void RegisterFile::printRegisterFile()
{
	for (int i = 0; i <= 31; i++)
	{
		cout << dec << i << " : " << hex << registerArray[i] << endl;
	}
}

































