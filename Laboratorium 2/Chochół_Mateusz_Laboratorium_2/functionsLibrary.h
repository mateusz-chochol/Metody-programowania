#ifndef FUNCTIONSLIBRARY_H
#define FUNCTIONSLIBRARY_H

#include <fstream>
#include <string>

#pragma region Naglowki funkcji sprawdzajacych poprawnosc danych

/*
Funkcja sprawdzajaca, czy dana liczba miesci sie w podanych granicach.
Potrzebuje do tego danej liczby oraz dolnej granicy i gornej granicy.
*/
void checkNumberValue(long long, long long, long long);

/*
Funkcja sprawdzajaca, czy rozszerzenie podanego pliku jest poprawne (czy to .txt.).
Potrzebuje do tego nazwy pliku.
*/
bool checkFileExtension(std::string);

/*
Funkcja sprawdzajaca czy plik istnieje.
Potrzebuje do tego nazwy pliku.
*/
bool checkIfFileExists(std::string);

/*
Funkcja sprawdzajaca, czy podane wartosci sa posortowane.
Potrzebuje do tego tablicy i jej rozmiaru.
(jesli wartosci sa nieposortowane to program jest wylaczany z informacja o zlych danych wejsciowych. Moglyby byc sortowane jakims QuickSortem, ale w zadaniu nic o tym nie bylo).
*/
void checkOrder(long long*, int);

#pragma endregion

#pragma region Naglowki funkcji przygotowujacych program do dzialania

/*
Funkcja zwracajaca fileStreama otwartego w podanym przy wywolaniu funkcji trybie i sprawdzajaca, czy plik istnieje (dla trybu odczytu).
Potrzebuje do tego jedynie trybu otwarcia pliku, gdyz sama potem, w srodku, zajmuje sie ewentualna potrzeba wpisania nazwy pliku.
*/
std::fstream createFileStream(std::ios_base::openmode);

/*
Funkcja zwracajaca tablice wypelniona liczbami znajdujacymi sie w pewnych linijkach w pliku.
Potrzebuje do tego otwartego pliku.
*/
long long *getNumbersTable(std::fstream&);

#pragma endregion

#pragma region Naglowki glownych funkcji programu

/*
Funkcja liczaca ile takich samych elementow jak podana wartosc wystepuje w tablicy.
Potrzebuje do tego tablicy, jej rozmiaru i danej wartosci.
*/
int countSameElements(long long*, int, long long);

/*
Funkcja szukajaca metoda wyszukiwania interpolacyjnego pod jakim indeksem w tablicy mozna znalezc dana wartosc.
Potrzebuje do tego tablicy, jej rozmiaru i danej wartosci.
*/
int findIndex(long long*, int, long long);

/*
Funkcja usuwajaca duplikaty tych samych wartosci z tablicy.
Potrzebuje do tego tablicy i jej rozmiaru.
*/
void getRidOfDuplicates(long long*, int);

/*
Funkcja wylaczajaca program i wyrzucajac informacje i blednych danych wejsciowych.
*/
void exitProgram();

#pragma endregion

#pragma region Naglowki funkcji pomocniczych

/*
Funkcja znajduje ostatni indeks, pod ktorym wystepuje dana wartosc.
Potrzebuje do tego tablicy, najmniejszego mozliwego indeksu, najwiekszego mozliwego indeksu, wielkosci tablicy i szukanej wartosci.
*/
int lastAppearance(long long*, int, int, int, long long);

/*
Funkcja znajduje pierwszy indeks, pod ktorym wystepuje dana wartosc.
Potrzebuje do tego tablicy, najmniejszego mozliwego indeksu, najwiekszego mozliwego indeksu i szukanej wartosci.
*/
int firstAppearance(long long*, int, int, long long);

/*
Funkcja konwertujaca stringa to long longa jednoczesnie sprawdzajac czy konwersji na pewno poddawana jest liczba (czy nie jest to czasem jakis dziwny ciag znakow jak np. "21asd/3", ...
... w takim wypadku program jest wylaczany z informacja o blednych danych wejsciowych).
*/
long long convertStringToLongLong(std::string);

#pragma endregion

#endif // !FUNCTIONSLIBRARY_H