#ifndef _MEMORY_BUCKET_H_
#define _MEMORY_BUCKET_H_

#include <assert.h>

namespace CommonUtilities
{
	class MemoryBucket
	{
	public:
		MemoryBucket(const int aStartSize);
		~MemoryBucket();

		//MemoryBucket& operator=(const MemoryBucket& aBucket);

		template<typename ObjectType>
		inline ObjectType* GetData();

		void Clear();
	private:
		char* myData;
		unsigned int myCurrAdress;
		unsigned int myStartSize;
	};

	template<typename ObjectType>
	inline ObjectType* MemoryBucket::GetData()
	{
		assert(myCurrAdress + sizeof(ObjectType) <= myStartSize && "Trying to access not allocated memory!");
		char* adress = myData + myCurrAdress;
		ObjectType* newObject = new (adress)ObjectType();
		myCurrAdress += sizeof(ObjectType);

		return newObject;
	}
}
namespace CU = CommonUtilities;
#endif