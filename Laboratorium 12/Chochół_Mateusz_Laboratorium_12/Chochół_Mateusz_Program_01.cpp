#include "FileFunctionsLibrary.h"
#include "CSortTablicy.h"

int main()
{
	auto file = createFileStream(std::ios::out);

	CSortTablicy::ultimateDemo(file);

	return 0;
}
