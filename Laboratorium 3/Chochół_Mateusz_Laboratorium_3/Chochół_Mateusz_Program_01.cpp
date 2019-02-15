#include <iostream>
#include <fstream>
#include <string>

int getNumber();

/*
Funkcja liczaca kolejne kombinacje binarne ciagu o zadanej wielkosci poprzez zmienianie tylko jednego elementu z poprzedniej kombinacji.
Sposob w jaki liczy bit, ktory nalezy zmienic polega na potegach dwojki. 
Bity zmieniane sa gdy liczba iteracji petli bedzie jakas liczba parzysta. Konkretniej, im wieksza potega liczby 2, tym pozniejszy bit jest zmieniany (nie do konca, ale to prawie prawda).
Wzor: k*2^n - 2^(n-1) mowi dla jakiej liczby krokow, bit o pozycji "n" zostanie zmieniony (k to dowolna liczba naturalna wieksza od 0).
Np. pierwszy bit zmieniony zostanie zmieniony przy kroku, ktory bedzie rowny k*2^1 - 2^0 (1, 3, 5... itd.), drugi przy k*2^2 - 2^1 (2, 6, 10... itd.), trzeci przy k*2^3 - 2^2 (4, 12, 20... itd.) itd. 
Warunek jest taki, ze zmiana dotyczy tylko jednego bitu i tak np przy kroku k*2^4 - 2^3 (8, 24, 40 itd.) zmieniany jest wy³¹cznie bit czwarty (pozosta³e nie)
Nie mam pojecia dlaczego liczba krokow to akurat k*2^n - 2^(n-1), a nie po prostu k*2^n. Podejrzewam, ze ma to jakis zwiazek z tym, ze 2^0 = 1, ale jezeli tak, to nie wiem jaki. :/

Jeszcze jedna rzecz: wydaje mi sie, ze niepotrzebny byl if, ktory dodal Pan pod koniec petli, wiec go usunalem. Zmienna "indexToChange" (w pseudokodzie bylo to "p") nigdy nie bedzie ...
... wieksza niz [rozmiar tablicy - 1], bo do tego potrzeba by bylo rowne dwa razy tyle przejsc petli ile bylo dotychczas (dla kombinacji 5 elementow normalnie przejsc jest 32, trzeba by wiec bylo 
... ich az 64, zeby program sie posypal, a przeciez juz przy 33 petla sie przerwie). Z kolei dla niewielkich danych sprawa wyglada tak: dla 0 petla w ogole sie nie zacznie, dla 1 "indexToChange" ...
... nie zostanie zinkrementowane (bo to liczba nieparzysta), a dla 2 potrzeba by juz az 4 przejsc by program sie posypal (a petla skonczy sie przy 3).
*/

int main() 
{
	int numberOfSets = getNumber();

	int *table = new int[numberOfSets](), printedSets = 0, indexToChange = 0, positionOfBitToChange = 1;
	
	std::ofstream file("Program_01.txt");

	while (indexToChange < numberOfSets)
	{
		for (int i = 0; i < numberOfSets; i++)
			file << table[i] << " ";

		file << std::endl;

		printedSets++;
		indexToChange = 0;
		positionOfBitToChange = printedSets;

		while (positionOfBitToChange % 2 == 0)
		{
			positionOfBitToChange /= 2;
			indexToChange++;
		}

		table[indexToChange] = 1 - table[indexToChange];
	}

	file.close();

	return 0;
}

int getNumber()
{
	std::string setsAsString;
	std::getline(std::cin, setsAsString);

	int letterIndex = 0;

	while (setsAsString.length() == 0 || letterIndex < setsAsString.length())
	{
		if (setsAsString.length() == 0) 
		{
			std::cout << "!(number)" << std::endl;
			std::getline(std::cin, setsAsString);
		}
		else if (setsAsString[letterIndex] < '0' || setsAsString[letterIndex] > '9')
		{
			std::cout << "!(number)" << std::endl;
			std::getline(std::cin, setsAsString);
			letterIndex = 0;
		}
		else
			letterIndex++;
	}

	return std::stoi(setsAsString);
}