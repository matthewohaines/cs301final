#include "PCCounter.h"
#include<iostream>
using namespace std;

PCCounter::PCCounter()
{
	count = 0x400000;
}

PCCounter::~PCCounter(){}

int PCCounter::getCount()
{
	return count;
}

void PCCounter::setCount(int theCount)
{
	count = theCount;
}

void PCCounter::printCounter()
{
	cout << count << endl;
}