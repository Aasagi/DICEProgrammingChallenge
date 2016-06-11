#ifndef _MEMORY_CONTAINER_H_
#define _MEMORY_CONTAINER_H_

#include "StaticArray.h"
#include "VectorOnStack.h"
#include "DL_Assert.h"
namespace CommonUtilities
{
	template<typename Type, int MaxNrOfObjects = 10>
	class MemoryContainer
	{
	public:
		MemoryContainer();
		~MemoryContainer();

		Type* AddObject(const Type& aType);
		Type* AddEmptyObject();
		void RemoveObject(const int aIndex);
		void RemoveObject(Type& aType);
		const Type& GetObjectA(const int aIndex) const;
		Type& GetObjectA(const int aIndex);
		int Count();

	private:
		Type* GetAvailabeObject();
		void MakeAvailable(Type* aObject);

		StaticArray<Type, MaxNrOfObjects> myObjects;
		VectorOnStack<int, MaxNrOfObjects> myAvailable;

	};

	template<typename Type, int MaxNrOfObjects>
	MemoryContainer<Type, MaxNrOfObjects>::MemoryContainer()
	{
		for(int i = MaxNrOfObjects - 1; i >= 0; --i)
		{
			myAvailable.Add(i);
			myObjects[i] = Type();
		}
	}

	template<typename Type, int MaxNrOfObjects>
	MemoryContainer<Type, MaxNrOfObjects>::~MemoryContainer()
	{

	}

	template<typename Type, int MaxNrOfObjects>
	Type* MemoryContainer<Type, MaxNrOfObjects>::AddObject(const Type& aType)
	{
		assert(myAvailable.Count() > 0 && "Ran out of memory!");

		myObjects[myAvailable.GetLast()] = aType;
		Type* newObject = &myObjects[myAvailable.GetLast()];
		myAvailable.RemoveCyclic(myAvailable.GetLast());

		return newObject;
	}

	template<typename Type, int MaxNrOfObjects>
	Type* MemoryContainer<Type, MaxNrOfObjects>::AddEmptyObject()
	{
		assert(myAvailable.Count() > 0 && "Ran out of memory!");

		Type* newObject = GetAvailabeObject();

		return newObject;
	}

	template<typename Type, int MaxNrOfObjects>
	void MemoryContainer<Type, MaxNrOfObjects>::RemoveObject(const int aIndex)
	{
#ifdef _DEBUG
		for(int i = 0; i < myAvailable.Size(); ++i)
		{
			assert(aIndex != myAvailable[i] && "Index already exists!");
		}
#endif
		myAvailable.Add(aIndex);
	}

	template<typename Type, int MaxNrOfObjects>
	void MemoryContainer<Type, MaxNrOfObjects>::RemoveObject(Type& aType)
	{
		MakeAvailable(&aType);
	}

	template<typename Type, int MaxNrOfObjects>
	const Type& MemoryContainer<Type, MaxNrOfObjects>::GetObjectA(const int aIndex) const
	{
#ifdef _DEBUG
		for(int i = 0; i < myAvailable.Count(); ++i)
		{
			assert(aIndex != myAvailable[i] && "Tried to get an object that doesn't exist!");
		}
#endif
		return myObjects[aIndex];
	}

	template<typename Type, int MaxNrOfObjects>
	Type& MemoryContainer<Type, MaxNrOfObjects>::GetObjectA(const int aIndex)
	{
#ifdef _DEBUG
		for(int i = 0; i < myAvailable.Count(); ++i)
		{
			assert(aIndex != myAvailable[i] && "Tried to get an object that doesn't exist!");
		}
#endif
		return myObjects[aIndex];
	}

	template<typename Type, int MaxNrOfObjects>
	int MemoryContainer<Type, MaxNrOfObjects>::Count()
	{
		return MaxNrOfObjects - myAvailable.Count();
	}

	template<typename Type, int MaxNrOfObjects>
	Type* MemoryContainer<Type, MaxNrOfObjects>::GetAvailabeObject()
	{
		int index = myAvailable.GetLast();
		myAvailable.RemoveCyclic(myAvailable.GetLast());
		return &myObjects[index];
	}

	template<typename Type, int MaxNrOfObjects>
	void MemoryContainer<Type, MaxNrOfObjects>::MakeAvailable(Type* aObject)
	{
		int index = aObject - &myObjects[0];
		assert(MaxNrOfObjects > index && "Lol it didn't work");
		myAvailable.Add(aObject - &myObjects[0]);
	}

}

namespace CU = CommonUtilities;
#endif