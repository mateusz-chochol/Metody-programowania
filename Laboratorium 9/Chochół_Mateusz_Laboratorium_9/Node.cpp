#include "Node.h"

/*
 * Zmienne statyczne klasy wymagaja inicjalizacji poza dekleracja klasy i teoretycznie mozna by umiescic je w pliku .h,
 * ale w praktyce zaczna pojawiac sie wtedy linker errory w zwiazku z tym, ze kazdy plik includujacy Node.h bedzie mial do tych zmiennych dostep
 * i kompilator zwariuje, bo nie wiedzial, ktore z tych wszystkich zmiennych to te "prawdziwe", dlatego tez trzeba zrobic to w osobnym pliku .cpp
 */

int Node::_maxValue;
int Node::_maxWeight;
std::vector<Object> Node::_allObjects;