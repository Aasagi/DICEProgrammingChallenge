#ifndef TREE_NODE_H
#define TREE_NODE_H

#ifndef SAFE_DELETE
#define SAFE_DELETE(aTreeNode) delete aTreeNode; aTreeNode = nullptr;
#endif

namespace CommonUtilities
{
	template<typename Type>
	struct TreeNode
	{
	public:
		TreeNode();
		TreeNode(Type aValue);
		~TreeNode();

		TreeNode*		myLeft;
		TreeNode*		myRight;
		Type			myData;
	};

	template<typename Type>
	TreeNode<Type>::TreeNode()
	{
		myLeft = nullptr;
		myRight = nullptr;
		myData;
	}

	template<typename Type>
	TreeNode<Type>::TreeNode(Type aValue)
	{
		myLeft = nullptr;
		myRight = nullptr;
		myData = aValue;
	}

	template<typename Type>
	TreeNode<Type>::~TreeNode()
	{

	}

};

namespace CU = CommonUtilities;

#endif