#include "AlgorithmsLibrary.h"
#include "RNGLibrary.h"
#include <ctime>
#include <iostream>
#include "InputFunctionsLibrary.h"

#pragma region LCG

/*
 * Generates random numbers using Linear Congruential Random Numbers Generator
 */
std::vector<int> linearCongruentialGenerator(const int upperBoundary, const int numberOfNumbers)
{
	const auto modulo = upperBoundary + 1, multiplier = getMultiplier(modulo), seed = getSeed(upperBoundary), growth = getGrowth(modulo);

	std::vector<int> randomNumbers;
	randomNumbers.push_back((multiplier * seed + growth) % modulo);

	for (auto i = 1; i < numberOfNumbers; i++)
		randomNumbers.push_back((multiplier * randomNumbers.at(i - 1) + growth) % modulo);

	return randomNumbers;
}

/*
 * Gets seed constant for Linear Congruential Random Numbers Generator
 */
int getSeed(const int upperBoundary)
{
	auto seed = 0;

	std::cout << "If you want to use custom seed, type it here, \nif not, type a value below 1 or greater than your upper boundary: ";
	seed = getNumber();

	return seed < 0 ? getRandomNumber(upperBoundary) : seed;
}

/*
* Gets growth constant for Linear Congruential Random Numbers Generator
*/
int getGrowth(const int number)
{
	for (auto i = number; i > 1; i--)
		if (greatesCommonDivisor(i, number) == 1)
			return i;

	return 1;
}

/*
* Gets multiplier constant for Linear Congruential Random Numbers Generator
*/
int getMultiplier(const int modulo)
{
	auto highestPower = 0;
	std::vector<int> potentialMultipliers, betterMultipliers, bestMultipliers;

	for (auto multiplier = 2; multiplier < modulo; multiplier++)
		for (auto power = 1; power < modulo; power++)
			if (long long(pow(multiplier, power)) % modulo == 1 && power >= highestPower)
			{
				if (power > highestPower)
				{
					potentialMultipliers.clear();
					highestPower = power;
				}

				potentialMultipliers.push_back(multiplier);
			}

	for (auto multiplier : potentialMultipliers)
	{
		auto multipleOfModuloFactors = true;

		for (auto factor : getPrimeFactors(modulo))
			if (multiplier % factor != 0)
				multipleOfModuloFactors = false;

		if (multipleOfModuloFactors)
		{
			if (modulo % 4 != 0 || (modulo % 4 == 0 && multiplier - 1 % 4 == 0))
				bestMultipliers.push_back(multiplier);
			else
				potentialMultipliers.push_back(multiplier);
		}
	}

	if (!bestMultipliers.empty())
		return bestMultipliers.back();

	if (!potentialMultipliers.empty())
		return potentialMultipliers.back();

	return 1;
}

#pragma endregion 

#pragma region ACG

/*
 * Generates random numbers using Additive Congruential Random Numbers Generator
 */
std::vector<int> additiveCongruentialGenerator(const int upperBoundary, const int numberOfNumbers)
{
	const auto modulo = getRandomNumber(upperBoundary);
	auto tablePairFirstIndex = 1, tablePairSecondIndex = numberOfNumbers;
	
	auto randomNumbers = linearCongruentialGenerator(upperBoundary, numberOfNumbers);
	std::reverse(randomNumbers.begin(), randomNumbers.end());

	for (auto i = 0; i < numberOfNumbers; i++)
	{	
		tablePairFirstIndex--, tablePairSecondIndex--;

		randomNumbers.at(tablePairSecondIndex) = (randomNumbers.at(tablePairFirstIndex) + randomNumbers.at(tablePairSecondIndex)) % modulo;

		if (tablePairSecondIndex == 0)
			tablePairSecondIndex = numberOfNumbers;
		else if (tablePairFirstIndex == 0)
			tablePairFirstIndex = numberOfNumbers;
	}

	return randomNumbers;
}

#pragma endregion 

#pragma region Shuffling

/*
 * Generates random numbers using shuffling method random numbers generator
 */
std::vector<int> shufflingGenerator(const int upperBoundary, const int numberOfNumbers)
{
	auto randomNumbers = linearCongruentialGenerator(upperBoundary, 2 * numberOfNumbers + 1);
	std::vector<int> shuffledRandomNumbers;

	auto index = numberOfNumbers, randomNumber = randomNumbers.at(numberOfNumbers);

	while (shuffledRandomNumbers.size() < numberOfNumbers)
	{
		const auto randomIndex = numberOfNumbers * randomNumber / upperBoundary;

		randomNumber = randomNumbers.at(randomIndex);
		randomNumbers.at(randomIndex) = randomNumbers.at(++index);
		
		shuffledRandomNumbers.push_back(randomNumber);
	}

	return shuffledRandomNumbers;
}

#pragma endregion 

#pragma region Common functions

/*
 * Returns pseudo random number
 */
int getRandomNumber(const int upperBoundary)
{
	return time(nullptr) * int(log(upperBoundary)) % upperBoundary;
}

#pragma endregion 