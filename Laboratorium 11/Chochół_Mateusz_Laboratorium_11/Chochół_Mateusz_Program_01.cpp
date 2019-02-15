#include "FileFunctionsLibrary.h"
#include "HuffmanFunctionLibrary.h"

/*
 * Program zaczyna od otwarcia pliku o podanej nazwie
 * Pobiera z niego informacje o znakach i czestotliwosci ich wystapien oraz zapisuje kazdy z nich jako "Node"
 * Z zapisanych w vectorze Node'ow tworzy drzewo huffmana i zapisuje polozenie glownego korzenia
 * Otwiera plik do zapisu
 * Biegajac po drzewie huffmana w gore i w dol zapisuje kazdy znak...
 * wraz z tworzaca sie podczas tego biegania jego binarna reprezentacja
 * Podczas calego dzialania obslugiwane sa wszelkie mozliwe nietypowe sytuacje 
 * (jak np proba zapisu w pliku, ktorego tryb ustawiony jest na odczyt itp.)
 */

int main()
{
	auto file = createFileStream(std::ios::in);
	auto nodes = getCharactersAsNodes(file);
	auto root = std::move(createTree(nodes));

	file = createFileStream(std::ios::out);
	huffmanCoding(file, root);

	return 0;
}