#ifndef GROWING_ARRAY_H
#define GROWING_ARRAY_H

#define GROWING_ARRAY_ARGS template <typename Type, typename CountType>
#define GROWING_ARRAY_DEFS GrowingArray<Type, CountType>

#ifndef SAFE_DELETE

#define SAFE_DELETE(aData) delete aData; aData = nullptr

#endif

#ifndef SAFE_DELETE_ARR

#define SAFE_DELETE_ARR(aDataArr) delete[] aDataArr; aDataArr = nullptr

#endif

typedef unsigned int UINT;

#include <assert.h>
#include <iostream>

namespace CommonUtilities
{
	template <typename Type, typename CountType = short>
	class GrowingArray
	{
	public:
										GrowingArray					(void);
										GrowingArray					(CountType aNrOfRecommendedItems, bool anUseSafeModeFlag = true);
										GrowingArray					(const GrowingArray& aGrowingArray);
										~GrowingArray					(void);

		GrowingArray&					operator=						(const GrowingArray& aGrowingArray);
	
		void							Init							(CountType aNrOfRecomendedItems, bool anUseSafeModeFlag = true);
		void							ReInit							(CountType aNrOfRecomendedItems, bool anUseSafeModeFlag = true);

		inline Type&					operator[]						(const CountType aIndex);
		inline const Type&				operator[]						(const CountType aIndex) const;

		inline void						Add								(const Type &anObject);
		inline void						Insert							(CountType anIndex, Type &anObject);
		inline void						DeleteCyclic					(Type &anObject);
		inline void						DeleteCyclicAtIndex				(CountType anItemNumber);
		inline void						RemoveCyclic					(const Type &anObject);
		inline void						RemoveCyclicAtIndex				(CountType anItemNumber);
		inline void						RemoveSlow						(CountType aIndex);
		inline CountType				Find							(const Type &anObject);
	
		inline Type&					GetLast							(void);
		inline const Type&				GetLast							(void) const;

		static const CountType			FoundNone			=			-1;

		inline void						DeleteAll						(void);
		inline void						RemoveAll						(void);
		
		void							Optimize						(void);
		__forceinline CountType			Count							(void) const;
		__forceinline CountType			Size							(void) const;
		__forceinline bool				Empty							(void) const;

	private:

		inline void						Resize							(CountType aNewSize);
		
		bool							myInit;

		Type*							myMainData;

		CountType						myCurrSize;
		CountType						myLimitSize;

		bool							myUseSafeModeFlag;
	};

	//Default Constructor
	GROWING_ARRAY_ARGS
									GROWING_ARRAY_DEFS::GrowingArray		(void)
	{
		myInit = false;

		myMainData = nullptr;

		myCurrSize = 0;
		myLimitSize = 0;

		myUseSafeModeFlag = true;
	}

	//Constructor Overload +1
	GROWING_ARRAY_ARGS
									GROWING_ARRAY_DEFS::GrowingArray		(CountType aNrOfRecommendedItems, bool anUseSafeModeFlag)
	{
		myInit = true;
		
		myMainData = new Type[aNrOfRecommendedItems];
		
		myCurrSize = 0;
		myLimitSize = aNrOfRecommendedItems;

		myUseSafeModeFlag = anUseSafeModeFlag;
	}

	//Copy Constructor
	GROWING_ARRAY_ARGS
									GROWING_ARRAY_DEFS::GrowingArray		(const GrowingArray& aGrowingArray)
	{
		if(myUseSafeModeFlag == true)
		{
			if(myInit == true)
			{
				SAFE_DELETE_ARR(myMainData);
			}

			myInit = aGrowingArray.myInit;

			myCurrSize = aGrowingArray.myCurrSize;
			myLimitSize = aGrowingArray.myLimitSize;

			myUseSafeModeFlag = aGrowingArray.myUseSafeModeFlag;

			if(myInit == true)
			{
				myMainData = new Type[myLimitSize];
				//Copy the data to *this
				for(CountType index = 0; index < myCurrSize; ++index)
				{
					myMainData[index] = aGrowingArray.myMainData[index];
				}
			}
		}
		else
		{
			if(myInit == true)
			{
				SAFE_DELETE_ARR(myMainData);
			}

			memcpy(this, &aGrowingArray, sizeof(aGrowingArray));	//Copy the whole other class to *this
			
			//Copy constructor, which means *this hasn't used (new) syntax yet, no need to safe delete
			//Make sure it doesn't point at the same memory

			myMainData = new Type[aGrowingArray.myLimitSize];
			memcpy(myMainData, aGrowingArray.myMainData, sizeof(*myMainData) * aGrowingArray.myCurrSize);
		}
	}
	
