#ifndef STACKIMPLEMENTATIONS_H
#define STACKIMPLEMENTATIONS_H

enum StackImplementationType { ARRAY, LIST, STACK };

/*
Parent class of any stack implementation (half abstract)
*/
class StackImplementation;

/*
Array implementation of stack
*/
class StackOnArray;

/*
List implementation of stack
*/
class StackOnLinkedList;

/*
std::stack implementation of stack (hmm)
*/
class StackOnSTDSTACK;

/*
Displays various stack functions.
*/
void stackDemo(int *numbers, StackImplementationType stackType);

#endif // !STACKIMPLEMENTATIONS_H

