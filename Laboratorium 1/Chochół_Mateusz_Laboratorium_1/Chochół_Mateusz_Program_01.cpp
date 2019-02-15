//komentarze po polsku, bo nie wiem czy mozna po angielsku

#include <iostream>
#include <conio.h>

using namespace std;

enum greaterOrLessThanSign { GREATER, LESS };

/*algorytm Kadane'a, ktory pozwala na obliczenie maksymalnej podtablicy w tablicy jednowymiarowej
- sumuje on po kolei liczby w tabeli tak dlugo, az owa suma jest wieksza od 0 - gdy jest mniejsza zaczyna od nowa w miejscu, w ktorym przerwal
- w miedzyczasie sprawdza, czy suma aktualnej sekwencji jest wieksza niz najwieksza dotychczas policzona
- poczatkowa wartosc biggestNumber to akurat -32768, bo to najmniejsza mozliwa wartosc dla liczby znajdujacej sie w tablicy (-2^15)*/
int kadaneAlgorithm(int *table, int size) 
{
	int currentMaximumSum = 0, currentSequenceSum = 0, biggestNumber = -32768;
	bool allNumbersNegative = true;
	
	for (int i = 0; i < size; i++)
	{
		currentSequenceSum += table[i];

		if (currentSequenceSum < 0) 
		{
			currentSequenceSum = 0;
		}
		else if (currentSequenceSum > currentMaximumSum) 
		{
			currentMaximumSum = currentSequenceSum;
		}

		if (table[i] > biggestNumber) 
		{
			biggestNumber = table[i];
		}

		if (allNumbersNegative && table[i] > 0) 
		{
			allNumbersNegative = false;
		}
	}
	
	if (allNumbersNegative) 
	{
		return biggestNumber;
	}
	else 
	{
		return currentMaximumSum;
	}
}

/*algorytm wykorzystujacy algorytm Kadane'a, ktory pozwala na policzenie maksymalnej sumy podtablicy jakiejs dwuwymiarowej tablicy
- zamyka on powoli tablice z lewej i z prawej, nastepnie sumuje powstale rzedy (i trzyma je w "temporaryArray"), a potem dla owych sum rzedow stosuje Kadane'a
- najwieksza suma podtablicy znajduje sie w zmiennej currentMaximumSum*/
int maximumSubarray(int **table, int horizontal, int vertical) 
{
	int currentMaximumSum = 0;

	for (int i = 0; i < horizontal; i++) 
	{
		int *temporaryArray = new int[vertical];

		for (int j = 0; j < vertical; j++) 
		{
			temporaryArray[j] = 0;
		}

		for (int j = i; j < horizontal; j++) 
		{
			for (int k = 0; k < vertical; k++) 
			{
				temporaryArray[k] += table[j][k];
			}
				
			int sumOfSubarray = kadaneAlgorithm(temporaryArray, vertical);

			if (currentMaximumSum < sumOfSubarray) 
			{
				currentMaximumSum = sumOfSubarray;
			}
		}
	}
	return currentMaximumSum;
}

/*funkcja sprawdza czy podana wartosc w ogole jest liczba i jezeli tak, to czy miesci sie w okreslonych granicach
- uznalem, ze najbardziej intuicyjne bedzie jesli program bedzie ignorowal wszystko co zostalo wpisane po "blednej" danej, wiec np. w przypadku takiego
zestawu danych: 1 2 3 a 5 6 7, zignorowane zostanie a 5 6 7 i trzeba bedzie od tego miejsca podac dane ponownie (np. 4 5 6 7)*/
void checkValue(int &value, int limit, greaterOrLessThanSign sign) 
{
	if (cin.fail())
	{
		cout << "!(number)" << endl;		
		cin.clear();
		cin.ignore(numeric_limits<int>::max(), '\n');		
		
		cin >> value;
		checkValue(value, limit, sign);
	}
	else if (sign == GREATER) 
	{ 
		if (value < limit)
		{
			cout << "!(>" << limit << ")" << endl;
			cin.clear();
			cin.ignore(numeric_limits<int>::max(), '\n');
			
			cin >> value;
			checkValue(value, limit, GREATER);
		}
	}
	else
	{
		if (value >= limit)
		{
			cout << "!(<" << limit << ")" << endl;
			cin.clear();
			cin.ignore(numeric_limits<int>::max(), '\n');
			
			cin >> value;			
			checkValue(value, limit, LESS);
		}
	}
}

//wpisywanie wartosci do tablicy
void typeInTableValues(int **table, int horizontal, int vertical) 
{
	for (int i = 0; i < horizontal; i++)
	{
		for (int j = 0; j < vertical; j++) 
		{
			cin >> table[i][j];				
			checkValue(table[i][j], 32768, LESS);
			checkValue(table[i][j], -32768, GREATER);
		}
	}
}

//tworzenie tablicy 2D
int **create2DTable(int horizontal, int vertical) 
{
	try 
	{
		int **table = new int*[horizontal];

		for (int i = 0; i < horizontal; i++) 
		{
			table[i] = new int[vertical];
		}

		return table;
	}
	catch (bad_alloc) 
	{
		cout << "Table cannot be created" << endl;
		_getch();
		exit(0);
	}
}

int main() 
{
	int numberOfSets = 0;

	cin >> numberOfSets;
	checkValue(numberOfSets, 0, GREATER);

	int *subarraysSums = new int[numberOfSets];

	for (int i = 0; i < numberOfSets; i++)
	{
		int horizontal = 0, vertical = 0;
		
		cin >> horizontal;
		checkValue(horizontal, 0, GREATER);
		checkValue(horizontal, 100, LESS);

		cin >> vertical;
		checkValue(vertical, 0, GREATER);
		checkValue(vertical, 100, LESS);

		int **table = create2DTable(horizontal, vertical);
		typeInTableValues(table, horizontal, vertical);

		subarraysSums[i] = maximumSubarray(table, horizontal, vertical);
	}

	for (int i = 0; i < numberOfSets; i++) 
	{
		cout << subarraysSums[i] << endl;
	}

	_getch();

	return 0;
}