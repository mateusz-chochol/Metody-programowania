#ifndef ONPFUNCTIONSLIBRARY_H
#define ONPFUNCTIONSLIBRARY_H

#include "OperatorClass.h"
#include <map>
#include <stack>

void infixToPostfix(std::string& line, const std::map<char, Operator>& operators);

void postfixToInfix(std::string& line, const std::map<char, Operator>& operators);

bool canOperatorBePushed(const std::stack<Operator>& stack, const std::map<char, Operator>& operators, char character);

#endif // !ONPFUNCTIONSLIBRARY_H