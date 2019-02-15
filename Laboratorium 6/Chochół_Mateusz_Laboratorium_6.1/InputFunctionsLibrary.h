#ifndef INPUTFUNCTIONSLIBRARY_H
#define INPUTFUNCTIONSLIBRARY_H

#include <string>
#include <iostream>

bool isCharacterOperand(char character);

bool isCharacterOperator(char character);

enum greaterOrLessThanSign { GREATER, LESS };

int getNumber();

void exitProgram();

/*
Converts number as a string to long long (exits program if a given string isn't a number)
*/
template<typename T> T convertStringToNumber(std::string numberAsString)
{
	if (numberAsString[0] == ' ')
		exitProgram();

	for (int i = 0; i < numberAsString.length(); i++)
	{
		if ((numberAsString[i] < '0' || numberAsString[i] > '9') && numberAsString[i] != '-' && numberAsString[i] != ' ')
			exitProgram();
	}

	return T(std::stoi(numberAsString));
}

/*
Checks whether the value is greater / lesser than a given limit
*/
template <typename T> void checkNumberValue(T &value, T limit, greaterOrLessThanSign sign)
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
template <typename T> void checkNumberValue(T &value, T lowerLimit, T upperLimit)
{
	if (value >= upperLimit || value <= lowerLimit)
	{
		std::cout << "!(" << upperLimit << "> & <" << lowerLimit << ")" << std::endl;
		value = getNumber();
		checkNumberValue(value, lowerLimit, upperLimit);
	}
}

#endif // !INPUTFUNCTIONSLIBRARY_H
