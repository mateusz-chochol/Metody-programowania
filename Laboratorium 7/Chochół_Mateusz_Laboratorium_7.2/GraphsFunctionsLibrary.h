#ifndef GRAPHSFUNCTIONSLIBRARY_H
#define GRAPHSFUNCTIONSLIBRARY_H
#include <vector>

void getNeighborhood(std::fstream &file, std::vector<std::vector<int>> &matrix, int numberOfEgdes, int numberOfVertexes);

void getNeighborhood(std::fstream &file, int** matrix, int numberOfEgdes, int numberOfVertexes);

void adjacencyListArray(std::fstream &file);

void graphsOnVectors(std::fstream &file);

void graphsOnArrays(std::fstream &file);

int getNumberOfVertexes(std::fstream &file, int numberOfEgdes);

int extractPairBiggerVertex(std::fstream &file);

#endif // !GRAPHSFUNCTIONSLIBRARY_H
