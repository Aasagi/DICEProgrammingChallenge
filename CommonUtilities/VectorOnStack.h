#ifndef VECTOR_ON_STACK_H
#define VECTOR_ON_STACK_H

#define VECTOR_ON_STACK_TEMPLATE		template <class T, int STACKSIZE, int HEAPADDSIZE, class COUNTTYPE, bool USESAFEMODEFLAG>
#define VECTOR_ON_STACK_DEFINITION		VectorOnStack<T, STACKSIZE, HEAPADDSIZE, COUNTTYPE, USESAFEMODEFLAG>

#ifndef SAFE_DELETE
#define SAFE_DELETE(aData)				delete aData; aData = nullptr
#endif

#ifndef SAFE_DELETE_ARR
#define SAFE_DELETE_ARR(aHeapData)		delete[] aHeapData; aHeapData = nullptr
#endif
#include <iostream>
namespace CommonUtilities
{
	/*****************************************************************************
							TEMPLATE DECLARATION
	*****************************************************************************/
	template
	<
		class T,
		int STACKSIZE = 10,
		int HEAPADDSIZE = 0,
		class COUNTTYPE = unsigned short,
		bool USESAFEMODEFLAG = true
	>
	class VectorOnStack
	{
	public:
		typedef VectorOnStack<T, STACKSIZE, HEAPADDSIZE, COUNTTYPE, USESAFEMODEFLAG> Vos;
										VectorOnStack					(void);
										VectorOnStack					(const VectorOnStack& aVectorOnStack);
										~VectorOnStack					(void);

		VectorOnStack &					operator=						(const VectorOnStack & aVectorOnStack);
	
		inline T&						operator[]						(const int &anIndex) const;
		inline T&						operator[]						(const int &anIndex);

		__forceinline COUNTTYPE			Count							(void);
		__forceinline COUNTTYPE			Size							(void);

		inline void						Add								(const T& anObject);
		inline void						Insert							(const int &anIndex, T &anObject);
		inline void						DeleteCyclic					(T& anObject);
		inline void						DeleteCyclicAtIndex				(const int &anItemNumber);
		inline void						RemoveCyclic					(const T &anObject);
		inline void						RemoveCyclicAtIndex				(const int &anItemNumber);

		inline void						DeleteAll						(void);
		inline void						RemoveAll						(void);

	protected:
		T								myStackData[STACKSIZE];
		T*								myHeapData;

		int					myStackSize;
		int					myHeapAddSize;
		COUNTTYPE						myCurrSize;
		bool							myUseSafeModeFlag;

		bool							myUsingStackData;
	};

	/*****************************************************************************
							CLASS FUNCTION DEFINITIONS
	*****************************************************************************/

	//Default constructor
	VECTOR_ON_STACK_TEMPLATE
	VECTOR_ON_STACK_DEFINITION::VectorOnStack							(void)
	{
		myHeapData = nullptr;
		
		myStackSize = STACKSIZE;
		myHeapAddSize = HEAPADDSIZE;
		myCurrSize = 0;
		myUseSafeModeFlag = USESAFEMODEFLAG;

		myUsingStackData = true;
	}

	//Copy constructor
	VECTOR_ON_STACK_TEMPLATE
	VECTOR_ON_STACK_DEFINITION::				VectorOnStack			(const VectorOnStack &aVectorOnStack)
	{
		for(int i = 0; i < aVectorOnStack.myStackSize; ++i)
		{
			myStackData[i] = aVectorOnStack.myStackData[i];
		}

		if(aVectorOnStack.myUsingStackData == false)
		{
			//Because the vectoronstack can differ, if *this already has allocated memory, delete it first
			if(myUsingStackData == false)
			{
				delete[] myHeapData;
			}

			//If it was allocated, it would be deleted. If myHeapData wasn't deleted, it's still nullptr, Thus, the new int
			myHeapData = new T[aVectorOnStack.myStackSize + aVectorOnStack.myHeapAddSize];

			for(int i = 0; i < aVectorOnStack.myStackSize + aVectorOnStack.myHeapAddSize; ++i)
			{
				myHeapData[i] = aVectorOnStack.myHeapData[i];
			}
		}

		myStackSize = aVectorOnStack.myStackSize;
		myHeapAddSize = aVectorOnStack.myHeapAddSize;
		myCurrSize = aVectorOnStack.myCurrSize;
		myUseSafeModeFlag = aVectorOnStack.myUseSafeModeFlag;

		myUsingStackData = aVectorOnStack.myUsingStackData;
	}

