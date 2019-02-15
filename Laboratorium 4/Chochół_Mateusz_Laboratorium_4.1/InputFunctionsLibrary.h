#ifndef INPUTFUNCTIONSLIBRARY_H
#define INPUTFUNCTIONSLIBRARY_H

#include <string>

enum greaterOrLessThanSign { GREATER, LESS };

int convertStringToInt(std::string numberAsString);

void checkNumberValue(int &value, int limit, greaterOrLessThanSign sign);

void checkNumberValue(int &value, int lowerLimit, int upperLimit);

int getNumber();

void exitProgram();

#endif // !INPUTFUNCTIONSLIBRARY_H
