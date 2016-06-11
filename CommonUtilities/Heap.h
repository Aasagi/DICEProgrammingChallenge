#ifndef HEAP_H
#define HEAP_H

#include "GrowingArray.h"
#include "LesserPointer.h"
#include <iostream>

namespace CommonUtilities
{
	template<typename Type, typename Comparator = LesserPointer<Type>>
	class Heap
	{
	public:
								Heap		();
								Heap		(const GrowingArray<Type, int>& aGrowingArray);
								~Heap		();

		void					Enqueue		(const Type& aData);
		Type					Dequeue		();
		Type&					Top			();
		Type*					Find		(const Type& aData);
		int						Count		() const;
		int						Size		() const;
		void					DeleteAll	();

	private:
		GrowingArray<Type, int>	myData;
		Comparator				myComparator;
	};

	template<typename Type, typename Comparator>
	Heap<Type, Comparator>::Heap()
	{
		myData.Init(128);
	}

	template<typename Type, typename Comparator>
	Heap<Type, Comparator>::Heap(const GrowingArray<Type, int>& aGrowingArray)
	{
		myData = aGrowingArray;

		for(int i = (myData.Size() - 1) / 2; i >= 0; --i)
		{
			int lastPos = i * 2 + 1;

			while(lastPos <= myData.Size() - 1)
			{
				if(lastPos < (myData.Size() - 1) && Comparator(myData[lastPos], myData[lastPos + 1]))
				{
					++lastPos;
				}
				if(myData[i] < myData[lastPos])
				{
					std::swap(myData[i], myData[lastPos]);
					i = lastPos;
					lastPos = i * 2 + 1;
				}
				else
				{
					lastPos = lastPos + 1;
				}
			}
		}
	}

	template<typename Type, typename Comparator>
	Heap<Type, Comparator>::~Heap()
	{

	}

	template<typename Type, typename Comparator>
	void Heap<Type, Comparator>::Enqueue(const Type& aData)
	{
		myData.Add(aData);

		int pos = myData.Size() - 1;

		while((pos > 0) && (myComparator(myData[pos],myData[(pos - 1) / 2])))
		{
			Type data = myData[(pos - 1) / 2];
			myData[(pos - 1) / 2] = myData[pos];
			myData[pos] = data;

			pos = (pos - 1) / 2;
		}
	}

	template<typename Type, typename Comparator>
	Type Heap<Type, Comparator>::Dequeue()
	{
		//Extract the element from the root
		Type data = myData[0];

		//Put the element from the last leaf in its place
		myData[0] = myData[myData.Size() - 1];

		//Remove the last leaf
		myData.RemoveCyclicAtIndex(myData.Size() - 1);

		int pos = 0;

		while(pos < ((myData.Size() - 1) / 2) &&
			(myComparator(myData[pos * 2 + 1], myData[pos]) ||
			myComparator(myData[pos*2 + 2], myData[pos])))
		{
			if(myComparator(myData[pos * 2 + 1],myData[pos * 2 + 2]))
			{
				std::swap(myData[pos], myData[pos * 2 + 1]);
				pos = pos * 2 + 1;
			}
			else
			{
				std::swap(myData[pos], myData[pos * 2 + 2]);
				pos = pos * 2 + 2;
			}
		}

		if(myData.Size() == 2)
		{
			if(myComparator(myData[0],myData[1]))
			{
				std::swap(myData[0], myData[1]);
			}
		}

		return data;
	}

	template<typename Type, typename Comparator>
	Type& Heap<Type, Comparator>::Top()
	{
		return myData[0];
	}

	template<typename Type, typename Comparator>
	int Heap<Type, Comparator>::Size()	const
	{
		return myData.Size();
	}

	template<typename Type, typename Comparator>
	int Heap<Type, Comparator>::Count()	const
	{
		return myData.Size();
	}

	template<typename Type, typename Comparator>
	void Heap<Type, Comparator>::DeleteAll()
	{
		myData.DeleteAll();
	}
};

#endif