	//Destructor
	VECTOR_ON_STACK_TEMPLATE
	VECTOR_ON_STACK_DEFINITION::				~VectorOnStack			(void)
	{
		if(myUsingStackData == false)
		{
			SAFE_DELETE_ARR(myHeapData);
		}
	}

	//Operator =
	VECTOR_ON_STACK_TEMPLATE
	VECTOR_ON_STACK_DEFINITION& VECTOR_ON_STACK_DEFINITION::operator=	(const VectorOnStack &aVectorOnStack)
	{
		if(myUseSafeModeFlag == true)
		{
			for(int i = 0; i < myStackSize; ++i)
			{
				myStackData[i] = aVectorOnStack.myStackData[i];
			}

			if(aVectorOnStack.myUsingStackData == false)
			{
				//Because the vectoronstack can differ, if *this already has allocated memory, delete it first
				if(myUsingStackData == false)
				{
					delete[] myHeapData;
				}

				//If it was allocated, it would be deleted. If myHeapData wasn't deleted, it's still nullptr, Thus, the new int
				myHeapData = new T[aVectorOnStack.myStackSize + aVectorOnStack.myHeapAddSize];

				for(int i = 0; i < myStackSize + myHeapAddSize; ++i)
				{
					myHeapData[i] = aVectorOnStack.myHeapData[i];
				}
			}

			myStackSize = aVectorOnStack.myStackSize;
			myHeapAddSize = aVectorOnStack.myHeapAddSize;
			myCurrSize = aVectorOnStack.myCurrSize;
			myUseSafeModeFlag = aVectorOnStack.myUseSafeModeFlag;

			myUsingStackData = aVectorOnStack.myUsingStackData;
		}
		else
		{
			//*this MIGHT have used heapdata too. Delete it first or the user will have Memory Leaks
			if(myUsingStackData == false)
			{
				delete[] myHeapData;
			}

			memcpy(this, &aVectorOnStack, sizeof(aVectorOnStack));	//Copy the whole other class to this

			if(aVectorOnStack.myUsingStackData == false)
			{
				//Make sure it doesn't point at the same memory
				myHeapData = new T[aVectorOnStack.myStackSize + aVectorOnStack.myHeapAddSize];
				memcpy(myHeapData, aVectorOnStack.myHeapData, sizeof(*myHeapData) * aVectorOnStack.myCurrSize);
			}
		}

		return *this;
	}
	
	//Operator [] const
	VECTOR_ON_STACK_TEMPLATE
	inline T& VECTOR_ON_STACK_DEFINITION::		operator[]				(const int &anIndex) const
	{
		assert(0 <= anIndex && anIndex < myCurrSize && "Error, Out of bounds at operator[] const");

		if(myUsingStackData == true)
		{
			return myStackData[anIndex];
		}
		
		return myHeapData[anIndex];
	}

	//Operator []
	VECTOR_ON_STACK_TEMPLATE
	inline T& VECTOR_ON_STACK_DEFINITION::		operator[]				(const int &anIndex)
	{
		assert(0 <= anIndex && anIndex < myCurrSize && "Error, Out of bounds at operator[]");

		if(myUsingStackData == true)
		{
			return myStackData[anIndex];
		}
		
		return myHeapData[anIndex];
	}

	//Count
	VECTOR_ON_STACK_TEMPLATE
	__forceinline COUNTTYPE VECTOR_ON_STACK_DEFINITION::Count			(void)
	{
		return myCurrSize;
	}

	VECTOR_ON_STACK_TEMPLATE
	__forceinline COUNTTYPE VECTOR_ON_STACK_DEFINITION::Size			(void)
	{
		return myCurrSize;
	}

