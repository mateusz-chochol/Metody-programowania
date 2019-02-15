#include <iostream>
#include <string>
#include <fstream>

int getNumber();
void getSubsets(std::ofstream&, int*, int, int);

/*
Nad funkcja "getSubsets(...)" jest cala sciana tekstu tlumaczaca jak dziala algorytm (wraz z przykladami). Jesli to za duzo, to prosze potraktowac to jako cos dla mnie, a jako komentarz ...
... do zadania przyjac to co napisze teraz:
Funkcja "getSubsets(...)" na podstawie pierwszego podzbioru, co iteracje petli zwieksza jeden element jednoczesnie dostosowujac pozostale. 
Element zwiekszany jest tak dlugo, az nie bedzie wiekszy niz powinien (dla ostatniego limitem jest najwiekszy w zbiorze glownym, dla pozostalych: element, ktory jest po nich), ...
... gdy taka sytuacja zajdzie zwiekszany jest element wczesniejszy, a ten zostaje zmniejszony tak, by byl jak najmniejszy, jednak wciaz wiekszy od poprzedniego.
*/

int main() 
{
	int numberOfElements = getNumber(), subsetLength = getNumber(), tries = 1;

	while (subsetLength > numberOfElements)
	{
		if (tries > 2) 
		{
			std::cout << "Wrong data, exiting program." << std::endl;
			getchar();
			exit(0);
		}

		std::cout << "!(subset length <= set length)" << std::endl;
		numberOfElements = getNumber();
		subsetLength = getNumber();
	
		tries++;
	}
		
	int *set = new int[numberOfElements]();
	int *subset = new int[subsetLength]();

	for (int i = 1; i <= numberOfElements; i++)
		set[i] = i + 1;
	
	std::ofstream file("Program_02.txt");
	
	getSubsets(file, subset, numberOfElements, subsetLength);

	file.close();

	getchar();
	getchar();

	return 0;
}

/*
Funkcja zapisuje pierwszy podzbior (pierwsze k elementow ze zbioru glownego) na samym poczatku, nastepnie go wypisuje, a potem dalej juz pracuje na jego podstawie.
Na poczatku kazdej petli, ktorej warunkiem jest by index pierwszego elementu do zmiany odpowiadal jakiemus rzeczywistemu elementowi, wypisywany jest kolejny podzbior.
(w zadaniu indeksu zaczynaja sie od 1 i koncza na "n", a nie od 0 i na "n - 1", bo tak bylo w pseudokodzie i w sumie calkiem fajnie to wyglada)
Potem sprawdzane jest, czy ostatni element z podzbioru (dla {1, 2, 3} byloby to 3) jest jednoczesnie najwiekszym elementem z calego zbioru:
- Jesli nie, to ustalamy pozycje pierwszego elementu do zmiany wlasnie na ten ostatni element (czyli zmieniamy tylko jego - jest pierwszy i ostatni)
- Jesli tak, to obnizamy o 1 pozycje pierwszego elementu do zmiany (np dla danych wejsciowych 5 i 3, i podzbiorze {1, 3, 5} zmianie teraz mialoby ulec element "3" i "5").
Nastepnie, jezeli indeks pierwszego elementu do zmiany odpowiada jakiemus rzeczywistemu elementowi, to rozpoczynana jest petla for, ktora pracuje tak dlugo, az przeleci przez ...
... wszystkie elementy, ktore musi zmienic (jezeli ma zmienic tylko ostatni, to przepuszczana jest raz, jezeli ma zmienic przedostatni, to zmienia takze ostatni czyli przepuszczana jest 2 razy itd.)
W petli natomiast, obliczana jest nowa wartosc dla danego elementu.
Zalezy ona od wartosci pierwszego elementu do zmiany, liczby elementow do zmiany i tego, ktory element od konca to jest.
Element ma byc wiekszy niz poprzednio byl (stad +1) oraz w razie potrzeby ma zostac zmniejszony na tyle by byc najmniejszym mozliwym, jednak wciaz wiekszym od elementu przed nim
(potrzeba zachodzi, gdy zmienany jest takze element przed nim).
Przykladowo, dla danych wejsciowych 5 i 3, oraz podzbioru {1, 2, 4} indeks pierwszego elementu do zmiany jest wciaz rowny indeksowi ostatniego elementu, a co za tym idzie tylko ostatni ...
... ma zostac zmieniony: wtedy rowniez "i" jest rowne indeksowi ostatniego elementu przez co wyrazenie "i - indexOfTheFirstElementToChange" sie zeruje, a wyrazenie ...
... "subset[i] = subset[indexOfTheFirstElementToChange] + 1" sprowadza sie do "subset[indexOfTheFirstElementToChange]++" czyli jedynie do inkrementacji ostatniego elementu.
Innym razem, dla podzbioru {1, 4, 5}, zmienna "indexOfTheFirstElementToChange" = 1 i wtedy zmieniane sa wszystkie elementy zaczynaj¹c od tego z indeksem 1 (czyli po prostu wszystkie).
W pierwszej petli wyrazenie ma postac "subset[3] = subset[1] + 3 - 1 + 1 = 4", w drugiej "subset[2] = subset[1] + 2 - 1 + 1 = 3", a w trzeciej "subset[1] = subset[1] + 1 - 1 + 1 = 2" i taki jest tez ...
... nastepny podzbior po {1, 4, 5}, czyli {2, 3, 4}.
*/
void getSubsets(std::ofstream &file, int *subset, int biggestElementInSet, int subsetLength) 
{
	for (int i = 1; i <= subsetLength; i++) 
		subset[i] = i;

	int indexOfTheFirstElementToChange = subsetLength;

	while (indexOfTheFirstElementToChange >= 1) 
	{
		for (int i = 1; i <= subsetLength; i++)
			file << subset[i] << " ";

		if (subset[subsetLength] == biggestElementInSet)
			indexOfTheFirstElementToChange--;
		else
			indexOfTheFirstElementToChange = subsetLength;

		std::cout << indexOfTheFirstElementToChange << std::endl;

		if (indexOfTheFirstElementToChange >= 1)
			for (int i = subsetLength; i >= indexOfTheFirstElementToChange; i--)
				subset[i] = subset[indexOfTheFirstElementToChange] + i - indexOfTheFirstElementToChange + 1;

		file << std::endl;
	}
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