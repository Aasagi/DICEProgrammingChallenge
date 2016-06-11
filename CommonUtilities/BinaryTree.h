#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "TreeNode.h"
#include <iostream>

namespace CommonUtilities
{
	template<typename Type>
	class BinaryTree
	{
	public:
		BinaryTree				();
		~BinaryTree				();

		TreeNode<Type>*		GetRootNode				();

		void				InsertNode				(TreeNode<Type>* aValueToInsert);
		void				DeleteNode				(TreeNode<Type>* aNode);
		void				InsertNode				(Type aValueToInsert);
		void				DeleteNode				(Type aValue);

		TreeNode<Type>*		Find					(Type aValue);

		void				InOrderTraverse			();
		void				InOrder					(TreeNode<Type>* aNode);
		void				PostOrderTraverse		();
		void				PostOrder				(TreeNode<Type>* aNode);

		void				Print					(TreeNode<Type>* aVisitingNode);

		void				DSW_Balance				();
		bool				RotateRight				(TreeNode<Type>* aCurrentNode);
		void				RotateLeft				(TreeNode<Type>* aCurrentNode);

	private:
		TreeNode<Type>*		myRootNode;

	};

	template<typename Type>
	BinaryTree<Type>::BinaryTree()
	{
		myRootNode = nullptr;
	}

	template<typename Type>
	BinaryTree<Type>::~BinaryTree()
	{

	}

	template<typename Type>
	TreeNode<Type>* BinaryTree<Type>::GetRootNode()
	{
		return myRootNode;
	}

	template<typename Type>
	void BinaryTree<Type>::InsertNode(TreeNode<Type>* aNodeToInsert)
	{
		if(myRootNode == nullptr)
		{
			myRootNode = aNodeToInsert;
		}
		else
		{
			TreeNode<Type>* node = myRootNode;
			TreeNode<Type>* previousNode = nullptr;

			while(node != nullptr)
			{
				previousNode = node;

				if(node->myData > aNodeToInsert->myData)
				{
					node = node->myLeft;
				}
				else
				{
					node = node->myRight;
				}
			}

			if(previousNode->myData > aNodeToInsert->myData)
			{
				previousNode->myLeft = aNodeToInsert;
			}
			else
			{
				previousNode->myRight = aNodeToInsert;
			}
		}
	}

	template<typename Type>
	void BinaryTree<Type>::DeleteNode(TreeNode<Type>* aNode)
	{
		if(aNode != nullptr)
		{
			//Deletion by Copying
			TreeNode<Type>* nodeToBeDeletedParent = myRootNode;
			TreeNode<Type>* nodeToBeDeleted = aNode;

			//Find parent node to the nodeToBeDeleted
			if(nodeToBeDeletedParent != nodeToBeDeleted)
			{
				while(nodeToBeDeletedParent->myLeft != nodeToBeDeleted && nodeToBeDeletedParent->myRight != nodeToBeDeleted)
				{
					if(nodeToBeDeletedParent->myData > nodeToBeDeleted->myData)
					{
						nodeToBeDeletedParent = nodeToBeDeletedParent->myLeft;
					}
					else
					{
						nodeToBeDeletedParent = nodeToBeDeletedParent->myRight;
					}
				}
			}

			//Has childs on both sides
			if(aNode->myLeft != nullptr && aNode->myRight != nullptr)
			{
				nodeToBeDeletedParent = nodeToBeDeleted;
				nodeToBeDeleted = nodeToBeDeleted->myLeft;

				while(nodeToBeDeleted->myRight != nullptr)
				{
					nodeToBeDeletedParent = nodeToBeDeleted;
					nodeToBeDeleted = nodeToBeDeleted->myRight;
				}

				aNode->myData = nodeToBeDeleted->myData;

				if(nodeToBeDeletedParent != aNode)
				{
					nodeToBeDeletedParent->myRight = nodeToBeDeleted->myLeft;
				}
				else
				{
					nodeToBeDeletedParent->myLeft = nodeToBeDeleted->myLeft;
				}
			}
			//Has only right child
			else if(nodeToBeDeleted->myRight != nullptr)
			{
				aNode = aNode->myRight;

				//Which side is this child on the parent?
				if(nodeToBeDeletedParent->myLeft == nodeToBeDeleted)
				{
					nodeToBeDeletedParent->myLeft = aNode;
				}
				else
				{
					nodeToBeDeletedParent->myRight = aNode;
				}
			}
			//Has only left child
			else if(nodeToBeDeleted->myLeft != nullptr)
			{
				aNode = aNode->myLeft;

				//Which side is this child on the parent?
				if(nodeToBeDeletedParent->myLeft == nodeToBeDeleted)
				{
					nodeToBeDeletedParent->myLeft = aNode;
				}
				else
				{
					nodeToBeDeletedParent->myRight = aNode;
				}
			}
			//No childs, make the parent point to nullptr
			else
			{
				if(nodeToBeDeletedParent->myLeft == nodeToBeDeleted)
				{
					nodeToBeDeletedParent->myLeft = nullptr;
				}
				else
				{
					nodeToBeDeletedParent->myRight = nullptr;
				}
			}

			if(nodeToBeDeleted == myRootNode)
			{
				myRootNode = aNode;
				if(myRootNode->myLeft == nullptr && myRootNode->myRight == nullptr)
				{
					myRootNode = nullptr;
				}
			}

			SAFE_DELETE(nodeToBeDeleted);
		}
	}

