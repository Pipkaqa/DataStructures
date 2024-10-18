#include "BinaryHeap/BinaryHeap.h"
#include "BinaryTree/BinaryTree.h"
#include "List/List.h"

#include <iostream>
#include <list>

static void BinaryHeapTest()
{
	std::cout << std::endl << "BinaryHeapTest:" << std::endl;

	BinaryHeap heap;

	heap.add(91784);
	heap.add(9);
	heap.add(3);
	heap.add(1);
	heap.add(6);
	heap.add(11);
	heap.add(999);
	heap.add(11231);
	heap.add(116);

	heap.print();

	std::cout << "\nPop: " << std::endl;
	std::cout << heap.pop() << std::endl;
	std::cout << heap.pop() << std::endl;
	std::cout << heap.pop() << std::endl;
	std::cout << heap.pop() << std::endl;
	std::cout << heap.pop() << std::endl;
	std::cout << heap.pop() << std::endl;
	std::cout << heap.pop() << std::endl;
	std::cout << heap.pop() << std::endl;
	std::cout << heap.pop() << std::endl;

	heap.print();
}

static void BinaryTreeTest()
{
	std::cout << std::endl << "BinaryTreeTest:" << std::endl;

	BinaryTree tree;

	tree.add(5);
	tree.add(2);
	tree.add(-1249);
	tree.add(0);
	tree.add(-69);
	tree.add(132);
	tree.add(253);
	tree.add(56);

	if (tree.find(9999999) == nullptr)
	{
		std::cout << "9999999 not found" << std::endl;
	}

	std::cout << tree.find(0)->get_data() << std::endl;
	std::cout << tree.find(-69)->get_data() << std::endl;
	std::cout << tree.find(-1249)->get_data() << std::endl;
}

class Obj
{
public:
	Obj(int i) {}
private:
	Obj() {}
};

static void LinkedListTest()
{
	using namespace List;

	std::cout << std::endl << "LinkedListTest:" << std::endl;

	LinkedList<int> List;

	{
		List.PushBack(1);
		List.PushBack(2);
		List.PushBack(3);
		List.PushBack(4);
		List.PushBack(5);

		LinkedList<int>::IteratorType BeginIt = List.Begin();
		LinkedList<int>::ConstIteratorType EndIt = List.ConstEnd();

		for (; BeginIt != EndIt; ++BeginIt)
		{
			std::cout << *BeginIt << std::endl;
		}

		--EndIt;
		--BeginIt;

		for (; BeginIt != List.Begin(); --BeginIt)
		{
			std::cout << *BeginIt << std::endl;
		}

		List.PopBack();
		List.PopBack();

		List.Clear();
		List.Clear();
		List.Clear();
		List.Clear();
	}

	{
		LinkedList<int>::IteratorType BeginIt = List.Begin();
		LinkedList<int>::ConstIteratorType EndIt = List.End();

		for (; BeginIt != EndIt; ++BeginIt)
		{
			std::cout << *BeginIt << std::endl;
		}

		List.PushFront(4);
		List.PushFront(5);

		BeginIt = List.Begin();
		EndIt = List.End();

		for (; BeginIt != EndIt; ++BeginIt)
		{
			std::cout << *BeginIt << std::endl;
		}
	}
}

int main()
{
	BinaryHeapTest();
	BinaryTreeTest();
	LinkedListTest();
}