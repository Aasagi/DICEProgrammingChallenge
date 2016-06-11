#pragma once
#include "CommonUtilities\Vector.h"
class Camera
{
public:
	Camera();
	~Camera();

	CU::Vector2f ConvertPositionToCameraPosition(const CU::Vector2f& aPosition);
	CU::Vector2f ConvertSquarePositionToCameraPosition(const CU::Vector2f& aPosition);



	CU::Vector2f myPositionOffset;



};

