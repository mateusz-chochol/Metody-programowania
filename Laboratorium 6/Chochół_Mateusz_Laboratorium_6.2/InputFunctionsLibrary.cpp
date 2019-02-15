#include "InputFunctionsLibrary.h"
#include <iostream>
#include <string>

/*
 * Returns true if a given character is a lowercase letter.
 */
bool isCharacterOperand(const char character)
{
	return (character >= 'a' && character <= 'z');
}

/*
 * Return true if a given character is one of the 11 possible operators (+, -, *, etc...)
 */
bool isCharacterOperator(const char character)
{
	return (character == '=' || character == '<' || character == '>' || character == '+' || character == '-' ||
		character == '*' || character == '/' || character == '%' || character == '^' || character == '~' || character == '(' || character == ')');
}

/*
Gets number, checks if it is really a number and if not, makes user type a number again
*/
int getNumber()
{
	std::string setsAsString;
	std::getline(std::cin, setsAsString);

	auto letterIndex = 0;

	while (setsAsString.length() == 0 || letterIndex < setsAsString.length())
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
Safely exits program
*/
void exitProgram()
{
	std::cout << "Something went wrong.";
	getchar();
	exit(0);
}