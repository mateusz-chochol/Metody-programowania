#include "StackImplementations.h"
#include "FileFunctionsLibrary.h"
#include "ArrayFunctionsLibrary.h"
#include <iostream>
#include <fstream>

int main()
{
	std::fstream file = createFileStream(std::ios_base::in);
	int *numbers = getNumbersTable(file);
	std::cout << std::endl;

	//stackDemo(numbers, ARRAY);
	//stackDemo(numbers, LIST);
	//stackDemo(numbers, STACK);

	getchar();
	return 0;
}