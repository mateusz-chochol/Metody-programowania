#include "InputFunctionsLibrary.h"
#include "ArrayFunctionsLibrary.h"
#include <string>
#include <fstream>

std::vector<std::string> getLinesFromFile(std::fstream &file)
{
	std::string temporaryString;
	auto linesCount = 0;

	std::getline(file, temporaryString);
	const auto numberOfLines = convertStringToInt(temporaryString);

	std::vector<std::string> lines;

	for (auto i = 0; i < numberOfLines; i++)
	{
		if (file.eof())
			exitProgram();

		linesCount++;

		std::getline(file, temporaryString);
		lines.push_back(temporaryString);
	}

	if (linesCount != numberOfLines)
		exitProgram();

	return lines;
}

int *getNumbersTable(std::fstream &file)
{
	if (file.peek() == EOF || !file.is_open())
		exitProgram();

	std::string numbersAsString;
	std::getline(file, numbersAsString);

	int numberOfNumbers = convertStringToInt(numbersAsString);

	checkNumberValue(numberOfNumbers, 0, 32768);

	int *numbersTable = new int[numberOfNumbers + 1];

	std::getline(file, numbersAsString);

	std::string singleNumberAsString = "";
	int tableIndex = 1;

	for (int i = 0; i <= numbersAsString.length(); i++)
	{
		if ((numbersAsString[i] == ' ' || numbersAsString[i] == '\0') && singleNumberAsString != "")
		{
			if (tableIndex > numberOfNumbers)
				exitProgram();

			int singleNumber = convertStringToInt(singleNumberAsString);
			numbersTable[tableIndex] = singleNumber;
			tableIndex++;
			singleNumberAsString = "";
		}
		else
			singleNumberAsString += numbersAsString[i];
	}

	if (tableIndex != numberOfNumbers + 1)
		exitProgram();

	numbersTable[0] = numberOfNumbers + 1;

	return numbersTable;
}

/*
Gets subarray with the biggest elements sum from a 1D array
*/
int kadaneAlgorithm(int *table, int size)
{
	int currentMaximumSum = 0, currentSequenceSum = 0, biggestNumber = -32768;
	bool allNumbersNegative = true;

	for (int i = 0; i < size; i++)
	{
		currentSequenceSum += table[i];

		if (currentSequenceSum < 0)
			currentSequenceSum = 0;
		else if (currentSequenceSum > currentMaximumSum)
			currentMaximumSum = currentSequenceSum;

		if (table[i] > biggestNumber)
			biggestNumber = table[i];

		if (allNumbersNegative && table[i] > 0)
			allNumbersNegative = false;
	}

	if (allNumbersNegative)
		return biggestNumber;
	else
		return currentMaximumSum;
}

/*
Gets subarray with the biggest elements sum from 2D array
*/
int maximumSubarray(int **table, int horizontal, int vertical)
{
	int currentMaximumSum = 0;

	for (int i = 0; i < horizontal; i++)
	{
		int *temporaryArray = new int[vertical]();

		for (int j = i; j < horizontal; j++)
		{
			for (int k = 0; k < vertical; k++)
				temporaryArray[k] += table[j][k];

			int sumOfSubarray = kadaneAlgorithm(temporaryArray, vertical);

			if (currentMaximumSum < sumOfSubarray)
				currentMaximumSum = sumOfSubarray;
		}
	}

	return currentMaximumSum;
}

/*
Finds an index of a given element in an ascending ordered table
If it doesn't exists: returns -1
*/
int findIndex(long long* table, int size, long long element)
{
	if (element < table[0] || element > table[size - 1])
		return -1;

	if (element == table[0] && element == table[size - 1])
		return 0;

	int startingIndex = 0, lastIndex = size - 1;

	while (startingIndex <= lastIndex)
	{
		int currentIndex = (startingIndex + lastIndex) / 2;

		if (table[currentIndex] == element)
			return currentIndex - 1;
		else if (table[currentIndex] < element)
			startingIndex = currentIndex + 1;
		else
			lastIndex = currentIndex - 1;
	}

	return -1;
}

/*
Finds how many times a given element appears in an ascending ordered table
*/
int countSameElements(long long *table, int size, long long element)
{
	if (table[0] == element && table[size - 1] == element)
		return size - 1;

	int firstIndex = firstAppearance(table, 0, size - 1, element);

	if (firstIndex == -1)
		return 0;

	int lastIndex = lastAppearance(table, firstIndex, size - 1, size, element);

	return lastIndex - firstIndex + 1;
}

/*
Finds the last index under which you can find a given element in a ascending ordered table
If it doesn't exists: returns -1
*/
int lastAppearance(long long *table, int lowestIndex, int highestIndex, int size, long long element)
{
	if (highestIndex >= lowestIndex)
	{
		int currentIndex = (lowestIndex + highestIndex) / 2;

		if ((currentIndex == size - 1 || element < table[currentIndex + 1]) && table[currentIndex] == element)
			return currentIndex;
		else if (element < table[currentIndex])
			return lastAppearance(table, lowestIndex, (currentIndex - 1), size, element);
		else
			return lastAppearance(table, (currentIndex + 1), highestIndex, size, element);
	}

	return -1;
}

/*
Finds the first index under which you can find a given element in a ascending ordered table
If it doesn't exists: returns -1
*/
int firstAppearance(long long *table, int lowestIndex, int highestIndex, long long element)
{
	if (highestIndex >= lowestIndex)
	{
		int currentIndex = (lowestIndex + highestIndex) / 2;

		if ((currentIndex == 1 || element > table[currentIndex - 1]) && table[currentIndex] == element)
			return currentIndex;
		else if (element > table[currentIndex])
			return firstAppearance(table, (currentIndex + 1), highestIndex, element);
		else
			return firstAppearance(table, lowestIndex, (currentIndex - 1), element);
	}

	return -1;
}