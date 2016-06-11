#ifndef DOUBLE_LINKED_LIST_NODE_H
#define DOUBLE_LINKED_LIST_NODE_H

#ifndef SAFE_DELETE
#define SAFE_DELETE(aValue) delete aValue; aValue = nullptr;
#endif

namespace CommonUtilities
{
	template<typename Type>
	struct DoubleLinkedListNode
	{
	public:
		DoubleLinkedListNode();
		DoubleLinkedListNode(const Type& aData);
		DoubleLinkedListNode(DoubleLinkedListNode* aPrevNode, DoubleLinkedListNode* aNextNode, Type& aData);
		DoubleLinkedListNode(DoubleLinkedListNode* aNode);
		~DoubleLinkedListNode();
		DoubleLinkedListNode*				myPrevNode;
		DoubleLinkedListNode*				myNextNode;
		Type								myData;
	};

	template<typename Type>
	DoubleLinkedListNode<Type>::DoubleLinkedListNode()
	{
		myPrevNode  = nullptr;
		myNextNode  = nullptr;
		myData;
	}

	template<typename Type>
	DoubleLinkedListNode<Type>::DoubleLinkedListNode(const Type& aData)
	{
		myPrevNode = nullptr;
		myNextNode  = nullptr;
		myData = aData;
	}

	template<typename Type>
	DoubleLinkedListNode<Type>::DoubleLinkedListNode(DoubleLinkedListNode* aPrevNode, DoubleLinkedListNode* aNextNode, Type& aData)
	{
		myPrevNode = aPrevNode;
		myNextNode  = aNextNode;
		myData = aData;
	}

	template<typename Type>
	DoubleLinkedListNode<Type>::DoubleLinkedListNode(DoubleLinkedListNode* aNode)
	{
		myPrevNode = aNode->myPrevNode;
		myNextNode  = aNode->myNextNode;
		myData = aNode->myData;
	}

	template<typename Type>
	DoubleLinkedListNode<Type>::~DoubleLinkedListNode()
	{
	}
};

namespace CU = CommonUtilities;

#endif