#include "FileFunctionsLibrary.h"
#include "RNGLibrary.h"
#include "InputFunctionsLibrary.h"
#include <iostream>

int getOptionNumber();
int getUpperBoundary();
int getNumberOfNumbers();
void openMenu(int numberOfNumbers, int upperBoundary, int optionNumber);

int main()
{
	openMenu(getNumberOfNumbers(), getUpperBoundary(), getOptionNumber());

	return 0;
}

int getOptionNumber()
{
	auto optionNumber = 0;

	while (optionNumber < 1 || optionNumber > 3)
	{
		std::cout << "Choose RNG option: \n\n1. LCG \n2. ACG \n3. Shuffling method \n\nOption: ";
		optionNumber = getNumber();
		system("cls");
	}

	return optionNumber;
}

int getUpperBoundary()
{
	auto upperBoundary = 0;

	while (upperBoundary < 1)
	{
		std::cout << "Whats the upper boundary of your numbers: ";
		upperBoundary = getNumber();
		system("cls");
	}

	return upperBoundary;
}

int getNumberOfNumbers()
{
	auto numberOfNumbers = 0;

	while (numberOfNumbers < 1 || numberOfNumbers > 256)
	{
		std::cout << "How many number you wish to generate: ";
		numberOfNumbers = getNumber();
		system("cls");
	}

	return numberOfNumbers;
}

void openMenu(const int numberOfNumbers, const int upperBoundary, const int optionNumber)
{
	auto file = createFileStream(std::ios::out);

	switch (optionNumber)
	{
	case 1:
		for (auto number : linearCongruentialGenerator(upperBoundary, numberOfNumbers))
			file << number << std::endl;
		break;
	case 2:
		for (auto number : additiveCongruentialGenerator(upperBoundary, numberOfNumbers))
			file << number << std::endl;
		break;
	case 3:
		for (auto number : shufflingGenerator(upperBoundary, numberOfNumbers))
			file << number << std::endl;
		break;
	default:
		exitProgram();
	}
}