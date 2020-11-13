#include "RegisterFile.h"
#include <iostream>
#include<fstream>
#include<sstream>
using namespace std;


bool isWhitespace(char c)
{ 
	return (c == ' '|| c == '\t'); 
}

string removeWhitespace(string str)
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
}

bool isColon(char c) 
{ 
	return (c == ':');
}


RegisterFile::RegisterFile(string filename)
{
	std::ifstream infile {filename} // get first two numbers, set as i, then for array[i], store the hex values
	std::string line;
	while (getLine(infile, line))
	{
		line.removeWhitespace();
		int index = 0;
		while (line.at(index) != ";")
		{
			string registerNumber += line.at(index);
			index++;
		}

		stringstream registerInt(registerNumber);
		int i;
		registerInt >> i;

		while( index < line.size())
		{
			string registerData += line.at(index);
			index++;
		}

		string hexString = "0x" + registerData;
		stringstream hexInt(hexData);
		int theData;
		hexInt >> theData;

		registerArray[i] = theData;
	}
}

RegisterFile::~RegisterFile(){}


// 12:ab236711