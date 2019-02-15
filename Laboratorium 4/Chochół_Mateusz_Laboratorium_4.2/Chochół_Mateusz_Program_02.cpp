#include "FileFunctionsLibrary.h"
#include "ArrayFunctionsLibrary.h"
#include "InputFunctionsLibrary.h"
#include "OperatorClass.h"
#include "OnpFunctionsLibrary.h"

int main()
{
	auto file = createFileStream(std::ios::in);
	auto expressions = getLinesFromFile(file);
	const auto operators = Operator::createCommonOperators();

	for (auto& expression : expressions)
	{
		if (expression.length() < 6 || expression.length() > 255)
			expression = "ERROR";
		else if (expression.substr(0, 5) == "INF: ")
			infixToPostfix(expression, operators);
		else if (expression.substr(0, 5) == "ONP: ")
			postfixToInfix(expression, operators);
		else
			exitProgram();
	}

	file = createFileStream(std::ios::out);

	for (auto& expression : expressions)
		file << expression << std::endl;

	return 0;
}