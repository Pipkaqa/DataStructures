#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
	_root = new BinaryTreeNode(0);
}

BinaryTree::BinaryTree(int data)
{
	_root = new BinaryTreeNode(data);
}

BinaryTreeNode* BinaryTree::add(int data)
{
	BinaryTreeNode* current = _root;

	while (true)
	{
		if (data > current->get_data())
		{
			if (current->right == nullptr)
			{
				return current->right = new BinaryTreeNode(data);
			}

			current = current->right;
		}
		else if (data < current->get_data())
		{
			if (current->left == nullptr)
			{
				return current->left = new BinaryTreeNode(data);
			}

			current = current->left;
		}
		else
		{
			return nullptr;
		}
	}
}

BinaryTreeNode* BinaryTree::find(int data)
{
	BinaryTreeNode* current = _root;

	while (true)
	{
		if (!current) { return current; }

		if (data > current->get_data())
		{
			current = current->right;
		}
		else if (data < current->get_data())
		{
			current = current->left;
		}
		else
		{
			return current;
		}
	}
}