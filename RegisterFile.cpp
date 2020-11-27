#include "RegisterFile.h"
#include <iostream>
#include<fstream>
#include<sstream>
using namespace std;


bool isitWhitespace(char c)
{ 
	return (c == ' '|| c == '\t'); 
}

string removetheWhitespace(string str)
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

bool isColon(char c) 
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

int RegisterFile::readReg1(int readReg1)
{
	return registerArray[readReg1];
}

int RegisterFile::readReg2(int readReg2)
{
	return registerArray[readReg2];
}


void RegisterFile::printRegisters()
{
	for (int i = 0; i <= 31; i++)
	{
		cout << registerArray [i] << endl;
	}

	return;
}
