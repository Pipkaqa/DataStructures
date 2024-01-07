#pragma once

#include <iostream>
#include <vector>

class BinaryHeap
{
public:
	void add(int data);
	int pop();

	void print();

private:
	std::vector<int> nodes;

	void sort();
};