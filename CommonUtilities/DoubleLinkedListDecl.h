#ifndef DOUBLE_LINKED_LIST_DECL_H
#define DOUBLE_LINKED_LIST_DECL_H

#include "DoubleLinkedListNodeDecl.h"

namespace CommonUtilities
{
	template<typename Type>
	class DoubleLinkedList
	{
	public:
					DoubleLinkedList();
					~DoubleLinkedList();

		DoubleLinkedListNode<Type>*			GetFirstNode()			const;
		DoubleLinkedListNode<Type>*			GetLastNode()			const;

		void		InsertNodeBeforeNode(DoubleLinkedListNode<Type>* aNode, DoubleLinkedListNode<Type>* aNodeToInsert);
		void		InsertNodeAfterNode(DoubleLinkedListNode<Type>* aNode, DoubleLinkedListNode<Type>* aNodeToInsert);

		void		InsertNodeSorted(DoubleLinkedListNode<Type>* aNodeToInsert);
		void		InsertNodeSorted(const Type& aValueToInsert);

		void		DeleteNode(DoubleLinkedListNode<Type>* aNode);
		void		DeleteNode(Type aValue);

		DoubleLinkedListNode<Type>*			Find(const Type& aValue);

	private:
		DoubleLinkedListNode<Type>*			myHead;
		DoubleLinkedListNode<Type>*			myTail;
	};
};

#endif