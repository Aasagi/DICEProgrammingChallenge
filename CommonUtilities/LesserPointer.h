#ifndef _LESSER_POINTER_COMPARATOR_H_
#define _LESSER_POINTER_COMPARATOR_H_

namespace CommonUtilities
{
	template<typename Type>
	class LesserPointer
	{
	public:
		LesserPointer(){}
		~LesserPointer(){}

		inline bool operator()(const Type& anIsThisType, const Type& aTypeToCompare) const;
	};

	template<typename Type>
	inline bool LesserPointer<Type>::operator()(const Type& anIsThisType, const Type& aTypeToCompare) const
	{
		if(*anIsThisType < *aTypeToCompare)
		{
			return true;
		}

		return false;
	}
};

namespace CU = CommonUtilities;

#endif