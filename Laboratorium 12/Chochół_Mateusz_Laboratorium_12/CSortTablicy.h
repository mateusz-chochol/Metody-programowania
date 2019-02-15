#ifndef CSORTTABLICY_H
#define CSORTTABLICY_H

#include "TableSize.h"
#include "CTablica.h"
#include "TableType.h"
#include "HoareSort.h"
#include "CocktailSort.h"
#include "LomutoSort.h"
#include "HeapSort.h"
#include <iostream>
#include <random>
#include <fstream>

class CSortTablicy
{
public:
	static int* fillTable(const int numberOfElements)
	{
		int* table;

		try
		{
			table = new int[numberOfElements];
		}
		catch (std::bad_alloc& exception)
		{
			std::cerr << "Memory couldn't be alocated (\"demo()\" function). Size less than 0? \nException message: " << exception.what();
			getchar();
			exit(0);
		}

		for (auto i = 0; i < numberOfElements; i++)
		{
			std::cin >> table[i];

			if (std::cin.fail())
			{
				std::cerr << "Value couldn't be insterted into an int array. Missclick?";
				getchar();
				exit(0);
			}
		}

		return table;
	}

	static int* getRandomlyFilledTable(const int numberOfElements)
	{
		int* table;

		try
		{
			table = new int[numberOfElements];
		}
		catch (std::bad_alloc& exception)
		{
			std::cerr << "Memory couldn't be alocated (\"demo()\" function). Size less than 0? \nException message: " << exception.what();
			getchar();
			exit(0);
		}

		std::random_device randomDevice;
		std::mt19937 engine(randomDevice());
		const std::uniform_int_distribution<int> distribution(1, numberOfElements);

		for (auto i = 0; i < numberOfElements; i++)
			table[i] = distribution(engine);

		return table;
	}

	static void demo(const TableSize tableSize, const TableType tableType, CTablica* sortingAlgorithm)
	{
		int numberOfElements;

		if (tableSize == Small)
			numberOfElements = 100;
		else if (tableSize == Medium)
			numberOfElements = 1000;
		else
			numberOfElements = 10000;

		auto table = new int[numberOfElements];

		if (tableType == Random)
			table = getRandomlyFilledTable(numberOfElements);
		else if (tableType == Ordered)
		{
			for (auto i = 0; i < numberOfElements; i++)
				table[i] = i + 1;
		}
		else if (tableType == ReverseOrdered)
		{
			for (auto i = numberOfElements - 1; i >= 0; i--)
				table[i] = numberOfElements - i + 1;
		}
		else
		{
			for (auto i = 0; i < numberOfElements; i++)
			{
				if (i % 10 == 0)
					table[i] = numberOfElements + i;
				else
					table[i] = i + 1;
			}
		}

		sortingAlgorithm->sort(table, 0, numberOfElements - 1);

		delete[] table;
	}

