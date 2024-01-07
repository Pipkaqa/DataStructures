#include "BinaryHeap.h"

void BinaryHeap::add(int data)
{
	nodes.push_back(data);

	sort();
}

int BinaryHeap::pop()
{
	if (nodes.empty())
	{
		return 0;
	}

	int deleted = nodes[0];

	nodes.erase(std::remove(nodes.begin(), nodes.end(), nodes[0]), nodes.end());

	sort();

	return deleted;
}

void BinaryHeap::print()
{
	for (auto& node : nodes)
	{
		std::cout << node << "\n";
	}
}

void BinaryHeap::sort()
{
	int length = static_cast<int>(nodes.size());

	for (int i = length - 1; i >= 0; i--)
	{
		int parent = (i - 1) / 2;

		if (nodes[parent] < nodes[i])
		{
			int temp = nodes[parent];
			nodes[parent] = nodes[i];
			nodes[i] = temp;
		}
	}
}