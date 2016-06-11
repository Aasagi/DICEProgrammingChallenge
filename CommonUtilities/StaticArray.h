#ifndef STATIC_ARRAY_H
#define STATIC_ARRAY_H

#define STATIC_ARRAY_TEMPLATE template <class T, unsigned int SIZE>

#include <assert.h>

namespace CommonUtilities
{
	/*****************************************************************************
							TEMPLATE DECLARATION
	*****************************************************************************/
	template <class T, unsigned int SIZE = 10>
	class StaticArray
	{
	public:
		StaticArray();
		StaticArray(const StaticArray &aStaticArray);
	
		~StaticArray();

		StaticArray& operator=(const StaticArray &aGrowingArray);
		inline const T& operator[](const int &anIndex) const;
		inline T& operator[](const int &anIndex);

		inline void Insert(int anIndex, const T& anObject);
		inline void DeleteAll();

	private:
		T myData[SIZE];
	};

	/*****************************************************************************
							CLASS FUNCTION DEFINITIONS
	*****************************************************************************/

	//Default Constructor
	STATIC_ARRAY_TEMPLATE
	StaticArray<T, SIZE>::StaticArray()
	{

	}

	//Copy Constructor
	STATIC_ARRAY_TEMPLATE
	StaticArray<T, SIZE>::StaticArray(const StaticArray &aStaticArray)
	{
		for(unsigned int i = 0; i < SIZE; ++i)
		{
			myData[i] = aStaticArray.myData[i];
		}
	}

	//Destructor
	STATIC_ARRAY_TEMPLATE
	StaticArray<T, SIZE>::~StaticArray()
	{
	}

	//Operator =
	STATIC_ARRAY_TEMPLATE
	StaticArray<T, SIZE>& StaticArray<T, SIZE>::operator=(const StaticArray &aGrowingArray)
	{
		for(unsigned int i = 0; i < SIZE; ++i)
		{
			myData[i] = aGrowingArray.myData[i];
		}

		return *this;
	}

	//Operator [] const
	STATIC_ARRAY_TEMPLATE
	inline const T& StaticArray<T, SIZE>::operator[](const int &anIndex) const
	{
		assert(0 <= anIndex && anIndex < SIZE && "Error, OUT OF BOUNDS, [] operator");

		return myData[anIndex];
	}

	//Operator []
	STATIC_ARRAY_TEMPLATE
	inline T& StaticArray<T, SIZE>::operator[](const int &anIndex)		//Can use unsigned int instead. Following the word file atm
	{
		assert(0 <= anIndex && anIndex < SIZE && "Error, OUT OF BOUNDS, [] operator");

		return myData[anIndex];
	}

	//Insert
	STATIC_ARRAY_TEMPLATE
	inline void StaticArray<T, SIZE>::Insert(int anIndex, const T &anObject)
	{
		assert(0 <= anIndex && anIndex < SIZE && "Error, OUT OF BOUNDS, Insert function");

		//-2 because we don't want to go out of bounds, touching memory we don't own
		for(int i = SIZE - 2; anIndex <= i; --i)
		{
			myData[i + 1] = myData[i];
		}
		
		myData[anIndex] = anObject;
	}

	//Delete All
	STATIC_ARRAY_TEMPLATE
	inline void StaticArray<T, SIZE>::DeleteAll()
	{
		for(unsigned int i = 0; i < SIZE; ++i)
		{
			delete myData[i];
			myData[i] = nullptr;
		}
	}
};

#endif