	template<typename Type>
	void BinaryTree<Type>::InsertNode(Type aValueToInsert)
	{
		TreeNode<Type>* node = new TreeNode<Type>(aValueToInsert);

		InsertNode(node);
	}

	template<typename Type>
	void BinaryTree<Type>::DeleteNode(Type aValue)
	{
		DeleteNode(Find(aValue));
	}

	template<typename Type>
	TreeNode<Type>* BinaryTree<Type>::Find(Type aValue)
	{
		TreeNode<Type>* node = myRootNode;

		while(node != nullptr)
		{
			if(node->myData == aValue)
			{
				return node;
			}
			else if(node->myData > aValue)
			{
				node = node->myLeft;
			}
			else
			{
				node = node->myRight;
			}
		}

		return nullptr;
	}

	template<typename Type>
	void BinaryTree<Type>::InOrderTraverse()
	{
		InOrder(myRootNode);
	}

	template<typename Type>
	void BinaryTree<Type>::InOrder(TreeNode<Type>* aNode)
	{
		if(aNode != nullptr)
		{
			InOrder(aNode->myLeft);
			Print(aNode);
			InOrder(aNode->myRight);
		}
	}

	template<typename Type>
	void BinaryTree<Type>::PostOrderTraverse()
	{
		PostOrder(myRootNode);
	}

	template<typename Type>
	void BinaryTree<Type>::PostOrder(TreeNode<Type>* aNode)
	{
		if(aNode != nullptr)
		{
			PostOrder(aNode->myLeft);
			PostOrder(aNode->myRight);
			Print(aNode);
		}
	}

	template<typename Type>
	void BinaryTree<Type>::Print(TreeNode<Type>* aVisitingNode)
	{
		std::cout << aVisitingNode->myData << std::endl;
	}

	template<typename Type>
	void BinaryTree<Type>::DSW_Balance()
	{
		//Create backbone first
		int numberOfNodes = 0;

		for(TreeNode<Type>* node = myRootNode; node != nullptr; node = node->myRight, ++numberOfNodes)
		{
			//This while loop will keep running as long as there is any left nodes
			while(RotateRight(node) == true)
			{
				//Do nothing, just keep on rotating right
			}
		}

		//Balance the backbone
		for(int i = numberOfNodes / 2; 0 < i; i /= 2)
		{
			int j = 0;
			for(TreeNode<Type>* node = myRootNode; j < i; node = node->myRight)
			{
				RotateLeft(node);
				++j;
			}
		}
	}

	template<typename Type> 
	bool BinaryTree<Type>::RotateRight(TreeNode<Type>* aCurrentNode)
	{
		if(aCurrentNode != nullptr && aCurrentNode->myLeft != nullptr)
		{
			//Switch the nodes places, including their childs
			TreeNode<Type>* node = aCurrentNode->myLeft;
			aCurrentNode->myLeft = node->myLeft;
			node->myLeft = node->myRight;
			node->myRight = aCurrentNode->myRight;
			aCurrentNode->myRight = node;

			//Switch their data
			Type previousData = aCurrentNode->myData;
			aCurrentNode->myData= node->myData;
			node->myData = previousData;

			return true;
		}

		return false;

		/*if(aGrand != nullptr)
		{
			aGrand->myRight = aChild;
		}
		else
		{
			myRootNode = aChild;
		}


		aParent->myRight = aChild->myleft;
		aChild->myleft = aParent;*/

	}

	template<typename Type> 
	void BinaryTree<Type>::RotateLeft(TreeNode<Type>* aCurrentNode)
	{
		TreeNode<Type>* node = aCurrentNode->myRight;
		aCurrentNode->myRight = node->myRight;
		node->myRight = node->myLeft;
		node->myLeft = aCurrentNode->myLeft;
		aCurrentNode->myLeft = node;

		Type previousData = aCurrentNode->myData;
		aCurrentNode->myData= node->myData;
		node->myData = previousData;
	}
};

using namespace CommonUtilities;

#endif