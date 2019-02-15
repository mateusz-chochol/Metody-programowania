#include "functionsLibrary.h"
#include <iostream>
#include <fstream>

/*
- Funkcja tworzy fileStreama w trybie odczytu.
- zbiera pierwsza linijke z podanego przy tworzeniu fileStreama pliku i konwertuja ja do inta sprawdzajac jednoczesnie, czy to faktycznie tylko liczba, a nie np "abc", lub "2a".
- sprawdza, czy liczba zestawow miesci sie w limitach (minimum 1, maks 32769).
- potem getlinem leci przez caly plik liczac ile jest linijek i jako, ze jeden zestaw sklada sie z 4 linijek, to linijek powinno byc 4 razy tyle (-1) ile wynosi liczba zestawow.
- jezeli cos sie nie zgadza - wychodzimy z programu.
- jezeli wszystko jest okej, wracamy do poczatku pliku i przeskakujemy linijke dalej (juz ja czytalismy wczesniej - to liczba zestawow).
- tworzymy dynamiczne tablice tablic long longow, w ktorych bedziemy trzymac: w jednej liczby, w ktorych bedziemy szukac i w drugiej, liczby, ktorych bedziemy szukac.
- zbieramy do tablic odpowiednie zestawy danych i przy okazji patrzymy, czy ten pierwszy jest uporzadkowany (bo powinien byc), jesli nie - wychodzimy.
- zamykamy plik i otwieramy go ponownie w trybie zapisu
- wpisujemy do pliku "out.txt" w nawiasie liczbe znalezionych takich samych liczb, jak ta, ktora szukamy oraz index, pod ktora te konkretna liczbe moznaby w pierwszej tablicy znalezc.
- nastepnie, linijke nizej wypisujemy (po usunieciu duplikatow) wszystkie liczby z pierwszej tablicy (maks 200, po 50 w linijce) oraz robimy dwie linijki odstepu na nowy zestaw.
- na koniec zamykamy plik i konczymy program.
*/

int main() 
{
	std::fstream file = createFileStream(std::ios_base::in);

	std::string setsAsString;
	std::getline(file, setsAsString);
	
	int sets = convertStringToLongLong(setsAsString);
	checkNumberValue(sets, 0, 32769);

	int actuallNumberOfLines = 0;

	for (; std::getline(file, setsAsString); ) 
		actuallNumberOfLines++;

	if (actuallNumberOfLines / 4 != sets)
		exitProgram();

	file.clear();
	file.seekg(0, std::ios::beg);
	std::getline(file, setsAsString);

	long long **tablesWithNumbers = new long long*[sets];
	long long **tablesWithNumbersToFind = new long long*[sets];

	for (int i = 0; i < sets; i++)
	{
		tablesWithNumbers[i] = getNumbersTable(file);
		checkOrder(tablesWithNumbers[i], tablesWithNumbers[i][0]);
		
		tablesWithNumbersToFind[i] = getNumbersTable(file);
	}

	file.close();

	file = createFileStream(std::ios_base::out);

	for (int i = 0; i < sets; i++)
	{
		for (int j = 1; j < tablesWithNumbersToFind[i][0]; j++)
		{
			file << "(" << countSameElements(tablesWithNumbers[i], tablesWithNumbers[i][0], tablesWithNumbersToFind[i][j]);
			file << " " << findIndex(tablesWithNumbers[i], tablesWithNumbers[i][0], tablesWithNumbersToFind[i][j]) << ") ";
		}
		
		file << '\n';

		getRidOfDuplicates(tablesWithNumbers[i], tablesWithNumbers[i][0]);

		if (tablesWithNumbers[i][0] > 200)
			tablesWithNumbers[i][0] = 200;

		for (int j = 1; j < tablesWithNumbers[i][0]; j++) 
		{
			if (j % 50 == 0 && j >= 50)
				file << '\n';

			file << tablesWithNumbers[i][j] << " ";
		}

		file << '\n' << '\n';
	}

	file.close();

	return 0;
}