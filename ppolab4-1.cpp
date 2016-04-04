// molecue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <time.h>
#include <list>

using namespace std;

template<typename T, int size>
class tablica
{
 
	
	T ciag[size];
	
	
public:
	void sort()
	{
		
		T tmp;
		T el;
		for (int i = 1; i < size; i++) // od drugiego elementu tablic do ostatniego
		{
			tmp = ciag[i]; //w tmp przechowujemy wartosc pierwszego elementu
			for (el = i - 1; el >= 0 && ciag[el] > tmp; el--)//zmienna el przechowuje poprzedni element tablicy, jeśli element jest wiekszy o 0 i jesli jest wiekszy od tmp to wykonujemy krok czyli zmniejszamy go o 1
				ciag[el + 1] = ciag[el]; //zamieniamy miejscami elementy

			ciag[el + 1] = tmp; //ponowna zmiana elementów
		}
		
	}

	T & operator[](int index) { return ciag[index]; }

};

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	
	tablica<int, 10> tab;
	for (int i = 0; i < 10; i++)
	{
		tab[i] = rand() % 20;
		
		
	}
	tab.sort();
	for (int i = 0; i < 10; i++)
	{
		cout << tab[i] << endl;
	}
	
	system("PAUSE");
	return 0;
}

