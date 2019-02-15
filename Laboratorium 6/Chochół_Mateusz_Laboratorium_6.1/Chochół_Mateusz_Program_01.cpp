#include "ArrayFunctionsLibrary.h"
#include "FileFunctionsLibrary.h"
#include "InputFunctionsLibrary.h"

template <typename T> int mergeArrays(T* leftArray, T* rightArray, int leftIndex, int middleIndex, int rightIndex);
template <typename T> int getInversionsCount(T* leftArray, T* rightArray, int leftIndex, int rightIndex);

/*
 * Cala logika opiera sie na sortowaniu tablicy i jednoczesnym liczeniu krokow potrzebnych do jej calkowitego posortowania
 * Owa liczba krokow to jednoczesnie liczba inwersji.
 * MergeSort dzieli tablice na dwie czesci, liczy w kazdej z nich liczbe inwersji, a nastepnie laczy je i dolicza dodatkowo liczbe inwersji w nowej, wiekszej tablicy
 * Funkcja wywoluje w kolko sama siebie, wiec tak naprawde wszelkie obliczenia znajduja sie w funkcji laczacej dwie tablice i sumujacej wszystkie inwersje
 * Funkcje zwiazane z szablonami umieszczone sa w plikach .h, bo inaczej bedzie wyskakiwal blad: "unresolved external symbol"
 */

int main()
{
	auto file = createFileStream(std::ios::in);

	std::string setsAsString;
	std::getline(file, setsAsString);
	const auto sets = convertStringToNumber<int>(setsAsString);

	auto **arrays = new long long*[sets];

	for (auto i = 0; i < sets; i++)
		arrays[i] = getNumbersTable<long long>(file);

	file = createFileStream(std::ios::out);

	for (auto i = 0; i < sets; i++)
		file << getInversionsCount(arrays[i], new long long[arrays[i][0] - 1], 1, arrays[i][0] - 1) << std::endl;

	file.close();

	return 0;
}

template <typename T> int getInversionsCount(T* leftArray, T* rightArray, const int leftIndex, const int rightIndex)
{
	const auto middleIndex = (rightIndex + leftIndex) / 2;
	auto inversionsCount = 0;

	if (rightIndex > leftIndex)
		inversionsCount = getInversionsCount(leftArray, rightArray, leftIndex, middleIndex) + 
			getInversionsCount(leftArray, rightArray, middleIndex + 1, rightIndex) + 
			mergeArrays(leftArray, rightArray, leftIndex, middleIndex + 1, rightIndex);

	return inversionsCount;
}

template<typename T> int mergeArrays(T* leftArray, T* rightArray, const int leftIndex, const int middleIndex, const int rightIndex)
{
	auto inversionsCount = 0, leftSubarrayIndex = leftIndex, rightSubarrayIndex = middleIndex, mergedIndex = leftIndex;

	while (leftSubarrayIndex < middleIndex && rightSubarrayIndex <= rightIndex)
	{
		if (leftArray[leftSubarrayIndex] <= leftArray[rightSubarrayIndex])
			rightArray[mergedIndex++] = leftArray[leftSubarrayIndex++];
		else
		{
			rightArray[mergedIndex++] = leftArray[rightSubarrayIndex++];
			inversionsCount += middleIndex - leftSubarrayIndex;
		}
	}

	while (leftSubarrayIndex < middleIndex)
		rightArray[mergedIndex++] = leftArray[leftSubarrayIndex++];

	while (rightSubarrayIndex <= rightIndex)
		rightArray[mergedIndex++] = leftArray[rightSubarrayIndex++];

	for (leftSubarrayIndex = leftIndex; leftSubarrayIndex <= rightIndex; leftSubarrayIndex++)
		leftArray[leftSubarrayIndex] = rightArray[leftSubarrayIndex];

	return inversionsCount;
}