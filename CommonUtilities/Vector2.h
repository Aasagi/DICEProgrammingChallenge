#ifndef VECTOR2_H
#define VECTOR2_H

#include "Vector2decl.h"

template<typename Type>
CU::Vector2<Type> operator+(const CU::Vector2<Type>& aFirstVector2, const CU::Vector2<Type>& aSecondVector2)
{
	CU::Vector2<Type> tmpVector;

	tmpVector.myX = aFirstVector2.myX + aSecondVector2.myX;
	tmpVector.myY = aFirstVector2.myY + aSecondVector2.myY;

	return tmpVector;
}

template<typename Type>
CU::Vector2<Type> operator-(const CU::Vector2<Type>& aFirstVector2, const CU::Vector2<Type>& aSecondVector2)
{
	CU::Vector2<Type> tmpVector;

	tmpVector.myX = aFirstVector2.myX - aSecondVector2.myX;
	tmpVector.myY = aFirstVector2.myY - aSecondVector2.myY;

	return tmpVector;
}

template<typename Type>
CU::Vector2<Type> operator*(const CU::Vector2<Type>& aFirstVector2, const CU::Vector2<Type>& aSecondVector2)
{
	CU::Vector2<Type> tmpVector;

	tmpVector.myX = aFirstVector2.myX * aSecondVector2.myX;
	tmpVector.myY = aFirstVector2.myY * aSecondVector2.myY;

	return tmpVector;
}

template<typename Type>
CU::Vector2<Type> operator/(const CU::Vector2<Type>& aFirstVector2, const CU::Vector2<Type>& aSecondVector2)
{
	CU::Vector2<Type> tmpVector;

	tmpVector.myX = aFirstVector2.myX / aSecondVector2.myX;
	tmpVector.myY = aFirstVector2.myY / aSecondVector2.myY;

	return tmpVector;
}

template<typename Type>
void operator+=(CU::Vector2<Type>& aFirstVector2, const CU::Vector2<Type>& aSecondVector2)
{
	aFirstVector2.myX += aSecondVector2.myX;
	aFirstVector2.myY += aSecondVector2.myY;
}

template<typename Type>
void operator-=(CU::Vector2<Type>& aFirstVector2, const CU::Vector2<Type>& aSecondVector2)
{
	aFirstVector2.myX -= aSecondVector2.myX;
	aFirstVector2.myY -= aSecondVector2.myY;
}

template<typename Type>
void operator*=(CU::Vector2<Type>& aFirstVector2, const CU::Vector2<Type>& aSecondVector2)
{
	aFirstVector2.myX *= aSecondVector2.myX;
	aFirstVector2.myY *= aSecondVector2.myY;
}

template<typename Type>
void operator/=(CU::Vector2<Type>& aFirstVector2, const CU::Vector2<Type>& aSecondVector2)
{
	aFirstVector2.myX /= aSecondVector2.myX;
	aFirstVector2.myY /= aSecondVector2.myY;
}

template<typename Type>
CU::Vector2<Type> operator*(const CU::Vector2<Type>& aVector2, Type aScalar)
{
	CU::Vector2<Type> tmpVector;

	tmpVector.myX = aVector2.myX * aScalar;
	tmpVector.myY = aVector2.myY * aScalar;

	return tmpVector;
}

template<typename Type>
CU::Vector2<Type> operator/(const CU::Vector2<Type>& aVector2, Type aScalar)
{
	CU::Vector2<Type> tmpVector;

	tmpVector.myX = aVector2.myX / aScalar;
	tmpVector.myY = aVector2.myY / aScalar;

	return tmpVector;
}

template<typename Type>
void operator*=(CU::Vector2<Type>& aVector2, Type aScalar)
{
	aVector2.myX *= aScalar;
	aVector2.myY *= aScalar;
}

template<typename Type>
void operator/=(CU::Vector2<Type>& aVector2, Type aScalar)
{
	aVector2.myX /= aScalar;
	aVector2.myY /= aScalar;
}

template<typename Type>
bool operator==(const CU::Vector2<Type>& aFirstVector2, const CU::Vector2<Type>& aSecondVector2)
{
	if(aFirstVector2.x != aSecondVector2.x)
	{
		return false;
	}
	if(aFirstVector2.y != aSecondVector2.y)
	{
		return false;
	}

	return true;
}

template<typename Type>
bool operator!=(const CU::Vector2<Type>& aFirstVector2, const CU::Vector2<Type>& aSecondVector2)
{
	if(aFirstVector2.x == aSecondVector2.x && aFirstVector2.y == aSecondVector2.y)
	{
		return false;
	}

	return true;
}

template<typename Type>
float Length(const CU::Vector2<Type> &aFirstVector2)
{
	return static_cast<float>(sqrt((aFirstVector2.myX * aFirstVector2.myX) + (aFirstVector2.myY * aFirstVector2.myY)));
}

template<typename Type>
float Length2(const CU::Vector2<Type> &aFirstVector2)
{
	return static_cast<float>(Length(aFirstVector2) * Length(aFirstVector2));
}

template<typename Type>
void Normalize(CU::Vector2<Type> &aFirstVector2)
{
	Type vectorLength = static_cast<Type>(Length(aFirstVector2));
	//If we put it like this:
	//aFirstVector2.myX /= static_cast<Type>(Length(aFirstVector2));
	//myX is changed. if you write the same for the Y, the Length is already changed. so it won't actually "normalize"
	aFirstVector2.myX /= vectorLength;
	aFirstVector2.myY /= vectorLength;
}

template<typename Type>
CU::Vector2<Type> GetNormalized(const CU::Vector2<Type> &aFirstVector2)
{
	CU::Vector2<Type> tmpVector2;

	tmpVector2.myX = static_cast<Type>(aFirstVector2.myX / Length(aFirstVector2));
	tmpVector2.myY = static_cast<Type>(aFirstVector2.myY / Length(aFirstVector2));

	return tmpVector2;
}

template<typename Type>
Type Dot(const CU::Vector2<Type> &aFirstVector2, const CU::Vector2<Type> &anOtherVector2)
{
	Type dotProduct = 0;

	dotProduct += aFirstVector2.myX * anOtherVector2.myX;
	dotProduct += aFirstVector2.myY * anOtherVector2.myY;

	return dotProduct;
}

#endif