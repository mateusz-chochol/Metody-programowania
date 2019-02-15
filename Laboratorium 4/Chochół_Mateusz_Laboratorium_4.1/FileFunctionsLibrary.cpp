#include "FileFunctionsLibrary.h"
#include "InputFunctionsLibrary.h"
#include <iostream>
#include <string>
#include <fstream>

/*
Creates and returns a file stream open in a given mode (for now only in and out are possible)
Gives 3 tries to type in a file name if it's looking for an existing file
Creates a file called "out.txt" if it's creating a file
*/
std::fstream createFileStream(std::ios_base::openmode streamType)
{
	if (streamType == std::ios_base::in)
	{
		std::string fileName;
		int numberOfTries = 0;

		while (numberOfTries < 3)
		{
			std::cout << "Type in the correct file name (.txt): ";
			std::getline(std::cin, fileName);

			if (checkIfFileExists(fileName) && checkFileExtension(fileName))
			{
				std::fstream fileStream(fileName, std::ios_base::in);
				return fileStream;
			}
			else if (checkIfFileExists(fileName + ".txt"))
			{
				std::fstream fileStream(fileName + ".txt", std::ios_base::in);
				return fileStream;
			}

			std::cout << "Cannot find the file." << std::endl;
			numberOfTries++;
		}

		std::cout << "File cannot be found." << std::endl;
		getchar();
		exit(0);
	}
	else if (streamType == std::ios_base::out)
	{
		std::fstream fileStream("out.txt", std::ios_base::out);
		return fileStream;
	}
	else
		exitProgram();
}

/*
Returns true if file extension is .txt, false otherwise
*/
bool checkFileExtension(std::string fileName)
{
	int numberOfLetters = fileName.length() - 1;

	if (fileName[numberOfLetters] == 't' && fileName[numberOfLetters - 1] == 'x' && fileName[numberOfLetters - 2] == 't' && fileName[numberOfLetters - 3] == '.')
		return true;

	return false;
}

/*
Returns true if it was able to find a file with a given name, false otherwise
*/
bool checkIfFileExists(std::string fileName)
{
	std::ifstream fileStream(fileName);
	return fileStream.good();
}