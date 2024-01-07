#pragma once
#pragma once

class BinaryTreeNode
{
public:
	BinaryTreeNode* left = nullptr;
	BinaryTreeNode* right = nullptr;

	BinaryTreeNode(int data);

	int get_data();
	void set_data(int data);

private:
	int _data;
};