#ifndef __REGISTERFILE_H__
#define __REGISTERFILE_H__

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


class RegisterFile{
	private:
		int readRegister1;
		int readRegister2;
		int readData1;
		int readData2;
		int writeRegister;
		int writeData;
		int regWrite;

		int registerArray[32]; // creates 32 int array, all initialized to 0


	public:
		RegisterFile(string filename);
		~RegisterFile();
		void readRegisters(int readReg1, int readReg2);
		int getReadData1();
		int getReadData2();
		int getRegister(int reg) { return registerArray[reg]; };
		void writeBack(int regWrite, int writeRegister, int writeData);
		void printReadInputs();
		void printReadOutputs();
		void printRegisterFile();
		bool isitWhitespace(char c);
		string removetheWhitespace(string str);
		bool isColon(char c);

};

#endif