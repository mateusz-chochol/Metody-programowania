#ifndef GRAPHSFUNCTIONSLIBRARY_H
#define GRAPHSFUNCTIONSLIBRARY_H
#include <fstream>
#include <vector>

void getNeighborhood(std::fstream &file, std::vector<std::vector<int>> &matrix, int numberOfEgdes, int numberOfVertexes);

void getNeighborhood(std::fstream &file, int** matrix, int numberOfEgdes, int numberOfVertexes);

void graphsOnVectors(std::fstream &file);

void graphsOnArrays(std::fstream &file);

int getNumberOfVertexes(std::fstream &file, int numberOfEgdes);

int extractPairBiggerVertex(std::fstream &file);

#endif // !GRAPHSFUNCTIONSLIBRARY_H
