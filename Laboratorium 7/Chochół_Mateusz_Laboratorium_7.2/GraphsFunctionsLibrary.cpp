#include "GraphsFunctionsLibrary.h"
#include "InputFunctionsLibrary.h"
#include "ArrayFunctionsLibrary.h"
#include "FileFunctionsLibrary.h"
#include "ListClass.h"

/*
* Gets all neigbhors of all vertexes
*/
void getNeighborhood(std::fstream &file, std::vector<std::vector<int>> &matrix, const int numberOfEgdes, const int numberOfVertexes)
{
	file << std::endl;

	for (auto i = 0; i < numberOfEgdes; i++)
	{
		auto firstVertex = 0, secondVertex = 0;

		for (auto j = 0; j < numberOfVertexes; j++)
		{
			if (matrix.at(i).at(j) == 1)
				firstVertex = j + 1;
			else if (matrix.at(i).at(j) == -1)
				secondVertex = j + 1;

			if (firstVertex != 0 && secondVertex != 0)
			{
				file << firstVertex << " sasiaduje z " << secondVertex << std::endl;
				j = numberOfVertexes;
			}
		}
	}
}

/*
* Gets all neigbhors of all vertexes
*/
void getNeighborhood(std::fstream &file, int** matrix, const int numberOfEgdes, const int numberOfVertexes)
{
	file << std::endl;

	for (auto i = 1; i <= numberOfEgdes; i++)
	{
		auto firstVertex = 0, secondVertex = 0;

		for (auto j = 1; j <= numberOfVertexes; j++)
		{
			if (matrix[i][j] == 1)
				firstVertex = j;
			else if (matrix[i][j] == -1)
				secondVertex = j;

			if (firstVertex != 0 && secondVertex != 0)
			{
				file << firstVertex << " sasiaduje z " << secondVertex << std::endl;
				j = numberOfVertexes;
			}
		}
	}
}

/*
 * Creates array of adjecency lists for graph with no directions
 */
void adjacencyListArray(std::fstream &file)
{
	const auto numberOfEgdes = getNumberFromFile(file), numberOfVertexes = getNumberOfVertexes(file, numberOfEgdes);
	const auto adjacencyListArray = new List*[numberOfVertexes + 1]();

	file.seekg(0);
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	for (auto i = 0; i < numberOfEgdes; i++)
	{
		std::string firstVertexValueAsString, secondVertexValueAsString;
		file >> firstVertexValueAsString;
		file >> secondVertexValueAsString;

		const auto firstVertexValue = convertStringToNumber<int>(firstVertexValueAsString);
		const auto secondVertexValue = convertStringToNumber<int>(secondVertexValueAsString);
		const auto firstVertex = new List, secondVertex = new List;

		firstVertex->value = secondVertexValue;
		secondVertex->value = firstVertexValue;

		firstVertex->next = adjacencyListArray[firstVertexValue];
		secondVertex->next = adjacencyListArray[secondVertexValue];

		adjacencyListArray[firstVertexValue] = firstVertex;
		adjacencyListArray[secondVertexValue] = secondVertex;
	}

	file = createFileStream(std::ios::out);

	for (auto i = 1; i <= numberOfVertexes; i++)
	{
		file << "Vertex " << i << " -> ";

		auto currentElement = adjacencyListArray[i];
		auto weight = 0;

		while (currentElement)
		{
			file << currentElement->value;
			currentElement = currentElement->next;

			if (currentElement)
				file << ", ";

			weight++;
		}

		file << "\nWeight: " << weight << std::endl << std::endl;
	}
}

/*
* Creates incidence matrix of a graph using vectors
*/
void graphsOnVectors(std::fstream &file)
{
	const auto numberOfEgdes = getNumberFromFile(file), numberOfVertexes = getNumberOfVertexes(file, numberOfEgdes);
	std::vector<std::vector<int>> matrix;

	file.seekg(0);
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	for (auto i = 0; i < numberOfEgdes; i++)
	{
		matrix.emplace_back();

		std::string firstVertexInPairAsString, secondVertexInPairAsString;
		file >> firstVertexInPairAsString;
		file >> secondVertexInPairAsString;

		const auto firstVertexInPair = convertStringToNumber<int>(firstVertexInPairAsString);
		const auto secondVertexInPair = convertStringToNumber<int>(secondVertexInPairAsString);

		for (auto j = 1; j <= numberOfVertexes; j++)
		{
			if (firstVertexInPair == secondVertexInPair && firstVertexInPair == j)
				matrix.at(i).push_back(2);
			else if (firstVertexInPair == j)
				matrix.at(i).push_back(1);
			else if (secondVertexInPair == j)
				matrix.at(i).push_back(-1);
			else
				matrix.at(i).push_back(0);
		}
	}

	file = createFileStream(std::ios::out);

	for (auto i = 0; i < numberOfEgdes; i++)
	{
		for (auto j = 0; j < numberOfVertexes; j++)
			file << matrix.at(i).at(j) << " ";

		file << std::endl;
	}
}

/*
 * Creates incidence matrix of a graph using arrays
 */
void graphsOnArrays(std::fstream &file)
{
	const auto numberOfEgdes = getNumberFromFile(file), numberOfVertexes = getNumberOfVertexes(file, numberOfEgdes);
	const auto matrix = create2DArray(numberOfEgdes + 1, numberOfVertexes + 1);

	file.seekg(0);
	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	for (auto i = 1; i <= numberOfEgdes; i++)
	{
		std::string firstVertexInPairAsString, secondVertexInPairAsString;
		file >> firstVertexInPairAsString;
		file >> secondVertexInPairAsString;

		const auto firstVertexInPair = convertStringToNumber<int>(firstVertexInPairAsString);
		const auto secondVertexInPair = convertStringToNumber<int>(secondVertexInPairAsString);

		if (firstVertexInPair == secondVertexInPair)
			matrix[i][firstVertexInPair] = 2;
		else
		{
			matrix[i][firstVertexInPair] = 1;
			matrix[i][secondVertexInPair] = -1;
		}
	}

	file = createFileStream(std::ios::out);

	for (auto i = 1; i <= numberOfEgdes; i++)
	{
		for (auto j = 1; j <= numberOfVertexes; j++)
			file << matrix[i][j] << " ";

		file << std::endl;
	}
}

/*
 * Returns number of vertexes in a given graph
 */
int getNumberOfVertexes(std::fstream &file, const int numberOfEgdes)
{
	auto numberOfVertexes = 0, egdeCount = 0;

	for (auto i = 1; i <= numberOfEgdes; i++)
	{
		if (file.peek() == EOF)
			exitProgram();

		const auto biggerVertexInPair = extractPairBiggerVertex(file);

		if (numberOfVertexes < biggerVertexInPair)
			numberOfVertexes = biggerVertexInPair;

		egdeCount++;
	}

	if (egdeCount != numberOfEgdes || !file.eof())
		exitProgram();

	return numberOfVertexes;
}

/*
 * Returns bigger number from a pair of vertexes
 */
int extractPairBiggerVertex(std::fstream &file)
{
	std::string firstNumberAsString, secondNumberAsString;
	file >> firstNumberAsString, file >> secondNumberAsString;

	auto firstNumber = convertStringToNumber<int>(firstNumberAsString), secondNumer = convertStringToNumber<int>(secondNumberAsString);

	return firstNumber > secondNumer ? firstNumber : secondNumer;
}