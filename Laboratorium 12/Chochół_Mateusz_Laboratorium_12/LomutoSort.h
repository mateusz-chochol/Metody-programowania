#ifndef LOMUTOSORT_H
#define LOMUTOSORT_H

#include "CTablica.h"
#include <string>

class LomutoSort : public CTablica
{
	int partition(int* table, const int first, const int last)
	{
		const auto pivot = table[last];
		auto currentIndex = first - 1;

		for (auto i = first; i < last; i++)
		{
			if (compare(table[i], pivot, LessOrEqual))
			{
				currentIndex++;
				swap(table[currentIndex], table[i]);
			}
		}

		swap(table[currentIndex + 1], table[last]);
		return currentIndex + 1;
	}

public:
	void sort(int* table, const int lowestIndex, const int highestIndex) override
	{
		if (compare(lowestIndex, highestIndex, Less))
		{
			const auto partitioningIndex = partition(table, lowestIndex, highestIndex);

			sort(table, lowestIndex, partitioningIndex - 1);
			sort(table, partitioningIndex + 1, highestIndex);
		}
	}

	std::string getName() override { return "Lomutosort"; }
};

#endif