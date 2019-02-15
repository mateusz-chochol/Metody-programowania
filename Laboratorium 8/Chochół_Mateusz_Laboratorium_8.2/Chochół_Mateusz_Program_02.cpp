#include "FileFunctionsLibrary.h"
#include "KnapsackFunctionsLibrary.h"
#include "InputFunctionsLibrary.h"
#include "ArrayFunctionsLibrary.h"
#include "fstream"

int** getAllCombinations(std::vector<Object> &allObjects, int backpackSize);
std::string getKnapsackContent(std::vector<Object> allObjects, int** combinations, int knapsackSize);

/*
 * Funkcja otwiera plik
 * zbiera informacje o pojemnosci plecaka
 * laduje do pamieci wszystkie obiekty (kazdy ma swoja cene, mase nazwe i stosunek cena/masa)
 * (musza byc zapisane w pliku w formacie: "nazwa(cena, masa)")
 * buduje dwuwymiarowa tabele z najlepszymi mozliwymi wynikami dla poszczegolnych warunkow
 * (co iteracje glownej petli dodawany jest jeden mozliwy do wyboru przedmiot wiecej)
 * (co iteracje petli zagniezdzonej zwiekszana jest maksymalna waga plecaka az osiagnie te podana w pliku)
 * wypisuje cala tabele do pliku (kazdy rzad oznacza nowy przedmiot, kazda kolumna - wage zwiekszona o 1)
 * oblicza na podstawie wczeniej obliczonej tabeli, ktore przedmioty zostaly uzyte w ostatnim ruchu
 * wypisuje owe przedmioty do pliku
 */

int main()
{
	auto file = createFileStream(std::ios::in);

	std::string backpackSizeAsString;
	std::getline(file, backpackSizeAsString);

	const auto knapsackSize = convertStringToNumber<int>(backpackSizeAsString);

	if (knapsackSize < 1)
		exitProgram();

	auto allObjects = getAllObjects(file);;
	const auto combinations = getAllCombinations(allObjects, knapsackSize);

	file = createFileStream(std::ios::out);

	for (auto i = 1; i <= allObjects.size(); i++)
	{
		for (auto j = 1; j <= knapsackSize; j++)
			file << combinations[i][j] << "	";

		file << std::endl;
	}

	const auto objectsList = getKnapsackContent(allObjects, combinations, knapsackSize);
	
	file << "\nObjects in knapsack: " << objectsList;
	file << "\nKnapsack value: " << combinations[allObjects.size()][knapsackSize];

	return 0;
}

int** getAllCombinations(std::vector<Object> &allObjects, const int backpackSize)
{
	const auto combinations = create2DArray<int>(allObjects.size() + 1, backpackSize + 1);

	for (auto i = 1; i <= allObjects.size(); i++)
	{
		for (auto j = 1; j <= backpackSize; j++)
		{
			if (allObjects.at(i - 1).getMass() > j)
				combinations[i][j] = combinations[i - 1][j];
			else
			{
				const auto oldValue = combinations[i - 1][j];
				const auto newValue = allObjects.at(i - 1).getPrice() + combinations[i - 1][j - allObjects.at(i - 1).getMass()];

				if (newValue > oldValue)
					combinations[i][j] = newValue;
				else
					combinations[i][j] = oldValue;
			}
		}
	}

	return combinations;
}

std::string getKnapsackContent(std::vector<Object> allObjects, int** combinations, int knapsackSize)
{
	std::string listOfObjects;
	auto numberOfObjects = allObjects.size();

	while (numberOfObjects > 0 && knapsackSize > 0)
	{
		const auto object = combinations[numberOfObjects][knapsackSize];

		if (object == combinations[numberOfObjects - 1][knapsackSize])
			numberOfObjects--;
		else
		{
			listOfObjects += allObjects.at(--numberOfObjects).getName() + "; ";
			knapsackSize -= allObjects.at(numberOfObjects).getMass();
		}
	}

	return listOfObjects;
}