#ifndef VECTOR3_H
#define VECTOR3_H

#include "Vector3decl.h"

template<typename Type>
Type							CU::Vector3<Type>::operator[]		(const short& anIndex)
{
	switch(anIndex)
	{
	case 0:
		return myX;
		break;
	case 1:
		return myY;
		break;
	case 2:
		return myZ;
		break;
	}
}

template<typename Type>
CU::Vector3<Type>				operator+		(const CU::Vector3<Type>& aFirstVector3, const CU::Vector3<Type>& aSecondVector3)
{
	CU::Vector3<Type> tmpVector;

	tmpVector.myX = aFirstVector3.myX + aSecondVector3.myX;
	tmpVector.myY = aFirstVector3.myY + aSecondVector3.myY;
	tmpVector.myZ = aFirstVector3.myZ + aSecondVector3.myZ;

	return tmpVector;
}

template<typename Type>
CU::Vector3<Type>				operator-		(const CU::Vector3<Type>& aFirstVector3, const CU::Vector3<Type>& aSecondVector3)
{
	CU::Vector3<Type> tmpVector;

	tmpVector.myX = aFirstVector3.myX - aSecondVector3.myX;
	tmpVector.myY = aFirstVector3.myY - aSecondVector3.myY;
	tmpVector.myZ = aFirstVector3.myZ - aSecondVector3.myZ;

	return tmpVector;
}

template<typename Type>
CU::Vector3<Type>				operator*		(const CU::Vector3<Type>& aFirstVector3, const CU::Vector3<Type>& aSecondVector3)
{
	CU::Vector3<Type> tmpVector;

	tmpVector.myX = aFirstVector3.myX * aSecondVector3.myX;
	tmpVector.myY = aFirstVector3.myY * aSecondVector3.myY;
	tmpVector.myZ = aFirstVector3.myZ * aSecondVector3.myZ;

	return tmpVector;
}

template<typename Type>
CU::Vector3<Type>				operator/		(const CU::Vector3<Type>& aFirstVector3, const CU::Vector3<Type>& aSecondVector3)
{
	CU::Vector3<Type> tmpVector;

	tmpVector.myX = aFirstVector3.myX / aSecondVector3.myX;
	tmpVector.myY = aFirstVector3.myY / aSecondVector3.myY;
	tmpVector.myZ = aFirstVector3.myZ / aSecondVector3.myZ;

	return tmpVector;
}

template<typename Type>
void							operator+=		(CU::Vector3<Type>& aFirstVector3, const CU::Vector3<Type>& aSecondVector3)
{
	aFirstVector3.myX += aSecondVector3.myX;
	aFirstVector3.myY += aSecondVector3.myY;
	aFirstVector3.myZ += aSecondVector3.myZ;
}

template<typename Type>
void							operator-=		(CU::Vector3<Type>& aFirstVector3, const CU::Vector3<Type>& aSecondVector3)
{
	aFirstVector3.myX -= aSecondVector3.myX;
	aFirstVector3.myY -= aSecondVector3.myY;
	aFirstVector3.myZ -= aSecondVector3.myZ;
}

template<typename Type>
void							operator*=		(CU::Vector3<Type>& aFirstVector3, const CU::Vector3<Type>& aSecondVector3)
{
	aFirstVector3.myX *= aSecondVector3.myX;
	aFirstVector3.myY *= aSecondVector3.myY;
	aFirstVector3.myZ *= aSecondVector3.myZ;
}

template<typename Type>
void							operator/=		(CU::Vector3<Type>& aFirstVector3, const CU::Vector3<Type>& aSecondVector3)
{
	aFirstVector3.myX /= aSecondVector3.myX;
	aFirstVector3.myY /= aSecondVector3.myY;
	aFirstVector3.myZ /= aSecondVector3.myZ;
}

template<typename Type>
CU::Vector3<Type>				operator*		(const CU::Vector3<Type>& aVector3, Type aScalar)
{
	CU::Vector3<Type> tmpVector;

	tmpVector.myX = aVector3.myX * aScalar;
	tmpVector.myY = aVector3.myY * aScalar;
	tmpVector.myZ = aVector3.myZ * aScalar;

	return tmpVector;
}

