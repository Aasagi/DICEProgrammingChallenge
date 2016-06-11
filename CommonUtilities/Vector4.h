#ifndef VECTOR4_H
#define VECTOR4_H

#include "Vector4decl.h"

template<typename Type>
CU::Vector4<Type>			operator+		(const CU::Vector4<Type>& aFirstVector4, const CU::Vector4<Type>& aSecondVector4)
{
	CU::Vector4<Type> tmpVector;

	tmpVector.myX = aFirstVector4.myX + aSecondVector4.myX;
	tmpVector.myY = aFirstVector4.myY + aSecondVector4.myY;
	tmpVector.myZ = aFirstVector4.myZ + aSecondVector4.myZ;
	tmpVector.myW = aFirstVector4.myW + aSecondVector4.myW;

	return tmpVector;
}

template<typename Type>
CU::Vector4<Type>			operator-		(const CU::Vector4<Type>& aFirstVector4, const CU::Vector4<Type>& aSecondVector4)
{
	CU::Vector4<Type> tmpVector;

	tmpVector.myX = aFirstVector4.myX - aSecondVector4.myX;
	tmpVector.myY = aFirstVector4.myY - aSecondVector4.myY;
	tmpVector.myZ = aFirstVector4.myZ - aSecondVector4.myZ;
	tmpVector.myW = aFirstVector4.myW - aSecondVector4.myW;

	return tmpVector;
}

template<typename Type>
CU::Vector4<Type>			operator*		(const CU::Vector4<Type>& aFirstVector4, const CU::Vector4<Type>& aSecondVector4)
{
	CU::Vector4<Type> tmpVector;

	tmpVector.myX = aFirstVector4.myX * aSecondVector4.myX;
	tmpVector.myY = aFirstVector4.myY * aSecondVector4.myY;
	tmpVector.myZ = aFirstVector4.myZ * aSecondVector4.myZ;
	tmpVector.myW = aFirstVector4.myW * aSecondVector4.myW;

	return tmpVector;
}

template<typename Type>
CU::Vector4<Type>			operator/		(const CU::Vector4<Type>& aFirstVector4, const CU::Vector4<Type>& aSecondVector4)
{
	CU::Vector4<Type> tmpVector;

	tmpVector.myX = aFirstVector4.myX / aSecondVector4.myX;
	tmpVector.myY = aFirstVector4.myY / aSecondVector4.myY;
	tmpVector.myZ = aFirstVector4.myZ / aSecondVector4.myZ;
	tmpVector.myW = aFirstVector4.myW / aSecondVector4.myW;

	return tmpVector;
}

template<typename Type>
void						operator+=		(CU::Vector4<Type>& aFirstVector4, const CU::Vector4<Type>& aSecondVector4)
{
	aFirstVector4.myX += aSecondVector4.myX;
	aFirstVector4.myY += aSecondVector4.myY;
	aFirstVector4.myZ += aSecondVector4.myZ;
	aFirstVector4.myW += aSecondVector4.myW;
}

template<typename Type>
void						operator-=		(CU::Vector4<Type>& aFirstVector4, const CU::Vector4<Type>& aSecondVector4)
{
	aFirstVector4.myX -= aSecondVector4.myX;
	aFirstVector4.myY -= aSecondVector4.myY;
	aFirstVector4.myZ -= aSecondVector4.myZ;
	aFirstVector4.myW -= aSecondVector4.myW;
}

template<typename Type>
void						operator*=		(CU::Vector4<Type>& aFirstVector4, const CU::Vector4<Type>& aSecondVector4)
{
	aFirstVector4.myX *= aSecondVector4.myX;
	aFirstVector4.myY *= aSecondVector4.myY;
	aFirstVector4.myZ *= aSecondVector4.myZ;
	aFirstVector4.myW *= aSecondVector4.myW;
}

