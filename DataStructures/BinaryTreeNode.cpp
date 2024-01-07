#include "BinaryTreeNode.h"

BinaryTreeNode::BinaryTreeNode(int data)
{
	_data = data;
}

int BinaryTreeNode::get_data()
{
	return _data;
}

void BinaryTreeNode::set_data(int data)
{
	_data = data;
}