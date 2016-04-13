// AIDS2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>

using namespace std;

class BSTkorzen
{

public:
	int wartosc;
	BSTkorzen *lewy;
	BSTkorzen *prawy;


	
	BSTkorzen(int wart) //konstruktor ktory przypisuje wartosc korzeniowi
	{
		this->wartosc = wart; //przypisanie wartosci do korzenia
		this->lewy = NULL;//lewy jest pusty
		this->prawy = NULL; //prawy tez jest ustawiony na pusty

	}

	bool dodaj(int wartosc)
	{
	
		if (wartosc < this->wartosc) {
			if (lewy == NULL) {
				lewy = new BSTkorzen(wartosc);
				return true;
			}
			else
				return lewy->dodaj(wartosc);
		}
		else if (wartosc > this->wartosc) {
			if (prawy == NULL) {
				prawy = new BSTkorzen(wartosc);
				return true;
			}
			else
				return prawy->dodaj(wartosc);
		}
		return false;
	}





};




class drzewoBST
{
public:
	BSTkorzen *korzen;

	drzewoBST()
	{
		korzen = NULL;
	}

	
	
bool dodaj(int wartosc)
	{
		if (korzen == NULL) {
			korzen = new BSTkorzen(wartosc);
			return true;
		}
		else
			return korzen->dodaj(wartosc);
	}

	void InorderTreeWalk(BSTkorzen *start)
	{
		if (start != NULL)
		{
			InorderTreeWalk(start->lewy);
			cout << start->wartosc << endl;
			InorderTreeWalk(start->prawy);
		}
	}

	void PreorderTreeWalk(BSTkorzen *start)
	{
		if (start)
		{
			cout << start->wartosc << endl;
			PreorderTreeWalk(start->lewy);
			PreorderTreeWalk(start->prawy);
		}
	
	}

};



class drzewoAVL
{

public:
	int wartosc;
	drzewoAVL *korzenglowny;
	drzewoAVL *parent;
	drzewoAVL *lewy;
	drzewoAVL *prawy;



	drzewoAVL(int x[], int n)
	{
		korzenglowny = dodaj(x, n);
	}
	
	drzewoAVL(int wart) //konstruktor ktory przypisuje wartosc korzeniowi
	{
		this->wartosc = wart; //przypisanie wartosci do korzenia
		this->lewy = NULL;//lewy jest pusty
		this->prawy = NULL; //prawy tez jest ustawiony na pusty
		this->parent = NULL; //jego rodzic jest pusty
	}

	void ustawLewy(drzewoAVL *lewy) 
	{
		this->lewy = lewy;
	}
	void ustawPrawy(drzewoAVL *prawy) 
	{
        this->prawy = prawy;
	}

	drzewoAVL *dodaj(int x[], int start, int koniec, drzewoAVL *parent)
	{
		
	
		if (start > koniec) return NULL;
		int srodek = start + (koniec - start) / 2;
		drzewoAVL *korzen = new drzewoAVL(x[srodek]);
		korzen->ustawLewy(dodaj(x, start, srodek - 1, korzen));
		korzen->ustawPrawy(dodaj(x, srodek + 1, koniec, korzen));
		korzen->parent = parent;
		return korzen;

			
	}
	drzewoAVL *dodaj(int x[], int n)
	{
		return dodaj(x, 0, n - 1, NULL);
	}

	
	
	void InorderTreeWalk(drzewoAVL *start)
	{
		if (start != NULL)
		{
			InorderTreeWalk(start->lewy);
			cout << start->wartosc << endl;
			InorderTreeWalk(start->prawy);
		}
	}
};



void wypelnijtablicelosowo(int *x, int n)
{
	x[0] = rand() % n;

	for (int i = 1; i < n; i++)
	{

		int j = 0;

		x[i] = rand() % n;
		while (j < i)
		{
			if (x[j] == x[i])
			{
				x[i] = rand() % n;
				j = 0;
			}
			else
				j++;


		}

	}
}

void wypelnijtablicerosnaco(int *x, int n)
{

	for (int i = 0; i < n; i++)
	{
		x[i] = i;
		//cout << x[i] << endl;
	}

}

int _tmain(int argc, _TCHAR* argv[])
{

	srand(time(NULL));
	int n, *ciag; //deklaracja dlugosci ciagu, i wskaznika na ciag
	
	cout << "Podaj liczbe elementow ciagu: ";
	cin >> n; //podanie wielkosci ciagu
	ciag = new int[n]; //stworzenie nowej tablicy dynamicznej o wielkosci podanej przez uzytkownika
	wypelnijtablicerosnaco(ciag, n);
	drzewoBST *drzewkoBST = new drzewoBST;
	drzewoAVL *drzewkoAVL = new drzewoAVL(ciag, n);

	drzewkoAVL->InorderTreeWalk(drzewkoAVL->korzenglowny);

	
			
	
	
	
	
	system("PAUSE");
	return 0;
}

