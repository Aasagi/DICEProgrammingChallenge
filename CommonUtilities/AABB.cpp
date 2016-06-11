#include "AABB.h"

AABB::AABB(void)
{
	myX = 0.f;
	myY = 0.f;
	myWidth = 0.f;
	myHeight = 0.f;
}

AABB::AABB(const float aX, const float aY, const float aWidth, const float aHeight)
{
	myX = aX;
	myY = aY;
	myWidth = aWidth;
	myHeight = aHeight;
}

AABB::~AABB(void)
{
}

bool AABB::Inside(const CU::Vector2f& aPoint)
{
	if (aPoint.x > myX && aPoint.x < (myX + myWidth) && aPoint.y > myY && aPoint.y < myY + myHeight)
	{
		return true;
	}

	return false;
}

bool AABB::Collides(const AABB aBoundingBox)
{
	if (myX < aBoundingBox.myX + aBoundingBox.myWidth &&
		myX + myWidth > aBoundingBox.myX &&
		myY < aBoundingBox.myY + aBoundingBox.myHeight &&
		myHeight + myY > aBoundingBox.myY)
	{
		return true;
	}

	return false;
}


float AABB::GetX() const
{
	return myX;
}

float AABB::GetY() const
{
	return myY;
}

float AABB::GetWidth() const
{
	return myWidth;
}

float AABB::GetHeight() const
{
	return myHeight;
}

void AABB::SetX(const float aX)
{
	myX = aX;
}

void AABB::SetY(const float aY)
{
	myY = aY;
}
void AABB::SetWidth(const float aWidth)
{
	myWidth = aWidth;
}

void AABB::SetHeight(const float aHeight)
{
	myHeight = aHeight;
}
