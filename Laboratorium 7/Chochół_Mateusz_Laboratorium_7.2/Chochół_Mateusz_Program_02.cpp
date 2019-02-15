#include "FileFunctionsLibrary.h"
#include "GraphsFunctionsLibrary.h"

/*
 * Program przy kazdej napotkanej parze wierzcholkow tworzy krawedzie w dwie strony (z 'a' do 'b' i z 'b' do 'a'). Lista uzywana w programie
 * stworzona jest na klasie. Uznalem, ze nie ma sensu robic drugiej wersji dla structa, skoro roznica miedzy nimi w C++ polega jedynie na 
 * hermetyzacji danych.
 */
int main()
{
	auto file = createFileStream(std::ios::in);
	adjacencyListArray(file);

	return 0;
}