template<typename Type>
void						operator/=		(CU::Vector4<Type>& aFirstVector4, const CU::Vector4<Type>& aSecondVector4)
{
	aFirstVector4.myX /= aSecondVector4.myX;
	aFirstVector4.myY /= aSecondVector4.myY;
	aFirstVector4.myZ /= aSecondVector4.myZ;
	aFirstVector4.myW /= aSecondVector4.myW;
}

template<typename Type>
CU::Vector4<Type>			operator*		(const CU::Vector4<Type>& aVector4, Type aScalar)
{
	CU::Vector4<Type> tmpVector;

	tmpVector.myX = aVector4.myX * aScalar;
	tmpVector.myY = aVector4.myY * aScalar;
	tmpVector.myZ = aVector4.myZ * aScalar;
	tmpVector.myW = aVector4.myW * aScalar;

	return tmpVector;
}

template<typename Type>
CU::Vector4<Type>			operator/		(const CU::Vector4<Type>& aVector4, Type aScalar)
{
	CU::Vector4<Type> tmpVector;
	
	tmpVector.myX = aVector4.myX / aScalar;
	tmpVector.myY = aVector4.myY / aScalar;
	tmpVector.myZ = aVector4.myZ / aScalar;
	tmpVector.myW = aVector4.myW / aScalar;

	return tmpVector;
}

template<typename Type>
void						operator*=		(CU::Vector4<Type>& aVector4, Type aScalar)
{
	aVector4.myX *= aScalar;
	aVector4.myY *= aScalar;
	aVector4.myZ *= aScalar;
	aVector4.myW *= aScalar;
}

template<typename Type>
void						operator/=		(CU::Vector4<Type>& aVector4, Type aScalar)
{
	aVector4.myX /= aScalar;
	aVector4.myY /= aScalar;
	aVector4.myZ /= aScalar;
	aVector4.myW /= aScalar;
}

template<typename Type>
bool						operator==		(const CU::Vector4<Type>& aFirstVector4, const CU::Vector4<Type>& aSecondVector4)
{
	if(aFirstVector4.x != aSecondVector4.x)
	{
		return false;
	}
	if(aFirstVector4.y != aSecondVector4.y)
	{
		return false;
	}
	if(aFirstVector4.z != aSecondVector4.z)
	{
		return false;
	}
	if(aFirstVector4.w != aSecondVector4.w)
	{
		return false;
	}

	return true;
}

template<typename Type>
bool						operator!=		(const CU::Vector4<Type>& aFirstVector4, const CU::Vector4<Type>& aSecondVector4)
{
	if(aFirstVector4.x == aSecondVector4.x)
	{
		return false;
	}
	if(aFirstVector4.y == aSecondVector4.y)
	{
		return false;
	}
	if(aFirstVector4.z == aSecondVector4.z)
	{
		return false;
	}
	if(aFirstVector4.w == aSecondVector4.w)
	{
		return false;
	}

	return true;
}

