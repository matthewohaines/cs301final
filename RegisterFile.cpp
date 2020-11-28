#include "RegisterFile.h"
#include <iostream>
#include<fstream>
#include<sstream>
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
  for (int i = 0; i < str.length(); i++)
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
	std::ifstream infile {filename}; // get first two numbers, set as i, then for array[i], store the hex values
	std::string line;
	while (getline(infile, line))
	{
		removetheWhitespace(line);
		int index = 0;
		string registerNumber;
		while (line.at(index) != ';')
		{
			registerNumber += line.at(index);
			index++;   
		}

		stringstream registerInt(registerNumber);
		int i;
		registerInt >> i;

		string registerData;
		while( index < line.size())
		{
			registerData += line.at(index);
			index++;
		}

		string hexString = "0x" + registerData;
		stringstream hexInt(hexString);
		int theData;
		hexInt >> theData;

		registerArray[i] = theData;
	}
}

RegisterFile::~RegisterFile(){}

void RegisterFile::readRegisters(int readReg1, int readReg2)
{
	readData1 = readReg1;
	readData2 = readReg2;
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
		cout << registerArray[i] << endl;
	}
}

































