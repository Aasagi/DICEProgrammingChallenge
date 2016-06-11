#pragma once
#include "CommonUtilities\Vector2.h"
class Line
{
public:
	Line();
	~Line();

	void RenderLine();

	CU::Vector2i myPosition1;
	CU::Vector2i myPosition2;


};