	//Add
	VECTOR_ON_STACK_TEMPLATE
	inline void VECTOR_ON_STACK_DEFINITION::	Add					(const T& anObject)
	{
		++myCurrSize;

		assert(myCurrSize <= myStackSize + myHeapAddSize && "Error, Heap is already full! Add function");
		
		if(myStackSize < myCurrSize && myUsingStackData == true)
		{
			myUsingStackData = false;

			myHeapData = new T[myStackSize + myHeapAddSize];

			for(int i = 0; i < myStackSize; ++i)
			{
				myHeapData[i] = myStackData[i];
			}
		}

		if(myUsingStackData == true)
		{
			myStackData[myCurrSize - 1] = anObject;
		}
		else
		{
			myHeapData[myCurrSize - 1] = anObject;
		}
	}

	//Insert
	VECTOR_ON_STACK_TEMPLATE
	inline void VECTOR_ON_STACK_DEFINITION::	Insert				(const int &anIndex,T& anObject)
	{
		++myCurrSize;

		assert(myCurrSize <= myStackSize + myHeapAddSize && "Error, Heap is full! Insert function");

		if(myStackSize < myCurrSize && myUsingStackData == true)
		{
			myUsingStackData = false;

			myHeapData = new T[myStackSize + myHeapAddSize];

			for(int i = 0; i < myStackSize; ++i)
			{
				myHeapData[i] = myStackData[i];
			}
		}

		//Check if it can be inserted in to the stackdata too
		if(anIndex < myStackSize)
		{
			for(int i = myStackSize - 2; anIndex <= i; --i)
			{
				myStackData[i + 1] = myStackData[i];
			}

			myStackData[anIndex] = anObject;
		}
		if(myUsingStackData == false)
		{
			//If it is using heapdata, make sure to insert it into heapdata too.
			for(int i = myStackSize + myHeapAddSize - 2; anIndex <= i; --i)
			{
				myHeapData[i + 1] = myHeapData[i];
			}

			myHeapData[anIndex] = anObject;
		}
	}

	//Delete cyclic
	VECTOR_ON_STACK_TEMPLATE
	inline void VECTOR_ON_STACK_DEFINITION::	DeleteCyclic		(T& anObject)
	{
		if(myUsingStackData == true)
		{
			for(COUNTTYPE i = 0; i < myCurrSize; ++i)
			{
				if(*myStackData[i] == *anObject)
				{
					SAFE_DELETE(myStackData[i]);

					myStackData[i] = myStackData[myCurrSize - 1];

					--myCurrSize;

					myStackData[myCurrSize] = nullptr;

					break;
				}
			}
		}
		else
		{
			for(COUNTTYPE i = 0; i < myCurrSize; ++i)
			{
				if(*myHeapData[i] == *anObject)
				{
					--myCurrSize;

					SAFE_DELETE(myStackData[i]);
					myHeapData[i] = nullptr;		//myHeapData[i] has already been deleted above, just change to nullptr
					
					if(i < myStackSize)
					{
						//If it exists in stackdata too, cyclic move in it too
						myStackData[i] = myHeapData[myCurrSize];
					}

					myHeapData[i] = myHeapData[myCurrSize];

					//Only set the last element in heapdata to nullptr, because that index doesn't exist in stackdata
					myHeapData[myCurrSize] = nullptr;

					if(myCurrSize <= myStackSize)
					{
						myUsingStackData = true;
						//Changed back to myStackData, delete the restore the memory
						SAFE_DELETE_ARR(myHeapData);
					}
					break;
				}
			}
		}
	}

