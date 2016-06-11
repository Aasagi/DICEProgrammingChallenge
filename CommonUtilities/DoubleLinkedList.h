#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include "DoubleLinkedListDecl.h"

namespace CommonUtilities
{
	template<typename Type>
	DoubleLinkedList<Type>::DoubleLinkedList()
	{
		myHead = nullptr;
		myTail = nullptr;
	}

	template<typename Type>
	DoubleLinkedList<Type>::~DoubleLinkedList()
	{
		DoubleLinkedListNode<Type>* currNode;
		DoubleLinkedListNode<Type>* nextNode = myTail;

		while(nextNode != nullptr)
		{
			currNode = nextNode;
			nextNode = currNode->myPrevNode;
			SAFE_DELETE(currNode);
		}
	}

	template<typename Type>
	DoubleLinkedListNode<Type>*			DoubleLinkedList<Type>::GetFirstNode()			const
	{
		return myHead;
	}

	template<typename Type>
	DoubleLinkedListNode<Type>*			DoubleLinkedList<Type>::GetLastNode()			const
	{
		return myTail;
	}

	template<typename Type>
	void		DoubleLinkedList<Type>::InsertNodeBeforeNode(DoubleLinkedListNode<Type>* aNode, DoubleLinkedListNode<Type>* aNodeToInsert)
	{
		//If there is nothing in the list
		if(myHead == nullptr)
		{
			myHead = aNodeToInsert;
			myTail = myHead;
		}
		else
		{
			if(myHead == aNode)
			{
				//If the list is only size 1
				if(myHead == myTail)
				{
					myHead = aNodeToInsert;

					myHead->myNextNode = myTail;

					myTail->myPrevNode = myHead;
				}
				//The list is larger than 1
				else
				{
					//assign their prev and next nodes first before assigning NodeToInsert as myHead
					myHead->myPrevNode = aNodeToInsert;

					aNodeToInsert->myNextNode = myHead;

					//NodeToInsert is now before myHead,
					myHead = aNodeToInsert;
				}
			}
			else
			{
				//Assign the inserted nodes Prev- and NextNode first
				aNodeToInsert->myPrevNode = aNode->myPrevNode;
				aNodeToInsert->myNextNode = aNode;

				//Assign insertedNodes Previous NextNode to the InsertedNode
				aNode->myPrevNode->myNextNode = aNodeToInsert;

				//Insert the TargetedNodes PrevNode to the insertedNode
				aNode->myPrevNode = aNodeToInsert;
			}
		}
	}

	template<typename Type>
	void		DoubleLinkedList<Type>::InsertNodeAfterNode(DoubleLinkedListNode<Type>* aNode, DoubleLinkedListNode<Type>* aNodeToInsert)
	{
		//If there is nothing in the list
		if(myHead == nullptr)
		{
			myHead = aNodeToInsert;
			myTail = myHead;
		}
		else
		{
			if(myTail == aNode)
			{
				//If the list is only size 1
				if(myHead == myTail)
				{
					myTail = aNodeToInsert;

					//Because a NodeToInsert has nextNode and prevNode as NULLPTR
					//Set myHeads nextNode as myTail and vice versa
					myHead->myNextNode = myTail;

					myTail->myPrevNode = myHead;
				}
				//The list is larger
				else
				{
					//assign their prev and next nodes first before assigning NodeToInsert as myTail
					myTail->myNextNode = aNodeToInsert;

					aNodeToInsert->myPrevNode = myTail;

					//NodeToInsert is now after myTail
					myTail = aNodeToInsert;
				}
			}
			else
			{
				//Assign the inserted nodes Prev- and NextNode first
				aNodeToInsert->myNextNode = aNode->myNextNode;
				aNodeToInsert->myPrevNode = aNode;

				//Assign insertedNodes nextNode PrevNode to the InsertedNode
				aNode->myNextNode->myPrevNode = aNodeToInsert;

				//Insert the TargetedNodes NextNode to the insertedNode
				aNode->myNextNode = aNodeToInsert;
			}
		}
	}

