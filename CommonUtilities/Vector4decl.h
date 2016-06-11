#ifndef VECTOR4_DECL_H
#define VECTOR4_DECL_H

namespace CommonUtilities
{
	template<typename Type>
	class Vector4
	{
	public:
		Vector4();
		Vector4(Type aX, Type aY, Type aZ, Type aW);
		~Vector4();
		
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
		union	//W
		{
			Type		myW;
			Type		w;
			Type		myA;
			Type		a;
		};
	};

	template<typename Type>
	Vector4<Type>::Vector4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	template<typename Type>
	Vector4<Type>::Vector4(Type aX, Type aY, Type aZ, Type aW)
	{
		x = aX;
		y = aY;
		z = aZ;
		w = aW;
	}

	template<typename Type>
	Vector4<Type>::~Vector4()
	{

	}

	template<typename Type>
	inline void Vector4<Type>::Set(const int& aX, const int& aY, const int& aZ)
	{
		myX = aX;
		myY = aY;
		myZ = aZ;
	}

	typedef Vector4<float> Vector4f;
};

namespace CU = CommonUtilities;

#endif