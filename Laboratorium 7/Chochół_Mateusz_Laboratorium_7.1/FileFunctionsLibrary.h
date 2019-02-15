#ifndef FILEFUNCTIONSLIBRARY_H
#define FILEFUNCTIONSLIBRARY_H

#include <fstream>

std::fstream createFileStream(std::ios_base::openmode streamType);

bool checkFileExtension(std::string fileName);

bool checkIfFileExists(std::string fileName);

#endif // !FILEFUNCTIONSLIBRARY_H