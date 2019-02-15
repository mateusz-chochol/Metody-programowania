#ifndef HUFFMANFUNCTIONSLIBRARY_H
#define HUFFMANFUNCTIONSLIBRARY_H

#include "Node.h"
#include <vector>
#include <memory>

void huffmanCoding(std::fstream& file, std::unique_ptr<Node>& node, const std::string& binaryRepresentation = "");

void sortByFrequency(std::vector<std::unique_ptr<Node>>& nodes, int left, int right);

std::unique_ptr<Node>& createTree(std::vector<std::unique_ptr<Node>>& nodes);

std::vector<std::unique_ptr<Node>> getCharactersAsNodes(std::fstream& file);

#endif // !HUFFMANFUNCTIONSLIBRARY_H