	//Delete cyclic by index
	VECTOR_ON_STACK_TEMPLATE
	inline void VECTOR_ON_STACK_DEFINITION::	DeleteCyclicAtIndex	(const int &anItemNumber)
	{
		assert(0 <= anItemNumber && anItemNumber < myCurrSize && "Error, Out of bounds! DeleteCyclicAtIndex function");
		
		if(myUsingStackData == true)
		{
			--myCurrSize;

			SAFE_DELETE(myStackData[anItemNumber]);

			myStackData[anItemNumber] = myStackData[myCurrSize];
			myStackData[myCurrSize] = nullptr;
		}
		else
		{
			--myCurrSize;

			SAFE_DELETE(myHeapData[anItemNumber]);

			//If itemnumber is in the stackdata, make sure to copy the last index of heapdata to stackdata
			if(anItemNumber < myStackSize)
			{
				myStackData[anItemNumber] = myHeapData[myCurrSize];
			}

			myHeapData[anItemNumber] = myHeapData[myCurrSize];
			myHeapData[myCurrSize] = nullptr;

			if(myCurrSize <= myStackSize)
			{
				myUsingStackData = true;
				//Changed back to myStackData, delete the restore the memory
				SAFE_DELETE_ARR(myHeapData);
			}
		}
	}

	//Remove cyclic
	VECTOR_ON_STACK_TEMPLATE
	inline void VECTOR_ON_STACK_DEFINITION::	RemoveCyclic		(const T& anObject)
	{
		if(myUsingStackData == true)
		{
			for(COUNTTYPE i = 0; i < myCurrSize; ++i)
			{
				if(myStackData[i] == anObject)
				{
					--myCurrSize;
					myStackData[i] = myStackData[myCurrSize];
					break;
				}
			}
		}
		else
		{
			for(COUNTTYPE i = 0; i < myCurrSize; ++i)
			{
				if(myHeapData[i] == anObject)
				{
					--myCurrSize;
					myHeapData[i] = myHeapData[myCurrSize];

					if(i < myStackSize)		//If the item exists in stackdata, remove it there too
					{
						myStackData[i] = myHeapData[myCurrSize];
					}
					break;
				}
			}
		}

		if(myCurrSize <= myStackSize)
		{
			myUsingStackData = true;	//If total objects is at myStackSize, begin using the stack again. freeing the memory

			SAFE_DELETE_ARR(myHeapData);
		}
	}

	//Remove cyclic by index
	VECTOR_ON_STACK_TEMPLATE
	inline void VECTOR_ON_STACK_DEFINITION::	RemoveCyclicAtIndex	(const int &anItemNumber)
	{
		assert(0 <= anItemNumber && anItemNumber < myCurrSize && "Error, Out of bounds! RemoveCyclicAtIndex function");
		
		--myCurrSize;

		if(myUsingStackData == true)
		{
			myStackData[anItemNumber] = myStackData[myCurrSize];
		}
		else
		{
			myHeapData[anItemNumber] = myHeapData[myCurrSize];

			if(anItemNumber < myStackSize)	//If the itemnumber exists in the stackdata, remove it there too
			{
				myStackData[anItemNumber] = myHeapData[myCurrSize];
			}
		}

		if(myCurrSize <= myStackSize)
		{
			myUsingStackData = true;	//If total objects is at myStackSize, begin using the stack again. freeing the memory

			SAFE_DELETE_ARR(myHeapData);
		}
	}

	//Delete all
	VECTOR_ON_STACK_TEMPLATE
	inline void VECTOR_ON_STACK_DEFINITION::	DeleteAll			(void)
	{
		if(myUsingStackData == true)
		{
			for(int i = myCurrSize - 1; 0 <= i; --i)
			{
				SAFE_DELETE(myStackData[i]);
			}
		}
		else
		{
			for(int i = myStackSize - 1; 0 <= i; --i)
			{
				SAFE_DELETE(myStackData[i]);
			}
			for(int i = myCurrSize - 1; myStackSize < i; --i)
			{
				SAFE_DELETE(myHeapData[i]);
			}
			for(int i = myStackSize - 1; 0 <= i; --i)
			{
				myHeapData[i] = nullptr;	

			}

			SAFE_DELETE_ARR(myHeapData);
		}

		myCurrSize = 0;
		myUsingStackData = true;
	}

	//Remove all
	VECTOR_ON_STACK_TEMPLATE
	inline void VECTOR_ON_STACK_DEFINITION::	RemoveAll			(void)
	{
		if(myUsingStackData == false)
		{
			//If he used heapdata, delete it
			SAFE_DELETE_ARR(myHeapData);
		}

		myCurrSize = 0;
		myUsingStackData = true;
	}
};

#endif