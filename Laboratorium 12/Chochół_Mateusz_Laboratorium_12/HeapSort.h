#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "CTablica.h"
#include <string>

class HeapSort : public CTablica
{
	void heapify(int* table, const int first, const int last)
	{
		auto indexToSwap = first;
		const auto leftIndex = 2 * first + 1;
		const auto rightIndex = leftIndex + 1;

		if (compare(leftIndex, last, Less) && compare(table[leftIndex], table[indexToSwap], Greater))
			indexToSwap = leftIndex;

		if (compare(rightIndex, last, Less) && compare(table[rightIndex], table[indexToSwap], Greater))
			indexToSwap = rightIndex;

		if (compare(indexToSwap, first, Greater))
		{
			swap(table[first], table[indexToSwap]);
			heapify(table, indexToSwap, last);
		}
	}

public:
	void sort(int* table, const int lowestIndex, const int highestIndex) override
	{
		for (auto i = highestIndex / 2 - 1; i >= 0; i--)
			heapify(table, i, highestIndex);

		for (auto i = highestIndex; i >= lowestIndex; i--)
		{
			swap(table[lowestIndex], table[i]);
			heapify(table, lowestIndex, i);
		}
	}

	std::string getName() override { return "Heapsort"; }
};

#endif