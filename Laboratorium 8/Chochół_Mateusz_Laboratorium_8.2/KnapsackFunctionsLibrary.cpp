#include "KnapsackFunctionsLibrary.h"
#include "InputFunctionsLibrary.h"
#include <fstream>

std::vector<Object> getAllObjects(std::fstream &file)
{
	std::vector<Object> objects;

	while (!file.eof())
	{
		std::string line;
		std::getline(file, line);

		objects.push_back(getObject(line));
	}

	return objects;
}

Object getObject(const std::string& line)
{
	std::string name, priceAsString, massAsString;
	auto index = 0;

	while (line[index] != '(')
		name += line[index++];

	index++;

	while (line[index] != ',')
		priceAsString += line[index++];

	index += 2;

	while (line[index] != ')')
		massAsString += line[index++];

	const auto price = convertStringToNumber<int>(priceAsString), mass = convertStringToNumber<int>(massAsString);

	if (mass <= 0 || price < 0)
		exitProgram();

	return Object(name, price, mass);
}