	//Destructor
	GROWING_ARRAY_ARGS
									GROWING_ARRAY_DEFS::~GrowingArray		(void)
	{
		if(myInit == true)
		{
			//Just to be safe, delete both
			SAFE_DELETE_ARR(myMainData);
		}

		myInit = false;
		
		myCurrSize = 0;
		myLimitSize = 0;

		myUseSafeModeFlag = true;
	}

	//Operator =
	GROWING_ARRAY_ARGS
	GROWING_ARRAY_DEFS&				GROWING_ARRAY_DEFS::operator=			(const GrowingArray& aGrowingArray)
	{
		if(myUseSafeModeFlag == true)
		{
			if(myInit == true)
			{
				SAFE_DELETE_ARR(myMainData);
			}

			myInit = aGrowingArray.myInit;

			myCurrSize = aGrowingArray.myCurrSize;
			myLimitSize = aGrowingArray.myLimitSize;
		
			myUseSafeModeFlag = aGrowingArray.myUseSafeModeFlag;

			if(myInit == true)
			{
				myMainData = new Type[myLimitSize];
				//Copy the data to *this
				for(CountType index = 0; index < myCurrSize; ++index)
				{
					myMainData[index] = aGrowingArray.myMainData[index];
				}
			}
		}
		else
		{
			if(myInit == true)
			{
				SAFE_DELETE_ARR(myMainData);
			}

			memcpy(this, &aGrowingArray, sizeof(aGrowingArray));	//Copy the whole other class to *this
			
			//Copy constructor, which means *this hasn't used (new) syntax yet, no need to safe delete
			//Make sure it doesn't point at the same memory

			myMainData = new Type[aGrowingArray.myLimitSize];
			memcpy(myMainData, aGrowingArray.myMainData, sizeof(*myMainData) * aGrowingArray.myCurrSize);
		}

		return *this;
	}
	
	//Init
	GROWING_ARRAY_ARGS
	void							GROWING_ARRAY_DEFS::Init				(CountType aNrOfRecomendedItems, bool anUseSafeModeFlag)
	{
		myInit = true;
		myLimitSize = aNrOfRecomendedItems;
		myUseSafeModeFlag = anUseSafeModeFlag;
		myCurrSize = 0;
		myMainData = new Type[aNrOfRecomendedItems];
	}

	//ReInit
	GROWING_ARRAY_ARGS
	void							GROWING_ARRAY_DEFS::ReInit				(CountType aNrOfRecomendedItems, bool anUseSafeModeFlag)
	{
		assert(myInit == true && "Error, Tried to ReInit when it haven't been Init! Function: ReInit");

		SAFE_DELETE_ARR(myMainData);
		myMainData = new Type[aNrOfRecomendedItems];
		
		myCurrSize = 0;
		myLimitSize = aNrOfRecomendedItems;
		myUseSafeModeFlag = anUseSafeModeFlag;
	}

	//Operator []
	GROWING_ARRAY_ARGS
	inline Type&					GROWING_ARRAY_DEFS::operator[]			(const CountType anIndex)
	{
		assert(0 <= anIndex && anIndex < myCurrSize && "Error, Out of bounds! Function: operator[]");

		return myMainData[anIndex];
	}

	//Operator [] const
	GROWING_ARRAY_ARGS
	inline const Type&				GROWING_ARRAY_DEFS::operator[]			(const CountType anIndex) const
	{
		assert(0 <= anIndex && anIndex < myCurrSize && "Error, Out of bounds! Function: operator[] const");

		return myMainData[anIndex];
	}

