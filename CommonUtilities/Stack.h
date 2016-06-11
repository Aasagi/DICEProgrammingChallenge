#ifndef STACK_H
#define STACK_H

#include "GrowingArray.h"

namespace CommonUtilities
{
	template<typename Type, typename CountType = short, unsigned short StartSize = 32>
	class Stack
	{
	public:
							Stack();
							~Stack();
		Type				Pop();
		Type				Top();
		int					Size();
		void				Push(const Type& aValue);

	private:
		GrowingArray<Type, CountType>	myData;
	};

	template<typename Type, typename CountType, unsigned short StartSize>
							Stack<Type, CountType, StartSize>::Stack()
	{
		myData.Init(StartSize);
	}

	template<typename Type, typename CountType, unsigned short StartSize>
							Stack<Type, CountType, StartSize>::~Stack()
	{
	}

	template<typename Type, typename CountType, unsigned short StartSize>
	Type					Stack<Type, CountType, StartSize>::Pop()
	{
		Type data = myData.GetLast();

		myData.RemoveCyclic(myData.GetLast());

		return data;
	}

	template<typename Type, typename CountType, unsigned short StartSize>
	Type					Stack<Type, CountType, StartSize>::Top()
	{
		return myData.GetLast();
	}

	template<typename Type, typename CountType, unsigned short StartSize>
	int						Stack<Type, CountType, StartSize>::Size()
	{
		return myData.Size();
	}

	template<typename Type, typename CountType, unsigned short StartSize>
	void					Stack<Type, CountType, StartSize>::Push(const Type& aValue)
	{
		myData.Add(aValue);
	}
};

#endif