//template<typename Type>
//										CU::Vector4<Type>::Vector4()
//{
//	x = 0;
//	y = 0;
//	z = 0;
//	w = 0;
//}
//
//template<typename Type>
//										CU::Vector4<Type>::Vector4(Type aX, Type aY, Type aZ, Type aW)
//{
//	x = aX;
//	y = aY;
//	z = aZ;
//	w = aW;
//}
//
//template<typename Type>
//										CU::Vector4<Type>::~Vector4()
//{
//
//}
//
//template<typename Type>
//CU::Vector4<Type>			CU::Vector4<Type>::operator+		(const CU::Vector4<Type>& aVector4)
//{
//	CU::Vector4<Type> tmpVector;
//
//	tmpVector.myX = myX + aVector4.myX;
//	tmpVector.myY = myY + aVector4.myY;
//	tmpVector.myZ = myZ + aVector4.myZ;
//	tmpVector.myW = myW + aVector4.myW;
//
//	return tmpVector;
//}
//
//template<typename Type>
//CU::Vector4<Type>			CU::Vector4<Type>::operator-		(const CU::Vector4<Type>& aVector4)
//{
//	CU::Vector4<Type> tmpVector;
//
//	tmpVector.myX = myX - aVector4.myX;
//	tmpVector.myY = myY - aVector4.myY;
//	tmpVector.myZ = myZ - aVector4.myZ;
//	tmpVector.myW = myW - aVector4.myW;
//
//	return tmpVector;
//}
//
//template<typename Type>
//CU::Vector4<Type>			CU::Vector4<Type>::operator-		()
//{
//	CU::Vector4<Type> tmpVector;
//
//	tmpVector.myX = -myX;
//	tmpVector.myY = -myY;
//	tmpVector.myZ = -myZ;
//	tmpVector.myW = -myW;
//
//	return tmpVector;
//}
//
//template<typename Type>
//CU::Vector4<Type>			CU::Vector4<Type>::operator*		(const CU::Vector4<Type>& aVector4)
//{
//	CU::Vector4<Type> tmpVector;
//
//	tmpVector.myX = myX * aVector4.myX;
//	tmpVector.myY = myY * aVector4.myY;
//	tmpVector.myZ = myZ * aVector4.myZ;
//	tmpVector.myW = myW * aVector4.myW;
//
//	return tmpVector;
//}
//
//template<typename Type>
//CU::Vector4<Type>			CU::Vector4<Type>::operator/		(const CU::Vector4<Type>& aVector4)
//{
//	CU::Vector4<Type> tmpVector;
//
//	tmpVector.myX = myX / aVector4.myX;
//	tmpVector.myY = myY / aVector4.myY;
//	tmpVector.myZ = myZ / aVector4.myZ;
//	tmpVector.myW = myW / aVector4.myW;
//
//	return tmpVector;
//}
//
//template<typename Type>
//CU::Vector4<Type>&			CU::Vector4<Type>::operator+=		(const CU::Vector4<Type>& aVector4)
//{
//	myX += aVector4.myX;
//	myY += aVector4.myY;
//	myZ += aVector4.myZ;
//	myW += aVector4.myW;
//
//	return *this;
//}
//
//template<typename Type>
//CU::Vector4<Type>&			CU::Vector4<Type>::operator-=		(const CU::Vector4<Type>& aVector4)
//{
//	myX -= aVector4.myX;
//	myY -= aVector4.myY;
//	myZ -= aVector4.myZ;
//	myW -= aVector4.myW;
//
//	return *this;
//}
//
//template<typename Type>
//CU::Vector4<Type>&			CU::Vector4<Type>::operator*=		(const CU::Vector4<Type>& aVector4)
//{
//	myX *= aVector4.myX;
//	myY *= aVector4.myY;
//	myZ *= aVector4.myZ;
//	myW *= aVector4.myW;
//
//	return *this;
//}
//
//template<typename Type>
//CU::Vector4<Type>&			CU::Vector4<Type>::operator/=		(const CU::Vector4<Type>& aVector4)
//{
//	myX /= aVector4.myX;
//	myY /= aVector4.myY;
//	myZ /= aVector4.myZ;
//	myW /= aVector4.myW;
//
//	return *this;
//}
//
//template<typename Type>
//CU::Vector4<Type>			CU::Vector4<Type>::operator*		(Type aScalar)
//{
//	CU::Vector4<Type> tmpVector;
//
//	tmpVector.myX = myX * aScalar;
//	tmpVector.myY = myY * aScalar;
//	tmpVector.myZ = myZ * aScalar;
//	tmpVector.myW = myW * aScalar;
//
//	return tmpVector;
//}
//
//template<typename Type>
//CU::Vector4<Type>			CU::Vector4<Type>::operator/		(Type aScalar)
//{
//	CU::Vector4<Type> tmpVector;
//	
//	tmpVector.myX = myX / aScalar;
//	tmpVector.myY = myY / aScalar;
//	tmpVector.myZ = myZ / aScalar;
//	tmpVector.myW = myW / aScalar;
//
//	return tmpVector;
//}
//
//template<typename Type>
//CU::Vector4<Type>&			CU::Vector4<Type>::operator*=		(Type aScalar)
//{
//	myX *= aScalar;
//	myY *= aScalar;
//	myZ *= aScalar;
//	myW *= aScalar;
//
//	return *this;
//}
//
//template<typename Type>
//CU::Vector4<Type>&			CU::Vector4<Type>::operator/=		(Type aScalar)
//{
//	myX /= aScalar;
//	myY /= aScalar;
//	myZ /= aScalar;
//	myW /= aScalar;
//
//	return *this;
//}
//
//template<typename Type>
//bool			CU::Vector4<Type>::operator==		(const Vector4& aVector4)
//{
//	if(myX != aVector4.myX)
//	{
//		return false;
//	}
//	if(myY != aVector4.myY)
//	{
//		return false;
//	}
//	if(myZ != aVector4.myZ)
//	{
//		return false;
//	}
//	if(myW != aVector4.myW)
//	{
//		return false;
//	}
//
//	return true;
//}
//
//template<typename Type>
//bool			CU::Vector4<Type>::operator!=		(const Vector4& aVector4)
//{
//	if(myX == aVector4.myX)
//	{
//		return false;
//	}
//	if(myY == aVector4.myY)
//	{
//		return false;
//	}
//	if(myZ == aVector4.myZ)
//	{
//		return false;
//	}
//	if(myW == aVector4.myW)
//	{
//		return false;
//	}
//
//	return true;
//}