	//Add
	GROWING_ARRAY_ARGS
	inline void						GROWING_ARRAY_DEFS::Add					(const Type &anObject)
	{
		assert(myInit == true && "Error, Tried to Add when it haven't been Init! Function: Add");

		++myCurrSize;

		//If myCurrSize will go over myLimitSize, create new data and remove the old
		if(myLimitSize < myCurrSize)
		{
			Resize(myLimitSize * 2);
		}

		myMainData[myCurrSize - 1] = anObject;
	}

	//Insert
	GROWING_ARRAY_ARGS
	inline void						GROWING_ARRAY_DEFS::Insert				(CountType anIndex, Type &anObject)
	{
		assert(myInit == true && "Error, Tried to Insert when it haven't been Init! Function: Insert");

		++myCurrSize;

		if(myLimitSize < myCurrSize)
		{
			Resize(myLimitSize * 2);
		}

		for(CountType index = myCurrSize - 2; anIndex <= index; --index)
		{
			myMainData[index + 1] = myMainData[index];
		}

		myMainData[anIndex] = anObject;
	}

	//Delete Cyclic
	GROWING_ARRAY_ARGS
	inline void						GROWING_ARRAY_DEFS::DeleteCyclic		(Type &anObject)
	{
		assert(myInit == true && "Error, Tried to DeleteCyclic when it haven't been Init! Function: DeleteCyclic");
		
		for(CountType i = 0; i < myCurrSize; ++i)
		{
			if(*myMainData[i] == *anObject)
			{
				SAFE_DELETE(myMainData[i]);

				--myCurrSize;

				myMainData[i] = myMainData[myCurrSize];

				myMainData[myCurrSize] = nullptr;

				break;
			}
		}
	}

	//Delete Cyclic At Index
	GROWING_ARRAY_ARGS
	inline void						GROWING_ARRAY_DEFS::DeleteCyclicAtIndex	(CountType anItemNumber)
	{
		assert(myInit == true && "Error, Tried to DeleteCyclicAtIndex when it haven't been Init! Function: DeleteCyclicAtIndex");

		assert(0 <= anItemNumber && anItemNumber < myCurrSize && "Error, Out of bounds! Function: DeleteCyclicAtIndex");
		
		--myCurrSize;

		SAFE_DELETE(myMainData[anItemNumber]);

		myMainData[anItemNumber] = myMainData[myCurrSize];
		myMainData[myCurrSize] = nullptr;
	}

	//Remove Cyclic
	GROWING_ARRAY_ARGS
	inline void						GROWING_ARRAY_DEFS::RemoveCyclic		(const Type &anObject)
	{
		assert(myInit == true && "Error, Tried to RemoveCyclic when it haven't been Init! Function: RemoveCyclic");
		
		for(CountType i = 0; i < myCurrSize; ++i)
		{
			if(myMainData[i] == anObject)
			{
				--myCurrSize;
				myMainData[i] = myMainData[myCurrSize];
				break;
			}
		}
	}

	//Remove Cyclic At Index
	GROWING_ARRAY_ARGS
	inline void						GROWING_ARRAY_DEFS::RemoveCyclicAtIndex	(CountType anItemNumber)
	{
		assert(myInit == true && "Error, Tried to RemoveCyclicAtIndex when it haven't been Init! Function: RemoveCyclicAtIndex");

		assert(0 <= anItemNumber && anItemNumber < myCurrSize && "Error, Out of bounds! RemoveCyclicAtIndex function");

		--myCurrSize;

		myMainData[anItemNumber] = myMainData[myCurrSize];
	}

	GROWING_ARRAY_ARGS
		inline void						GROWING_ARRAY_DEFS::RemoveSlow(CountType aIndex)
	{
		assert(myInit == true && "Error, Tried to RemoveSlow when it haven't been Init! Function: RemoveSlow");

		assert(0 <= aIndex && aIndex < myCurrSize && "Error, Out of bounds! RemoveSlow function");

		for(CountType i = aIndex + 1; i <= myCurrSize; ++i)
		{
			myMainData[i - 1] = myMainData[i];
		}

		--myCurrSize;
	}

