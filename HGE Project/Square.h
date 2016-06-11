#pragma once
#include "CommonUtilities\Vector2.h"
class Square
{
public:
	Square();
	~Square();
	bool myUp;
	bool myDown;
	bool myRight;
	bool myLeft;
	bool myIsTaken;
	CU::Vector2i myPosition;
};

