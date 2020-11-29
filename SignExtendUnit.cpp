#include "SignExtendUnit.h"

SignExtendUnit::SignExtendUnit(){}
SignExtendUnit::SignExtendUnit(const SignExtendUnit& other){}
SignExtendUnit::~SignExtendUnit(){}

void SignExtendUnit::signExtend(int number){
	// if (binaryNumber.at(0) == '0'){
	// 	bitNumber = "0000000000000000" + binaryNumber;
	// }
	// if (binaryNumber.at(0) == '1'){
	// 	bitNumber = "1111111111111111" + binaryNumber;
	// }

	input = number;
	output = number;
	// if number is positive, we are good, but if it is negative we need to make
  // sure it is extended by 1s.
	// convert it to binary
	bitset<16> binNum = bitset<16>(number);
	if (binNum[15] == 1) { //check if most significant digit is 1
		// if so convert from two's compliment into integer (flip digits, add 1,
		// and multiply that by -1).
		// when we print it using std::hex, it will be converted back into to two's
		// compliment
		output = -1 * (binNum.flip().to_ulong() + 1);
	}
}

void SignExtendUnit::printInput() {
	cout << "input:" << endl;
	// if we want to print it regularly
	// cout << hex << "\t0x" << input << endl;

	// Printing input in hex, but using setfill, setw(4), and right to fill in all 4 digits
	cout << hex << "\t0x" << setfill('0') << setw(4) << right << input << endl;
}

void SignExtendUnit::printOutput() {
	cout << "output:" << endl;
	// cout << hex << "\t0x" << output << endl << endl;

	// same here except with filling in all 8 digits
	cout << hex << "\t0x" << setfill('0') << setw(8) << right << output << endl << endl;
}