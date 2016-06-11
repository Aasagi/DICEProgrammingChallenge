#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	myPositionOffset.myX = 0.f;
	myPositionOffset.myY = 0.f;
}


Camera::~Camera()
{
}

CU::Vector2f Camera::ConvertPositionToCameraPosition(const CU::Vector2f& aPosition)
{
	return (aPosition - myPositionOffset);
}

CU::Vector2f Camera::ConvertSquarePositionToCameraPosition(const CU::Vector2f& aPosition)
{
	return (aPosition - myPositionOffset*myPositionOffset);
}
