#ifndef __REGISTERFILE_H__
#define __REGISTERFILE_H__

#include <iostream>
#include<fstream>
#include<sstream>
using namespace std;


class RegisterFile{
	private:
		int readRegister1;
		int readRegister2;
		int readData1;
		int readData2;
		int writeReg;
		int writeData;
		int regWrite;

		int registerArray[32]; // creates 32 int array, all initialized to 0


	public:
		RegisterFile(string filename);
		~RegisterFile();
		int readReg1(int readReg1);
		int readReg2(int readReg2);
		void printRegisters();


};

#endif