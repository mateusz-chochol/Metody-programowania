#ifndef ARRAYFUNCTIONSLIBRARY_H
#define ARRAYFUNCTIONSLIBRARY_H
#include "InputFunctionsLibrary.h"
#include <vector>
#include <fstream>

template<typename T> T** create2DArray(const int horizontally, const int vertically)
{
	const auto array = new T*[horizontally];

	for (auto i = 0; i < horizontally; i++)
		array[i] = new T[vertically]();

	return array;
}

std::vector<std::string> getLinesFromFile(std::fstream &file);

template<typename T> T* getNumbersTable(std::fstream &file)
{
	if (file.peek() == EOF || !file.is_open())
		exitProgram();

	std::string numbersAsString;
	std::getline(file, numbersAsString);

	auto numberOfNumbers = convertStringToNumber<int>(numbersAsString);

	checkNumberValue(numberOfNumbers, 0, 32768);

	auto *numbersTable = new T[numberOfNumbers + 1];

	std::getline(file, numbersAsString);

	std::string singleNumberAsString = "";
	auto tableIndex = 1;

	for (auto i = 0; i <= numbersAsString.length(); i++)
	{
		if ((numbersAsString[i] == ' ' || numbersAsString[i] == '\0') && singleNumberAsString != "")
		{
			if (tableIndex > numberOfNumbers)
				exitProgram();

			const auto singleNumber = convertStringToNumber<T>(singleNumberAsString);
			numbersTable[tableIndex++] = singleNumber;
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

int kadaneAlgorithm(const int *table, int size);

int maximumSubarray(int **table, int horizontal, int vertical);

int findIndex(long long* table, int size, long long element);

int countSameElements(long long *table, int size, long long element);

int lastAppearance(long long *table, int lowestIndex, int highestIndex, int size, long long element);

int firstAppearance(long long *table, int lowestIndex, int highestIndex, long long element);

#endif // !ARRAYFUNCTIONSLIBRARY_H