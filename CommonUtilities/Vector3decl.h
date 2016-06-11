#ifndef VECTOR3_DECL_H
#define VECTOR3_DECL_H

namespace CommonUtilities
{
	template<typename Type>
	class Vector3
	{
	public:
		Vector3			();
		Vector3			(Type aX, Type aY, Type aZ);
		~Vector3		();

		Type			operator[](const short& anIndex);

		inline void Set(const int& aX, const int& aY, const int& aZ);

		union	//X
		{
			Type		myX;
			Type		x;
			Type		myR;
			Type		r;
		};
		union	//Y
		{
			Type		myY;
			Type		y;
			Type		myG;
			Type		g;
		};
		union	//Z
		{
			Type		myZ;
			Type		z;
			Type		myB;
			Type		b;
		};
	};

	template<typename Type>
	Vector3<Type>::Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	template<typename Type>
	Vector3<Type>::Vector3(Type aX, Type aY, Type aZ)
	{
		x = aX;
		y = aY;
		z = aZ;
	}

	template<typename Type>
	Vector3<Type>::~Vector3()
	{

	}

	template<typename Type>
	inline void Vector3<Type>::Set(const int& aX, const int& aY, const int& aZ)
	{
		myX = aX;
		myY = aY;
		myZ = aZ;
	}

	typedef Vector3<float> Vector3f;
};

namespace CU = CommonUtilities;

#endif