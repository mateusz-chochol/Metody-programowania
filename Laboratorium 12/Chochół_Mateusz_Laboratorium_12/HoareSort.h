#ifndef HOARESORT_H
#define HOARESORT_H

#include "CTablica.h"
#include <string>

class HoareSort : public CTablica
{
	int partition(int *table, const int first, const int last) 
	{
		const auto pivot = table[first];
		auto leftIndex = first - 1; 
		auto rightIndex = last + 1;

		while (true) 
		{
			while (table[++leftIndex] < pivot) { }

			while (table[--rightIndex] > pivot) { }
			
			if (compare(leftIndex, rightIndex, GreaterOrEqual))
				return rightIndex;

			swap(table[leftIndex], table[rightIndex]);
		}
	}

public:
	void sort(int *table, const int lowestIndex, const int highestIndex) override
	{
		if (compare(highestIndex, lowestIndex, Greater)) 
		{
			const auto partitioningIndex = partition(table, lowestIndex, highestIndex);

			sort(table, lowestIndex, partitioningIndex);
			sort(table, partitioningIndex + 1, highestIndex);
		}
	}

	std::string getName() override { return "Hoaresort"; }
};

#endif