	static void sortDemo(CTablica* sortingAlgorithm, std::fstream &file)
	{
		demo(Small, Random, sortingAlgorithm);
		file << sortingAlgorithm->getName() << ", 100, Random, Swaps: " << sortingAlgorithm->getNumberOfSwaps() << ", Comparisons: " << sortingAlgorithm->getNumberOfComparisons() << std::endl;
		sortingAlgorithm->zeroSwapsAndComparisons();

		demo(Medium, Random, sortingAlgorithm);
		file << sortingAlgorithm->getName() << ", 1000, Random, Swaps: " << sortingAlgorithm->getNumberOfSwaps() << ", Comparisons: " << sortingAlgorithm->getNumberOfComparisons() << std::endl;
		sortingAlgorithm->zeroSwapsAndComparisons();

		demo(Large, Random, sortingAlgorithm);
		file << sortingAlgorithm->getName() << ", 10000, Random, Swaps: " << sortingAlgorithm->getNumberOfSwaps() << ", Comparisons: " << sortingAlgorithm->getNumberOfComparisons() << std::endl;
		sortingAlgorithm->zeroSwapsAndComparisons();

		demo(Small, Ordered, sortingAlgorithm);
		file << sortingAlgorithm->getName() << ", 100, Ordered, Swaps: " << sortingAlgorithm->getNumberOfSwaps() << ", Comparisons: " << sortingAlgorithm->getNumberOfComparisons() << std::endl;
		sortingAlgorithm->zeroSwapsAndComparisons();

		demo(Medium, Ordered, sortingAlgorithm);
		file << sortingAlgorithm->getName() << ", 1000, Ordered, Swaps: " << sortingAlgorithm->getNumberOfSwaps() << ", Comparisons: " << sortingAlgorithm->getNumberOfComparisons() << std::endl;
		sortingAlgorithm->zeroSwapsAndComparisons();

		demo(Large, Ordered, sortingAlgorithm);
		file << sortingAlgorithm->getName() << ", 10000, Ordered, Swaps: " << sortingAlgorithm->getNumberOfSwaps() << ", Comparisons: " << sortingAlgorithm->getNumberOfComparisons() << std::endl;
		sortingAlgorithm->zeroSwapsAndComparisons();

		demo(Small, ReverseOrdered, sortingAlgorithm);
		file << sortingAlgorithm->getName() << ", 100, Reverse ordered, Swaps: " << sortingAlgorithm->getNumberOfSwaps() << ", Comparisons: " << sortingAlgorithm->getNumberOfComparisons() << std::endl;
		sortingAlgorithm->zeroSwapsAndComparisons();

		demo(Medium, ReverseOrdered, sortingAlgorithm);
		file << sortingAlgorithm->getName() << ", 1000, Reverse ordered, Swaps: " << sortingAlgorithm->getNumberOfSwaps() << ", Comparisons: " << sortingAlgorithm->getNumberOfComparisons() << std::endl;
		sortingAlgorithm->zeroSwapsAndComparisons();

		demo(Large, ReverseOrdered, sortingAlgorithm);
		file << sortingAlgorithm->getName() << ", 10000, Reverse ordered, Swaps: " << sortingAlgorithm->getNumberOfSwaps() << ", Comparisons: " << sortingAlgorithm->getNumberOfComparisons() << std::endl;
		sortingAlgorithm->zeroSwapsAndComparisons();

		demo(Small, MostlyOrdered, sortingAlgorithm);
		file << sortingAlgorithm->getName() << ", 100, Mostly ordered, Swaps: " << sortingAlgorithm->getNumberOfSwaps() << ", Comparisons: " << sortingAlgorithm->getNumberOfComparisons() << std::endl;
		sortingAlgorithm->zeroSwapsAndComparisons();

		demo(Medium, MostlyOrdered, sortingAlgorithm);
		file << sortingAlgorithm->getName() << ", 1000, Mostly ordered, Swaps: " << sortingAlgorithm->getNumberOfSwaps() << ", Comparisons: " << sortingAlgorithm->getNumberOfComparisons() << std::endl;
		sortingAlgorithm->zeroSwapsAndComparisons();

		demo(Large, MostlyOrdered, sortingAlgorithm);
		file << sortingAlgorithm->getName() << ", 10000, Mostly ordered, Swaps: " << sortingAlgorithm->getNumberOfSwaps() << ", Comparisons: " << sortingAlgorithm->getNumberOfComparisons() << std::endl << std::endl;
		sortingAlgorithm->zeroSwapsAndComparisons();
	}

	static void ultimateDemo(std::fstream &file)
	{
		CTablica* sortingAlgorithm = new LomutoSort();
		sortDemo(sortingAlgorithm, file);

		sortingAlgorithm = new HeapSort();
		sortDemo(sortingAlgorithm, file);

		sortingAlgorithm = new CocktailSort();
		sortDemo(sortingAlgorithm, file);

		sortingAlgorithm = new HoareSort();
		sortDemo(sortingAlgorithm, file);
	}
};

#endif