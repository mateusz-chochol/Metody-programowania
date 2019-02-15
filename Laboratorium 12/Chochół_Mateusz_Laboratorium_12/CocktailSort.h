#ifndef COCTAILSORT_H
#define COCTAILSORT_H

#include "CTablica.h"
#include <string>

class CocktailSort : public CTablica
{
public:
	void sort(int *table, const int lowestIndex, const int highestIndex) override
	{
		auto swapMade = true;
		auto leftIndex = lowestIndex;
		auto rightIndex = highestIndex;

		while (leftIndex < rightIndex && swapMade)
		{
			swapMade = false;

			for (auto i = leftIndex; i < rightIndex; i++)
			{
				if (compare(table[i], table[i + 1], Greater))
				{
					swap(table[i], table[i + 1]);
					swapMade = true;
				}
			}

			rightIndex--;

			if(swapMade)
			{
				swapMade = false;

				for (auto i = rightIndex; i > leftIndex; i--)
				{
					if (compare(table[i], table[i - 1], Less))
					{
						swap(table[i], table[i - 1]);
						swapMade = true;
					}
				}
			}

			leftIndex++;
		}
	}

	std::string getName() override { return "Coctailsort"; }
};

#endif