	template<typename Type>
	void		DoubleLinkedList<Type>::InsertNodeSorted(DoubleLinkedListNode<Type>* aNodeToInsert)
	{
		//If there is nothing in the list
		if(myHead == nullptr)
		{
			myHead = aNodeToInsert;
			myTail = myHead;
		}
		else
		{
			//If the list is only size 1
			if(myHead == myTail)
			{
				if(aNodeToInsert->myData < myHead->myData)
				{
					myHead = aNodeToInsert;

					myHead->myNextNode = myTail;

					myTail->myPrevNode = myHead;
				}
				else
				{
					myTail = aNodeToInsert;

					myHead->myNextNode = myTail;

					myTail->myPrevNode = myHead;
				}
			}
			//The list is larger
			else
			{
				for(DoubleLinkedListNode<Type>* nodeInList = myHead;
					nodeInList != nullptr;		//myTail->myNextNode is a nullptr, If it is, break loop
					nodeInList = nodeInList->myNextNode)
				{
					if(aNodeToInsert->myData < nodeInList->myData)
					{
						if(nodeInList == myHead)
						{
							//assign their prev and next nodes first before assigning NodeToInsert as myHead
							myHead->myPrevNode = aNodeToInsert;

							aNodeToInsert->myNextNode = myHead;

							//NodeToInsert is now before myHead,
							myHead = aNodeToInsert;
						}
						else
						{
							//Assign the inserted nodes Prev- and NextNode first
							aNodeToInsert->myPrevNode = nodeInList->myPrevNode;
							aNodeToInsert->myNextNode = nodeInList;

							//Assign insertedNodes Previous NextNode to the InsertedNode
							nodeInList->myPrevNode->myNextNode = aNodeToInsert;

							//Insert the TargetedNodes PrevNode to the insertedNode
							nodeInList->myPrevNode = aNodeToInsert;
						}
						//Break the loop because we have inserted the node
						break;
					}
					else if(nodeInList == myTail)
					{
						//This means that InsertNode is larger than myTails Data
						//and will be inserted as the last node, which is as myTail

						//assign their prev and next nodes first before assigning NodeToInsert as myTail
						myTail->myNextNode = aNodeToInsert;

						aNodeToInsert->myPrevNode = myTail;

						//NodeToInsert is now after myTail
						myTail = aNodeToInsert;
						//Break the loop because we have inserted the node
						break;
					}
				}
			}
		}
	}

	template<typename Type>
	void		DoubleLinkedList<Type>::InsertNodeSorted(const Type& aValueToInsert)
	{
		DoubleLinkedListNode<Type>* newNode = new DoubleLinkedListNode<Type>(aValueToInsert);
		//If there is nothing in the list
		InsertNodeSorted(newNode);
	}

	template<typename Type>
	void		DoubleLinkedList<Type>::DeleteNode(DoubleLinkedListNode<Type>* aNode)
	{
		//If there is nothing in the list
		if(myHead != nullptr)
		{
			//If the list is only size 1
			if(myHead == myTail)
			{
				if(myHead == aNode)
				{
					SAFE_DELETE(myHead);
					myTail = nullptr;
				}
			}
			else
			{
				if(aNode == myTail)
				{
					myTail = myTail->myPrevNode;
					myTail->myNextNode = nullptr;
				}
				else if(aNode == myHead)
				{
					myHead = myHead->myNextNode;
					myHead->myPrevNode = nullptr;
				}
				else
				{
					aNode->myPrevNode->myNextNode = aNode->myNextNode;
					aNode->myNextNode->myPrevNode = aNode->myPrevNode;
				}

				SAFE_DELETE(aNode);
			}
		}
	}

	template<typename Type>
	void		DoubleLinkedList<Type>::DeleteNode(Type aValue)
	{
		//If there is nothing in the list
		if(myHead != nullptr)
		{
			//If the list is only size 1
			if(myHead == myTail)
			{
				if(myHead->myData == aValue)
				{
					SAFE_DELETE(myHead);
					myTail = nullptr;
				}
			}
			else
			{
				for(DoubleLinkedListNode<Type>* nodeInList = myHead;
					nodeInList != nullptr;		//Tail->NextNode is a nullptr, If it is, break loop
					nodeInList = nodeInList->myNextNode)
				{
					if(nodeInList->myData == aValue)
					{
						//Successfully found the node in list, we can use SAFE_DELETE on it (because it's in the list) 

						if(nodeInList == myTail)
						{
							myTail = myTail->myPrevNode;
							myTail->myNextNode = nullptr;
						}
						else if(nodeInList == myHead)
						{
							myHead = myHead->myNextNode;
							myHead->myPrevNode = nullptr;
						}
						else
						{
							nodeInList->myPrevNode->myNextNode = nodeInList->myNextNode;
							nodeInList->myNextNode->myPrevNode = nodeInList->myPrevNode;
						}

						SAFE_DELETE(nodeInList);
						break;
					}
				}
			}
		}
	}

	template<typename Type>
	DoubleLinkedListNode<Type>*			DoubleLinkedList<Type>::Find(const Type& aValue)
	{
		for(DoubleLinkedListNode<Type>* nodeInList = myHead;
			nodeInList != nullptr;
			nodeInList = nodeInList->myNextNode)
		{
			if(nodeInList->myData == aValue)
			{
				return nodeInList;
			}
		}

		//If it hasnt returned from the for loop, it means it didnt successfully find the value in the list
		//and if the list is empty, it will return myHead (which is nullptr)
		return nullptr;
	}
};

using namespace CommonUtilities;

#endif