	//Find
	GROWING_ARRAY_ARGS
	inline CountType				GROWING_ARRAY_DEFS::Find				(const Type &anObject)
	{
		assert(myInit == true && "Error, Tried to Find when it haven't been Init! Function: Find");

		for(CountType i = 0; i < myCurrSize; ++i)
		{
			if(myMainData[i] == anObject)
			{
				return i;
			}
		}

		return FoundNone;
	}

	//Get Last
	GROWING_ARRAY_ARGS
	inline Type&					GROWING_ARRAY_DEFS::GetLast				(void)
	{
		assert(myInit == true && "Error, Tried to GetLast when it haven't been Init! Function: GetLast");
		assert(0 <= myCurrSize && "Error, Tried to GetLast when the list is empty!");

		return myMainData[myCurrSize - 1];
	}

	//Get Last const
	GROWING_ARRAY_ARGS
	inline const Type&				GROWING_ARRAY_DEFS::GetLast				(void) const
	{
		assert(myInit == true && "Error, Tried to GetLast when it haven't been Init! Function: GetLast const");
		assert(0 <= myCurrSize && "Error, Tried to GetLast when the list is empty!");

		return myMainData[myCurrSize - 1];
	}

	//Delete all
	GROWING_ARRAY_ARGS
	inline void						GROWING_ARRAY_DEFS::DeleteAll			(void)
	{
		assert(myInit == true && "Error, Tried to DeleteAll when it haven't been Init! Function: DeleteAll");

		for(int i = myCurrSize - 1; 0 <= i; --i)
		{
			SAFE_DELETE(myMainData[i]);
		}

		myCurrSize = 0;
	}

	//Remove All
	GROWING_ARRAY_ARGS
	inline void						GROWING_ARRAY_DEFS::RemoveAll			(void)
	{
		assert(myInit == true && "Error, Tried to RemoveAll when it haven't been Init! Function: RemoveAll");

		myCurrSize = 0;
	}
	
	//Optimize
	GROWING_ARRAY_ARGS
	void							GROWING_ARRAY_DEFS::Optimize			(void)
	{
		assert(myInit == true && "Error, Tried to Optimize when it haven't been Init! Function: Optimize");

		Type* tempData = new Type[myCurrSize];

		for(CountType i = 0; i < myCurrSize; ++i)
		{
			tempData[i] = myMainData[i];
		}

		SAFE_DELETE_ARR(myMainData);
		myMainData = new Type[myCurrSize];
		for(CountType i = 0; i < myCurrSize; ++i)
		{
			myMainData[i] = tempData[i];
		}
		myLimitSize = myCurrSize;

		SAFE_DELETE_ARR(tempData);
	}

	//Count == Size
	GROWING_ARRAY_ARGS
	__forceinline CountType			GROWING_ARRAY_DEFS::Count				(void) const
	{
		return myCurrSize;
	}

	//Size == Count
	GROWING_ARRAY_ARGS
	__forceinline CountType			GROWING_ARRAY_DEFS::Size				(void) const
	{
		assert(myInit == true && "Error, Tried to Size when it haven't been Init! Function: Size");

		return myCurrSize;
	}

	//Empty
	GROWING_ARRAY_ARGS
	__forceinline bool				GROWING_ARRAY_DEFS::Empty(void) const
	{
		assert(myInit == true && "Error, Tried to Size when it haven't been Init! Function: Size");

		return myCurrSize <= 0;
	}

	//Resize
	GROWING_ARRAY_ARGS
	inline void						GROWING_ARRAY_DEFS::Resize				(CountType aNewSize)
	{
		assert(myInit == true && "Error, Tried to Resize when it haven't been Init! Function: Resize");

		Type* tempData = new Type[aNewSize];
		
		for(CountType index = 0; index < myLimitSize; ++index)
		{
			tempData[index] = myMainData[index];
		}

		SAFE_DELETE_ARR(myMainData);
		myMainData = new Type[aNewSize];
		
		for(CountType index = 0; index < myLimitSize; ++index)
		{
			myMainData[index] = tempData[index];
		}
		myLimitSize = aNewSize;

		SAFE_DELETE_ARR(tempData);
	}
};

namespace CU = CommonUtilities;

#endif