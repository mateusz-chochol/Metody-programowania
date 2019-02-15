#include "FileFunctionsLibrary.h"
#include "GraphsFunctionsLibrary.h"

/*
 * Krawedzie sa ustawione w pionie (rzedy), a wierzcholki poziomo (kolumny), np:
 *			v1 v2 v3 v4 v5
 *	e1   
 *	e2	
 *	e3			
 *	e4	  jakies dane 
 *	e5       macierzy
 *	e6
 *	e7
 *	e8
 */

int main()
{
	auto file = createFileStream(std::ios::in);

	//graphsOnArrays(file);
	//graphsOnVectors(file);

	return 0;
}