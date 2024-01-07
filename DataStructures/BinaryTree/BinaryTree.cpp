#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
	_root = new BinaryTreeNode(0);
}

BinaryTree::BinaryTree(int data)
{
	_root = new BinaryTreeNode(data);
}

void BinaryTree::add(int data)
{
	BinaryTreeNode* current = _root;

	while (true)
	{
		if (data > current->get_data())
		{
			if (current->right == nullptr)
			{
				current->right = new BinaryTreeNode(data);
				return;
			}

			current = current->right;
		}
		else if (data < current->get_data())
		{
			if (current->left == nullptr)
			{
				current->left = new BinaryTreeNode(data);
				return;
			}

			current = current->left;
		}
		else
		{
			return;
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