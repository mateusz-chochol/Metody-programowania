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
Converts number as a string to long long (exits program if a given string isn't a number)
*/
int convertStringToInt(std::string numberAsString)
{
	if (numberAsString[0] == ' ')
		exitProgram();

	for (int i = 0; i < numberAsString.length(); i++)
	{
		if ((numberAsString[i] < '0' || numberAsString[i] > '9') && numberAsString[i] != '-' && numberAsString[i] != ' ')
			exitProgram();
	}

	return std::stoi(numberAsString);
}

/*
Checks whether the value is greater / lesser than a given limit
*/
void checkNumberValue(int &value, int limit, greaterOrLessThanSign sign)
{
	if (sign == GREATER)
	{
		if (value < limit)
		{
			std::cout << "!(>" << limit << ")" << std::endl;
			value = getNumber();
			checkNumberValue(value, limit, GREATER);
		}
	}
	else
	{
		if (value >= limit)
		{
			std::cout << "!(<" << limit << ")" << std::endl;
			value = getNumber();
			checkNumberValue(value, limit, LESS);
		}
	}
}

/*
Checks whether the value stays between the limits
*/
void checkNumberValue(int &value, int lowerLimit, int upperLimit)
{
	if (value >= upperLimit || value <= lowerLimit) 
	{
		std::cout << "!(" << upperLimit << "> & <" << lowerLimit << ")" << std::endl;
		value = getNumber();
		checkNumberValue(value, lowerLimit, upperLimit);
	}
}

/*
Gets number, checks if it is really a number and if not, makes user type a number again
*/
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

/*
Safely exits program
*/
void exitProgram()
{
	std::cout << "Something went wrong.";
	getchar();
	exit(0);
}