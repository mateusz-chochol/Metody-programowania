#ifndef INPUTFUNCTIONSLIBRARY_H
#define INPUTFUNCTIONSLIBRARY_H
#include <string>
#include <iostream>

bool isCharacterOperand(char character);

bool isCharacterOperator(char character);

enum GreaterOrLessThanSign { Greater, Less };

int getIntegerFromFile(std::fstream &file);

int getIntegerFromConsole();

void exitProgram(const std::string &message = "");

/*
Converts number as a string to T type number (exits program if a given string isn't a number)
*/
template<typename T> T convertStringToNumber(const std::string numberAsString)
{
	try
	{
		if (std::is_same<T, int>() || std::is_same<T, short>())
			return std::stoi(numberAsString);
		if (std::is_same<T, long>())
			return std::stol(numberAsString);
		if (std::is_same<T, long long>())
			return std::stoll(numberAsString);
		if (std::is_same<T, double>())
			return std::stod(numberAsString);
		if (std::is_same<T, float>())
			return std::stof(numberAsString);

		throw std::runtime_error("Function \"convertStringToNumber()\" wasn't given any of the common value types to convert to.");
	}
	catch(std::invalid_argument& exception)
	{
		exitProgram(std::string("Function \"convertStringToNumber()\" was given a number in incorrect form. \n(Possible other characters than digits, '+' or '-' ?)\n") + exception.what());
	}
}

/*
Checks whether the value is greater / lesser than a given limit
*/
template <typename T> void checkConsoleNumberValue(T &value, T limit, const GreaterOrLessThanSign sign)
{
	if (sign == Greater)
	{
		if (value < limit)
		{
			std::cout << "!(>" << limit << ")" << std::endl;
			value = getIntegerFromConsole();
			checkConsoleNumberValue(value, limit, Greater);
		}
	}
	else
	{
		if (value >= limit)
		{
			std::cout << "!(<" << limit << ")" << std::endl;
			value = getIntegerFromConsole();
			checkConsoleNumberValue(value, limit, Less);
		}
	}
}

/*
Checks whether the value stays between the limits
*/
template <typename T> void checkConsoleNumberValue(T &value, T lowerLimit, T upperLimit)
{
	if (value >= upperLimit || value <= lowerLimit)
	{
		std::cout << "!(" << upperLimit << "> & <" << lowerLimit << ")" << std::endl;
		value = getIntegerFromConsole();
		checkConsoleNumberValue(value, lowerLimit, upperLimit);
	}
}

#endif // !INPUTFUNCTIONSLIBRARY_H