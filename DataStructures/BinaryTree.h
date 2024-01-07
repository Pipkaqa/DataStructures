#pragma once

#include "BinaryTreeNode.h"

class BinaryTree
{
public:
	BinaryTree();
	BinaryTree(int data);

	void add(int data);
	BinaryTreeNode* find(int data);

private:
	BinaryTreeNode* _root;
	int _size = 0;
};
