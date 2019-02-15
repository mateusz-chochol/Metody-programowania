#include "FileFunctionsLibrary.h"
#include "InputFunctionsLibrary.h"
#include "Node.h"
#include <string>

std::vector<Object> getObjects(std::fstream &file);
void getBestValue(Node* node, std::fstream &file);

/*
 * Program zbiera informacje (plik '.txt') o maksymalnej wadze plecaka i nastepnie o wszystkich obiektach, ktore potencjalnie mozna do niego wsadzic
 * Tworzy korzen, na ktorego podstawie rozpoczete bedzie pozniej cale drzewo
 * Wysyla utworzony korzen do funkcji rekurencyjnej, ktora w srodku zajmuje sie tworzeniem wierzcholkow
 * Funkcja ma taka zasade dzialania: jesli aktualnie sprawdzany wierzcholek jest obiecujacy, to stworz jego lewa i prawa galaz
 * W lewej dodaj kolejny obiekt, w prawej nie
 * (cala logika tego, czy wierzcholek jest obiecujacy znajduje sie w konstruktorze wierzcholka)
 * Jesli wierzcholek nie jest obiecujacy - nie rob nic
 * Pod koniec, po przejsciu przez cale drzewo, najlepsze upakowanie plecaka znajduje sie w zmiennej 'maxValue" bedacej czescia klasy 'Node'
 * W miedzyczasie podczas dzialania calego programu caly czas do pliku 'out.txt' zapisywane sa wszystkie kroki tworzenia drzewa
 */

int main()
{
	auto file = createFileStream(std::ios::in);

	std::string maxWeightAsString;
	getline(file, maxWeightAsString);

	const auto maxWeight = convertStringToNumber<int>(maxWeightAsString);
	const auto objects = getObjects(file);
	file = createFileStream(std::ios::out);

	getBestValue(new Node(objects, maxWeight), file);
	file << "\nBest value: " << Node::getMaxValue();

	return 0;
}

void getBestValue(Node* node, std::fstream &file)
{
	file << node->getNodeData();

	if (node->isPromising())
	{
		node->setLeftChild();
		getBestValue(node->getLeftChild(), file);

		node->setRightChild();
		getBestValue(node->getRightChild(), file);
	}

	file << "Go back" << std::endl;
}

std::vector<Object> getObjects(std::fstream &file)
{
	std::vector<Object> objects;

	while (!file.eof())
	{
		std::string priceAsString, weightAsString;
		
		file >> priceAsString; 
		
		if (file.peek() == EOF)
			exitProgram();
		
		file >> weightAsString;

		auto price = convertStringToNumber<int>(priceAsString); 
		auto weight = convertStringToNumber<int>(weightAsString);

		if (weight < 1 || price < 0)
			exitProgram();

		objects.emplace_back(price, weight);
	}

	return objects;
}