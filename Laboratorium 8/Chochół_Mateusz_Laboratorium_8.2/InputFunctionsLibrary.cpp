#include "InputFunctionsLibrary.h"
#include <fstream>
#include <iostream>
#include <string>

/*
 * Returns true if a given character is a lowercase letter.
 */
bool isCharacterOperand(const char character)
{
	return character >= 'a' && character <= 'z';
}

/*
 * Returns true if a given character is one of the 11 possible operators (+, -, *, etc...)
 */
bool isCharacterOperator(const char character)
{
	return character == '=' || character == '<' || character == '>' || character == '+' || character == '-' ||
		character == '*' || character == '/' || character == '%' || character == '^' || character == '~' || character == '(' || character == ')';
}

/*
 * Returns a single number from a file set on a given line or exits the programme if input was incorrect
 */
int getNumberFromFile(std::fstream &file)
{
	if (!file.is_open())
		exitProgram();

	std::string numberAsString;
	std::getline(file, numberAsString);

	if (numberAsString.length() == 0)
		exitProgram();

	for(auto character : numberAsString)
	{
		if ((character < '0' || character > '9') && character != '-')
			exitProgram();
	}

	return std::stoi(numberAsString);
}

/*
Gets number, checks if it is really a number and if not, makes user type a number again
*/
int getNumberFromConsole()
{
	std::string setsAsString;
	std::getline(std::cin, setsAsString);

	auto letterIndex = 0;

	while (setsAsString.length() == 0 || letterIndex < int(setsAsString.length()))
	{
		if (setsAsString.length() == 0)
		{
			std::cout << "!(number)\nType number: ";
			std::getline(std::cin, setsAsString);
		}
		else if ((setsAsString[letterIndex] < '0' || setsAsString[letterIndex] > '9') && setsAsString[letterIndex] != '-')
		{
			std::cout << "!(number)\nType number: ";
			std::getline(std::cin, setsAsString);
			letterIndex = 0;
		}
		else
			letterIndex++;
	}

	return std::stoi(setsAsString);
}

/*
Safely exits the program
*/
void exitProgram()
{
	system("cls");
	std::cout << "Something went wrong.";
	getchar();
	exit(0);
}