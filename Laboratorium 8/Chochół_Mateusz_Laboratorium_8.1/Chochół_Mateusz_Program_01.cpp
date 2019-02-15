#include "FileFunctionsLibrary.h"
#include "InputFunctionsLibrary.h"
#include "KnapsackFunctionsLibrary.h"
#include "Object.h"
#include <vector>

std::vector<Object> getBestObjects(std::vector<Object> &allObjects, int maxSize);
void sortObjectsByPriceMassRatio(std::vector<Object> &objects, int left, int right);

/*
 * Funkcja otwiera plik
 * zbiera informacje o wielkosci plecaka
 * laduje do pamieci wszystkie obiekty (kazdy ma swoja cene, mase, nazwe i stosunek cena/masa)
 * (musza byc zapisane w pliku w formacie: "nazwa(cena, masa)")
 * sortuje obiekty quicksortem na podstawie stosunku cena/masa
 * laduje do pamieci wszystkie obiekty tak dluga jak ich laczna masa nieprzekracza wielkosci plecaka (sa juz posortowane po cena/masa)
 * zapisuje liste do pliku
 */

int main()
{
	auto file = createFileStream(std::ios::in);
	
	std::string backpackSizeAsString;
	std::getline(file, backpackSizeAsString);

	const auto backpackSize = convertStringToNumber<int>(backpackSizeAsString);

	if (backpackSize < 1)
		exitProgram();

	auto allObjects = getAllObjects(file);
	const auto bestObjects = getBestObjects(allObjects, backpackSize);

	file = createFileStream(std::ios::out);

	for (const auto& object : bestObjects)
		file << object.getName() << std::endl;

	return 0;
}

std::vector<Object> getBestObjects(std::vector<Object> &allObjects, int maxSize)
{
	sortObjectsByPriceMassRatio(allObjects, 0, allObjects.size() - 1);
	std::reverse(allObjects.begin(), allObjects.end());
	std::vector<Object> bestObjects;

	for (auto& object : allObjects)
	{
		const auto sizeAfter = maxSize - object.getMass();

		if (sizeAfter >= 0)
		{
			bestObjects.push_back(object);
			maxSize = sizeAfter;
		}
	}

	return bestObjects;
}

void sortObjectsByPriceMassRatio(std::vector<Object> &objects, const int left, const int right)
{
	auto currentLeft = left, currentRight = right;
	const auto currentMiddle = objects.at((left + right) / 2).getPriceMassRatio();
	
	do
	{
		while (objects.at(currentLeft).getPriceMassRatio() < currentMiddle)
			currentLeft++;

		while (objects.at(currentRight).getPriceMassRatio() > currentMiddle)
			currentRight--;

		if (currentLeft <= currentRight)
		{
			std::swap(objects.at(currentLeft), objects.at(currentRight));

			currentLeft++;
			currentRight--;
		}
	} while (currentLeft <= currentRight);

	if (left < currentRight) 
		sortObjectsByPriceMassRatio(objects, left, currentRight);

	if (right > currentLeft) 
		sortObjectsByPriceMassRatio(objects, currentLeft, right);
}