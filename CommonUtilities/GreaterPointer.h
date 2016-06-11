#ifndef _GREATER_POINTER_COMPARATOR_H_
#define _GREATER_POINTER_COMPARATOR_H_

namespace CommonUtilities
{
	template<typename Type>
	class GreaterPointer
	{
	public:
		GreaterPointer(){}
		~GreaterPointer(){}

		inline bool operator()(const Type& anIsThisType, const Type& aTypeToCompare) const;
	};

	template<typename Type>
	inline bool GreaterPointer<Type>::operator()(const Type& anIsThisType, const Type& aTypeToCompare) const
	{
		if(*anIsThisType > *aTypeToCompare)
		{
			return true;
		}

		return false;
	}
};

namespace CU = CommonUtilities;

#endif