template<typename Type>
void						Abs				()
{
	myX = abs(myX);
	myY = abs(myY);
	myZ = abs(myZ);
	myW = abs(myW);
}

template<typename Type>
float						Length			(const CU::Vector4<Type> &aVector4)
{
	return static_cast<float>(sqrt
		(
		(aVector4.myX * aVector4.myX) + (aVector4.myY * aVector4.myY) +
		(aVector4.myZ * aVector4.myZ) + (aVector4.myW * aVector4.myW)
		));
}

template<typename Type>
float						Length2			(const CU::Vector4<Type> &aVector4)
{
	return static_cast<float>(Length(aVector4) * Length(aVector4));
}

template<typename Type>
void						Normalize		(CU::Vector4<Type> &aVector4)
{
	Type vectorLength = static_cast<Type>(Length(aVector4));

	aVector4.myX /= vectorLength;
	aVector4.myY /= vectorLength;
	aVector4.myZ /= vectorLength;
	aVector4.myW /= vectorLength;
}

template<typename Type>
CU::Vector4<Type>			GetNormalized	(const CU::Vector4<Type> &aVector4)
{
	CU::Vector4<Type> tmpVector4;

	tmpVector4.myX = aVector4.myX / Length(aVector4);
	tmpVector4.myY = aVector4.myY / Length(aVector4);
	tmpVector4.myZ = aVector4.myZ / Length(aVector4);
	tmpVector4.myW = aVector4.myW / Length(aVector4);

	return tmpVector4;
}

template<typename Type>
Type						Dot				(const CU::Vector4<Type> &aVector4, const CU::Vector4<Type> &anOtherVector4)
{
	Type dotProduct = 0;

	dotProduct += aVector4.myX * anOtherVector4.myX;
	dotProduct += aVector4.myY * anOtherVector4.myY;
	dotProduct += aVector4.myZ * anOtherVector4.myZ;
	dotProduct += aVector4.myW * anOtherVector4.myW;

	return dotProduct;
}

template<typename Type>
void						Abs				(CU::Vector4<Type> &aVector4)
{
	aVector4.myX = abs(aVector4.myX);
	aVector4.myY = abs(aVector4.myY);
	aVector4.myZ = abs(aVector4.myZ);
	aVector4.myW = abs(aVector4.myW);
}

#endif