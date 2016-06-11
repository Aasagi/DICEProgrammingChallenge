#include "MemoryBucket.h"

CU::MemoryBucket::MemoryBucket(const int aStartSize)
{
	myStartSize = aStartSize;
	myData = new char[myStartSize];
	myCurrAdress = 0;
}

CU::MemoryBucket::~MemoryBucket()
{
	delete[] myData;
	myData = nullptr;
}

void CU::MemoryBucket::Clear()
{
	myCurrAdress = 0;
}

//CU::MemoryBucket& CU::MemoryBucket::operator=(const CU::MemoryBucket& aBucket)
//{
//	myData = aBucket.myData;
//	myCurrAdress = aBucket.myCurrAdress;
//	myStartSize = aBucket.myStartSize;
//	return *this;
//}