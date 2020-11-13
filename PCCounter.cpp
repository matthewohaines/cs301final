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

int PCCounter::setCount(int theCount)
{
	count = theCount;
}