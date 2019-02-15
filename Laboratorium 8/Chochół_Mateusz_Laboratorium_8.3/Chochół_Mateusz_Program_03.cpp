#include "FileFunctionsLibrary.h"
#include "InputFunctionsLibrary.h"
#include "ArrayFunctionsLibrary.h"
#include <string>

bool isThereProperCombination(const int* allObjects, int knapsackSize, std::vector<int> &combination, int currentSize = 0, int index = 1);
void checkKnapsack(const int* allObjects, int knapsackSize);

/*
 * Program otwiera podany plik
 * zbiera informacje o liczbie zestawow danych
 * nastepnie dla kazdego zestawu danych funkcja:
 * zbiera informacje o pojemnosci plecaka
 * zbiera wszystkie obiekty do jednowymiarowej tablicy int'ow (bo w tym cwiczeniu obiekty te maja jedynie wage - bez nazwy i ceny)
 * sprawdza czy istnieje kombinacja wag pozwalajaca uzyskac maksymalna wage plecaka i jednoczesnie zapisuje ja do zmiennej typu vector<int>
 * na koniec jesli funkcja zwrocila "true" to znaczy, ze znalazla odpowiednia kombinacje i zapisala ja we wczesniej utworzonym vectorze
 * program wiec zapisuje ja do pliku 
 * jesli funkcja zwrocila "false" to znaczy, ze nie znalazla zadnej kombinacji wag, ktorych suma bylaby rowna wadze plecaka oraz, ze vector jest pusty
 * w takim razie program wpisuje do pliku "BRAK"
 */

int main()
{
	auto input = createFileStream(std::ios::in);
	auto output = createFileStream(std::ios::out);
	std::string numberOfSetsAsString;

	std::getline(input, numberOfSetsAsString);
	const auto numberOfSets = convertStringToNumber<int>(numberOfSetsAsString);
	
	if (numberOfSets < 1)
		exitProgram();

	for (auto i = 0; i < numberOfSets; i++)
	{
		std::string knapsackSizeAsString;
		std::getline(input, knapsackSizeAsString);

		const auto knapsackSize = convertStringToNumber<int>(knapsackSizeAsString);
		const auto allObjects = getNumbersTable<int>(input);
		checkKnapsack(allObjects, knapsackSize);
		
		std::vector<int> combination;

		if (isThereProperCombination(allObjects, knapsackSize, combination))
		{
			output << knapsackSize << " = ";

			for (auto &part : combination)
				output << part << " ";
		}
		else
			output << "BRAK";

		output << std::endl;
	}

	return 0;
}

bool isThereProperCombination(const int* allObjects, const int knapsackSize, std::vector<int> &combination, const int currentSize, int index)
{
	if (currentSize == knapsackSize)
		return true;

	if (knapsackSize < currentSize || index > allObjects[0] - 1)
		return false;

	combination.push_back(allObjects[index++]);

	if (!isThereProperCombination(allObjects, knapsackSize, combination, currentSize + combination.back(), index))
	{
		combination.pop_back();
		return isThereProperCombination(allObjects, knapsackSize, combination, currentSize, index);
	}
		
	return true;
}

void checkKnapsack(const int* allObjects, const int knapsackSize)
{
	if (knapsackSize < 1 || knapsackSize > 1000000)
		exitProgram();

	for (auto i = 1; i < allObjects[0]; i++)
		if (allObjects[i] < 1 || allObjects[i] > 1000000)
			exitProgram();
}