#ifndef KNAPSACKFUNCTIONSLIBRARY_H
#define KNAPSACKFUNCTIONSLIBRARY_H
#include "Object.h"
#include <vector>

std::vector<Object> getAllObjects(std::fstream &file);

Object getObject(const std::string& line);

#endif // !KNAPSACKFUNCTIONSLIBRARY_H
