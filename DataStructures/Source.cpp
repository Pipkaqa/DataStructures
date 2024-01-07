#include "iostream"
#include "BinaryTree.h"

int main()
{
	BinaryTree* tree = new BinaryTree(100);

	tree->add(90);
	tree->add(110);
	tree->add(111);
	tree->add(112);
	tree->add(10);
	tree->add(120);
	tree->add(75);

	auto node1 = tree->find(1);
	auto node2 = tree->find(111);
	auto node3 = tree->find(75);

	return 0;
}