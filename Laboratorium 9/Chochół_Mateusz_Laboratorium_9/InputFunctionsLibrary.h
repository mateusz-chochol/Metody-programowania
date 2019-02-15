#ifndef INPUTFUNCTIONSLIBRARY_H
#define INPUTFUNCTIONSLIBRARY_H
#include <string>
#include <iostream>

bool isCharacterOperand(char character);

bool isCharacterOperator(char character);

enum GreaterOrLessThanSign { Greater, Less };

int getNumberFromFile(std::fstream &file);

int getNumberFromConsole();

void exitProgram();

/*
Converts number as a string to long long (exits program if a given string isn't a number)
*/
template<typename T> T convertStringToNumber(std::string numberAsString)
{
	if (numberAsString[0] == ' ')
		exitProgram();

	for (auto character : numberAsString)
	{
		if ((character < '0' || character > '9') && character != '-' && character != ' ')
			exitProgram();
	}

	if (std::is_same<T, int>() || std::is_same<T, short>())
		return std::stoi(numberAsString);
	if (std::is_same<T, long>())
		return std::stol(numberAsString);
	if (std::is_same<T, long long>())
		return std::stoll(numberAsString);

	exitProgram();
	return NULL;
}

/*
Checks whether the value is greater / lesser than a given limit
*/
template <typename T> void checkNumberValue(T &value, T limit, const GreaterOrLessThanSign sign)
{
	if (sign == Greater)
	{
		if (value < limit)
		{
			std::cout << "!(>" << limit << ")" << std::endl;
			value = getNumberFromConsole();
			checkNumberValue(value, limit, Greater);
		}
	}
	else
	{
		if (value >= limit)
		{
			std::cout << "!(<" << limit << ")" << std::endl;
			value = getNumberFromConsole();
			checkNumberValue(value, limit, Less);
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
		value = getNumberFromConsole();
		checkNumberValue(value, lowerLimit, upperLimit);
	}
}

#endif // !INPUTFUNCTIONSLIBRARY_H
