#include "iostream"
#include "BinaryTree/BinaryTree.h"
#include "BinaryHeap/BinaryHeap.h"

int main()
{
	BinaryHeap* heap = new BinaryHeap();

	heap->add(91784);
	heap->add(9);
	heap->add(3);
	heap->add(1);
	heap->add(6);
	heap->add(11);
	heap->add(999);
	heap->add(11231);
	heap->add(116);

	heap->print();

	std::cout << "\nPOP: " << std::endl;
	std::cout << heap->pop() << std::endl;
	std::cout << heap->pop() << std::endl;
	std::cout << heap->pop() << std::endl;
	std::cout << heap->pop() << std::endl;
	std::cout << heap->pop() << std::endl;
	std::cout << heap->pop() << std::endl;
	std::cout << heap->pop() << std::endl;
	std::cout << heap->pop() << std::endl;
	std::cout << heap->pop() << std::endl;
}