template<typename Type>
CU::Vector3<Type>				operator/		(const CU::Vector3<Type>& aVector3, Type aScalar)
{
	CU::Vector3<Type> tmpVector;
	
	tmpVector.myX = aVector3.myX / aScalar;
	tmpVector.myY = aVector3.myY / aScalar;
	tmpVector.myZ = aVector3.myZ / aScalar;

	return tmpVector;
}

template<typename Type>
void							operator*=		(CU::Vector3<Type>& aVector3, Type aScalar)
{
	aVector3.myX *= aScalar;
	aVector3.myY *= aScalar;
	aVector3.myZ *= aScalar;
}

template<typename Type>
void							operator/=		(CU::Vector3<Type>& aVector3, Type aScalar)
{
	aVector3.myX /= aScalar;
	aVector3.myY /= aScalar;
	aVector3.myZ /= aScalar;
}

template<typename Type>
bool							operator==		(const CU::Vector3<Type>& aFirstVector3, const CU::Vector3<Type>& aSecondVector3)
{
	if(aFirstVector3.x != aSecondVector3.x)
	{
		return false;
	}
	if(aFirstVector3.y != aSecondVector3.y)
	{
		return false;
	}
	if(aFirstVector3.z != aSecondVector3.z)
	{
		return false;
	}

	return true;
}

template<typename Type>
bool							operator!=		(const CU::Vector3<Type>& aFirstVector3, const CU::Vector3<Type>& aSecondVector3)
{
	if(aFirstVector3.x == aSecondVector3.x)
	{
		return false;
	}
	if(aFirstVector3.y == aSecondVector3.y)
	{
		return false;
	}
	if(aFirstVector3.z == aSecondVector3.z)
	{
		return false;
	}

	return true;
}

template<typename Type>
float							Length			(const CU::Vector3<Type> &aVector3)
{
	return static_cast<float>(sqrt
		(
		(aVector3.myX * aVector3.myX) + (aVector3.myY * aVector3.myY) + 
		(aVector3.myZ * aVector3.myZ)
		));
}

template<typename Type>
float							Length2			(const CU::Vector3<Type> &aVector3)
{
	return static_cast<float>(Length(aVector3) * Length(aVector3));
}

template<typename Type>
void							Normalize		(CU::Vector3<Type> &aVector3)
{
	Type vectorLength = static_cast<Type>(Length(aVector3));

	aVector3.myX /= vectorLength;
	aVector3.myY /= vectorLength;
	aVector3.myZ /= vectorLength;
}

template<typename Type>
CU::Vector3<Type>				GetNormalized	(const CU::Vector3<Type> &aVector3)
{
	CU::Vector3<Type> tmpVector3;
	
	tmpVector3.myX = aVector3.myX / Length(aVector3);
	tmpVector3.myY = aVector3.myY / Length(aVector3);
	tmpVector3.myZ = aVector3.myZ / Length(aVector3);

	return tmpVector3;
}

template<typename Type>
Type							Dot				(const CU::Vector3<Type> &aVector3, const CU::Vector3<Type> &anOtherVector3)
{
	Type dotProduct = 0;

	dotProduct += aVector3.myX * anOtherVector3.myX;
	dotProduct += aVector3.myY * anOtherVector3.myY;
	dotProduct += aVector3.myZ * anOtherVector3.myZ;

	return dotProduct;
}

template<typename Type>
CU::Vector3<Type>				Cross			(const CU::Vector3<Type> &aVector3, const CU::Vector3<Type> &anOtherVector3)
{
	CU::Vector3<Type> crossProduct;
		
	crossProduct.myX = 0;
	crossProduct.myY = 0;
	crossProduct.myZ = 0;

	crossProduct.myX += aVector3.myY * anOtherVector3.myZ - aVector3.myZ * anOtherVector3.myY;
	crossProduct.myY += aVector3.myZ * anOtherVector3.myX - aVector3.myX * anOtherVector3.myZ;
	crossProduct.myZ += aVector3.myX * anOtherVector3.myY - aVector3.myY * anOtherVector3.myX;

	return crossProduct;
}

#endif