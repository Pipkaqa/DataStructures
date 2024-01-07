#pragma once
#pragma once

#include "BinaryTreeNode.h"

class BinaryTree
{
public:
	BinaryTree();
	BinaryTree(int data);

	BinaryTreeNode* add(int data);
	BinaryTreeNode* find(int data);

private:
	BinaryTreeNode* _root;
	int _size = 0;
};
