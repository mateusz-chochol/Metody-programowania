#include "AlgorithmsLibrary.h"
#include <cmath>
#include <vector>

/*
* Gets the biggest common divisor of two given numbers
*/
int greatesCommonDivisor(const int a, const int b)
{
	if (b == 0)
		return a;

	return greatesCommonDivisor(b, a%b);
}

/*
* Gets all distinct prime factors of a given number.
*/
std::vector<int> getPrimeFactors(int number)
{
	std::vector<int> factors;

	if (number % 2 == 0)
	{
		factors.push_back(2);

		while (number % 2 == 0)
			number /= 2;
	}

	for (auto i = 3; i < sqrt(number); i += 2)
	{
		if (number % i == 0)
		{
			factors.push_back(i);

			while (number % i == 0)
				number /= i;
		}
	}

	if (number > 2)
		factors.push_back(number);

	return factors;
}
