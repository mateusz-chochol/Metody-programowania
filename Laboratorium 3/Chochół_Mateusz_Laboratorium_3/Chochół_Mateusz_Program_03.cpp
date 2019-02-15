#include <iostream>
#include <fstream>
#include <string>

int getNumber();
void savePartition(std::ofstream&, int*, int*, int);

int main() 
{
	int number = getNumber(), *elements = new int[number](), *elementsCount = new int[number](), distinctNumbersCount = 1;

	std::ofstream file("Program_03.txt");

	elements[1] = number;
	elementsCount[1] = 1;

	file << elements[1] << std::endl;

	while (elements[1] > 1) 
	{
		int sumOfDeletedComponents = 0;

		if (elements[distinctNumbersCount] == 1)
		{
			sumOfDeletedComponents += elementsCount[distinctNumbersCount];
			distinctNumbersCount--;
		}

		sumOfDeletedComponents += elements[distinctNumbersCount];
		elementsCount[distinctNumbersCount]--;	
		
		int lastElement = elements[distinctNumbersCount] - 1;

		if (elementsCount[distinctNumbersCount] > 0)
			distinctNumbersCount++;

		elements[distinctNumbersCount] = lastElement;
		elementsCount[distinctNumbersCount] = sumOfDeletedComponents / lastElement;

		lastElement = sumOfDeletedComponents % lastElement;

		if (lastElement != 0)
		{
			distinctNumbersCount++;
			elements[distinctNumbersCount] = lastElement;
			elementsCount[distinctNumbersCount] = 1;
		}

		std::cout << distinctNumbersCount << std::endl;

		savePartition(file, elements, elementsCount, distinctNumbersCount);
	}

	file.close();

	getchar();

	return 0;
}

void savePartition(std::ofstream &file, int *elements, int *elementsCount, int numberOfParts)
{
		for (int i = 1; i <= numberOfParts; i++)
			for (int j = 1; j <= elementsCount[i]; j++)
					file << elements[i] << " ";	
		
		file << std::endl;
}

int getNumber()
{
	std::string setsAsString;
	std::getline(std::cin, setsAsString);

	int letterIndex = 0;

	while (setsAsString.length() == 0 || letterIndex < setsAsString.length())
	{
		if (setsAsString.length() == 0)
		{
			std::cout << "!(number)" << std::endl;
			std::getline(std::cin, setsAsString);
		}
		else if (setsAsString[letterIndex] < '0' || setsAsString[letterIndex] > '9')
		{
			std::cout << "!(number)" << std::endl;
			std::getline(std::cin, setsAsString);
			letterIndex = 0;
		}
		else
			letterIndex++;
	}

	return std::stoi(setsAsString);
}