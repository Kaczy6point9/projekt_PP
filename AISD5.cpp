// AISD5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <algorithm>
#include <list>


using namespace std;


class Przedmioty
{
public:
	int wartosc;
	int objetosc;
	void przypiszwartosc(int wartosc, int objetosc)
	{
		this->wartosc = wartosc;
		this->objetosc = objetosc;
	}
};

int plecakdynamic(Przedmioty *przedmiot, int ilosc_przedmiotow, int objetosc_plecaka)
{
	if (ilosc_przedmiotow < 0)  // jeżeli ilość przedmiotów wynosi zero to zwracamy zero
	{
		return 0; 
	}
	if (przedmiot[ilosc_przedmiotow].objetosc > objetosc_plecaka) // jeżeli przedmiot nie mieści się w plecaku
	{
		return plecakdynamic(przedmiot, ilosc_przedmiotow - 1, objetosc_plecaka); //to rekurencycjnie sprawdzamy kolejny przedmiot
	}
	else  //jeśli mieści się to zwracamy najbardziej optymalna wartość z porównań dwóch kolejnych tablic wynikowych w tym wypadku naszych rekurencji
	{
		return max(plecakdynamic(przedmiot, ilosc_przedmiotow - 1, objetosc_plecaka), plecakdynamic(przedmiot, ilosc_przedmiotow - 1, objetosc_plecaka - przedmiot[ilosc_przedmiotow].objetosc) + przedmiot[ilosc_przedmiotow].wartosc);
		//jeżeli nie to wybieramy maxa z wartości zwracanej przez kolejny przedmiot lub wybieramy wartość zwracaną przez drugą rekurencję do której dodajemy wartość przedmiotu
		//pierwsza rekurencja sprawdza nam kolejny przedmiot, a druga sprawdza nam wartość aktualnego przedmiotu z przedmiotem kolejnym
		//max służy do wybrania najlepszej opcjonalnej opcji z rekurencji złożoność tej funkcji to O(nW) czyli jest to funkcja pseudo wielomianowa
		//dzięki rekurencji zapamiętujemy wartości 
	}
}

int maxWartosc = 0; //zmienna przechowująca wartośc maksymalną plecaka

void plecakBF(Przedmioty *przedmiot, int poczatek, int index, int objetosc_plecka, int ilosc_przedmiotow, int aktualna_wartosc, int aktualna_waga) 
{
	if (aktualna_waga <= objetosc_plecka && aktualna_wartosc > maxWartosc) //jeżeli aktualna waga jest mniejsza od objętości plecaka, i aktualna wartość jest mniejsza od aktualnie maksymalnej wartości otrzymanej
		maxWartosc = aktualna_wartosc; //to maksymalna wartość naszego plecaka przyjmuje aktualną wartość

	for (int i = 0; i < ilosc_przedmiotow; i++) //przechodzimy przez wszystkie przedmioty
	if (i>index && i != poczatek)  plecakBF(przedmiot, poczatek, i, objetosc_plecka, ilosc_przedmiotow, aktualna_wartosc+przedmiot[i].wartosc, aktualna_waga+przedmiot[i].objetosc);
	//jezeli i jest przedmiotem kolejnym od przedmiotu pod indexem I i przyjmuje wartość różną od początku to sprawdzamy, przedmiot od poczatku, pod indexem i, aktualna_wartośc =aktualna_wartość+wartosc kolejnego przedmiotu, aktualna_waga=aktualna_waga+waga nastepnego przedmiotu

}

void przeglad(Przedmioty *przedmiot, int objetosc_plecaka ,int ilosc_przedmiotow) //robimy przegląd wszystkich przedmiotow i ich możliwych kombinacji
{
	for (int i = 0; i < ilosc_przedmiotow; i++)
	{
		plecakBF(przedmiot, 0, i, objetosc_plecaka, ilosc_przedmiotow, przedmiot[i].wartosc, przedmiot[i].objetosc);
	}

	cout << endl << maxWartosc << endl;
}
	


int _tmain(int argc, _TCHAR* argv[])
{
	int n = 0; //ilosc przedmiotow
	n = 5; 
	int objetosc_plecaka;
	objetosc_plecaka = 50;
	srand(time(NULL));
	Przedmioty *przedmiot = new Przedmioty[n];
	for (int i = 0; i < n; i++)
	{
		int wartosc = rand() % 50 + 1; //losuje wartosci przedmiotow
		int objetosc = rand() % objetosc_plecaka + 1; //losuje objetosci przedmiotow
		przedmiot[i].przypiszwartosc(wartosc, objetosc); //przypisuje wylosowane wartosci do przedmiotow
	}
	for (int i = 0; i < n; i++) //wyswietla przedmioty
	{
		cout << przedmiot[i].objetosc << "  " << przedmiot[i].wartosc << endl;
	}

	cout << plecakdynamic(przedmiot, n, objetosc_plecaka) << endl; //rozwiazanie dynamiczne

	przeglad(przedmiot, objetosc_plecaka, n); //brute force O(n2^n)

	system("PAUSE");
	return 0;
}

