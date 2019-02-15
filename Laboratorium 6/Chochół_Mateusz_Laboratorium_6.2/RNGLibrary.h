#ifndef RNGLIBRARY_H
#define RNGLIBRARY_H
#include <vector>

std::vector<int> linearCongruentialGenerator(int upperBoundary, int numberOfNumbers);

std::vector<int> additiveCongruentialGenerator(int upperBoundary, int numberOfNumbers);

std::vector<int> shufflingGenerator(int upperBoundary, int numberOfNumbers);

int getSeed(int upperBoundary);

int getRandomNumber(int upperBoundary);

int getGrowth(int number);

int getMultiplier(int modulo);

#endif //!RNGLIBRARY_H
