#ifndef VECTOR2_DECL_H
#define VECTOR2_DECL_H

namespace CommonUtilities
{
	template<typename Type>
	class Vector2
	{
	public:
		Vector2();
		Vector2(Type aX, Type aY);
		~Vector2();

		inline Type& operator[](const short anIndex);
		inline const Type& operator[](const short anIndex) const;
		inline void Set(const Type& aX, const Type& aY);

		union	//X
		{
			Type		myX;
			Type		x;
			Type		myU;
			Type		u;
		};
		union	//Y
		{
			Type		myY;
			Type		y;
			Type		myV;
			Type		V;
		};
	};

	template<typename Type>
	Vector2<Type>::Vector2()
	{
		x = 0;
		y = 0;
	}

	template<typename Type>
	Vector2<Type>::Vector2(Type aX, Type aY)
	{
		x = aX;
		y = aY;
	}

	template<typename Type>
	Vector2<Type>::~Vector2()
	{

	}

	template<typename Type>
	inline Type& Vector2<Type>::operator[](const short anIndex)
	{
		switch(anIndex)
		{
		case 0:
			return myX;
			break;
		case 1:
			return myY;
			break;
		}

		return myX;
	}

	template<typename Type>
	inline const Type& Vector2<Type>::operator[](const short anIndex) const
	{
		switch(anIndex)
		{
		case 0:
			return myX;
			break;
		case 1:
			return myY;
			break;
		}

		return myX;
	}

	template<typename Type>
	inline void Vector2<Type>::Set(const Type& aX, const Type& aY)
	{
		myX = aX;
		myY = aY;
	}

	typedef Vector2<float> Vector2f;
	typedef Vector2<int> Vector2i;
};

namespace CU = CommonUtilities;

#endif