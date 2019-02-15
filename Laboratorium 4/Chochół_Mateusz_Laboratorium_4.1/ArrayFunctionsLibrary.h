#ifndef ARRAYFUNCTIONSLIBRARY_H
#define ARRAYFUNCTIONSLIBRARY_H

int *getNumbersTable(std::fstream &file);

int kadaneAlgorithm(int *table, int size);

int maximumSubarray(int **table, int horizontal, int vertical);

int findIndex(long long* table, int size, long long element);

int countSameElements(long long *table, int size, long long element);

int lastAppearance(long long *table, int lowestIndex, int highestIndex, int size, long long element);

int firstAppearance(long long *table, int lowestIndex, int highestIndex, long long element);

#endif // !ARRAYFUNCTIONSLIBRARY_H