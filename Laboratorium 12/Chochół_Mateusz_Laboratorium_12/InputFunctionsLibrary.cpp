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
 * Returns a single number from a file set on a given line or exits the program if input was incorrect
 */
int getIntegerFromFile(std::fstream &file)
{
	if (!file.is_open())
		exitProgram();

	std::string numberAsString;
	std::getline(file, numberAsString);
	auto number = 0;

	try
	{
		number = std::stoi(numberAsString);
	}
	catch(std::invalid_argument& exception)
	{
		exitProgram(std::string("Function \"getIntegerFromFile()\" read an integer from file which was in incorrect form. \n(Possible other characters than digits in the same line?) \nException message: ") + exception.what());
	}

	return number;
}

/*
Gets number, checks if it is really a number and if not, informs a user about it and safely exits the program.
*/
int getIntegerFromConsole()
{
	std::string numberAsString;
	std::getline(std::cin, numberAsString);
	auto number = 0;

	try
	{
		number = stoi(numberAsString);
	}
	catch (std::invalid_argument& exception)
	{
		exitProgram(std::string("Function \"getIntegerFromConsole\" got integer in incorrect form \n(Possible other characters than digits?)\nException message: ") + exception.what());
	}

	return number;
}

/*
Safely exits the program and if given - displays a message
*/
void exitProgram(const std::string &message)
{
	if (message.empty())
		std::cerr << "Something went wrong.";
	else
		std::cerr << message;

	std::cerr << "\n\nClick enter to exit the program.";
	getchar();
	exit(0);
}