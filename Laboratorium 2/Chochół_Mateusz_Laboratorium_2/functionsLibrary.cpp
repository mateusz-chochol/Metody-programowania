#include "functionsLibrary.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#pragma region Sprawdzanie poprawnosci danych

void checkNumberValue(long long value, long long lowerLimit, long long upperLimit)
{
	if (value >= upperLimit || value <= lowerLimit)
		exitProgram();
}

bool checkFileExtension(std::string fileName)
{
	int numberOfLetters = fileName.length();

	if (fileName[numberOfLetters] == 't' && fileName[numberOfLetters - 1] == 'x' && fileName[numberOfLetters - 2] == 't' && fileName[numberOfLetters - 3] == '.')
		return true;

	return false;
}

bool checkIfFileExists(std::string fileName)
{
	std::ifstream fileStream(fileName);
	return fileStream.good();
}

void checkOrder(long long *table, int size)
{
	for (int i = 1; i < size - 1; i++)
	{
		if (table[i + 1] < table[i])
			exitProgram();
	}
}

#pragma endregion

#pragma region Przygotowanie programu do dzialania

std::fstream createFileStream(std::ios_base::openmode streamType)
{
	if (streamType == std::ios_base::in)
	{
		std::string fileName;
		int numberOfTries = 0;

		while (numberOfTries < 3)
		{
			std::cout << "Type in the correct file name (.txt): ";
			std::getline(std::cin, fileName);

			if (checkIfFileExists(fileName) && checkFileExtension(fileName))
			{
				std::fstream fileStream(fileName, std::ios_base::in);
				return fileStream;
			}
			else if (checkIfFileExists(fileName + ".txt"))
			{
				std::fstream fileStream(fileName + ".txt", std::ios_base::in);
				return fileStream;
			}

			std::cout << "Cannot find the file." << std::endl;
			numberOfTries++;
		}

		std::cout << "File cannot be found." << std::endl;
		getchar();
		exit(0);
	}
	else if (streamType == std::ios_base::out)
	{
		std::fstream fileStream("out.txt", std::ios_base::out);
		return fileStream;
	}
	else
		exitProgram();
}

long long *getNumbersTable(std::fstream &file)
{
	if (file.peek() == EOF || !file.is_open())
		exitProgram();

	std::string numbersAsString;
	std::getline(file, numbersAsString);

	int numberOfNumbers = convertStringToLongLong(numbersAsString);

	checkNumberValue(numberOfNumbers, 0, 32768);

	/*tablice sa zawsze wieksze niz "potrzeba" o 1 dodatkowa komorke, po to, by w komorce o indeksie [0] moc trzymac swoj rozmiar (przydaje sie w wielu miejsach, 
	... a to najprostsze rozwiazanie na zapamietanie go [dlatego tez pozniej, w niektorych miejsach poczatek tablicy ma indeks [1] - bo od tego miejsca zaczyna sie ...
	... tablica z pliku. Komorka z [0] to rozmiar tablicy, wiec np przy wyszukiwaniu indexu srednio nas ona interesuje]).*/
	long long *numbersTable = new long long[numberOfNumbers + 1];

	std::getline(file, numbersAsString);

	std::string singleNumberAsString = "";
	int tableIndex = 1;

	for (int i = 0; i <= numbersAsString.length(); i++)
	{
		if ((numbersAsString[i] == ' ' || numbersAsString[i] == '\0') && singleNumberAsString != "")
		{
			if (tableIndex > numberOfNumbers)
				exitProgram();

			long long singleNumber = convertStringToLongLong(singleNumberAsString);
			checkNumberValue(singleNumber, -pow(2, 48), pow(2, 48));
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

#pragma endregion

#pragma region Glowne funkcje programu

int countSameElements(long long *table, int size, long long element)
{
	if (table[1] == element && table[size - 1] == element)
		return size - 1;

	int firstIndex = firstAppearance(table, 1, size - 1, element);

	if (firstIndex == -1)
		return 0;

	int lastIndex = lastAppearance(table, firstIndex, size - 1, size, element);

	return lastIndex - firstIndex + 1;
}

int findIndex(long long* table, int size, long long element)
{
	if (element < table[1] || element > table[size - 1])
		return -1;

	if (element == table[1] && element == table[size - 1])
		return 0;

	int startingIndex = 1, lastIndex = size - 1;

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

void getRidOfDuplicates(long long *table, int size)
{
	int temporaryTableIndex = 2;

	for (int i = 1; i < size - 1; i++)
	{
		if (table[i + 1] != table[i])
		{
			table[temporaryTableIndex] = table[i + 1];
			temporaryTableIndex++;
		}
	}

	table[0] = temporaryTableIndex;
}

void exitProgram()
{
	std::cout << "Values in the file are incorrect.";
	getchar();
	exit(0);
}

#pragma endregion

#pragma region Funkcje pomocnicze

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

long long convertStringToLongLong(std::string numberAsString)
{
	if (numberAsString[0] == ' ')
		exitProgram();

	for (int i = 0; i < numberAsString.length(); i++) 
	{
		if ((numberAsString[i] < '0' || numberAsString[i] > '9') && numberAsString[i] != '-' && numberAsString[i] != ' ')
			exitProgram();
	}

	return std::stoll(numberAsString);
}

#pragma endregion