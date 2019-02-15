#ifndef CTABLICA_H
#define CTABLICA_H

#include "ComparisonType.h"
#include <string>

class CTablica
{
	long long _numberOfSwaps = 0;
	long long _numberOfComparisons = 0;

protected:
	void swap(int &firstNumber, int &secondNumber)
	{
		_numberOfSwaps++;

		std::swap(firstNumber, secondNumber);
	}

	bool compare(const int firstNumber, const int secondNumber, const ComparisonType comparison)
	{
		_numberOfComparisons++;

		if (comparison == Less)
			return firstNumber < secondNumber;
		if (comparison == Greater)
			return firstNumber > secondNumber;
		if (comparison == LessOrEqual)
			return firstNumber <= secondNumber;
		if (comparison == GreaterOrEqual)
			return firstNumber >= secondNumber;

		return firstNumber == secondNumber;
	}

public:
	virtual void sort(int* table, int lowestIndex, int highestIndex) = 0;

	virtual std::string getName() = 0;

	long long getNumberOfSwaps() const { return _numberOfSwaps; }

	long long getNumberOfComparisons() const { return _numberOfComparisons; }

	void zeroSwapsAndComparisons()
	{
		_numberOfSwaps = 0;
		_numberOfComparisons = 0;
	}
};

#endif