// AISD3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <list>
#include <queue>

using namespace std;
int n; // ilość wierzchołków


double liczbakrawedzi = 0;
int **macierzsasiedztwa(int wielkosc)
{
	//Tworzenie tablicy dynamicznej dwuwymiarowej - dla macierzy sasiedztwa
	int **msas = new int *[wielkosc];  //msas = macierz sasiedztwa

	for (int i = 0; i < wielkosc; i++)
		msas[i] = new int[wielkosc];
	

	//Tworzenie macierzy sasiedztwa dla grafu spojnego acyklicznego
	liczbakrawedzi = (wielkosc*(wielkosc - 1)) * 0.5 * 0.5;
	liczbakrawedzi = ceil(liczbakrawedzi);
	cout << liczbakrawedzi	<< endl;
	for (int pom = 0; pom < wielkosc; pom++) //pom = zmienna pomocnicza, w tym przypadku będzie oznaczała indeks kolumny
	{
		for (int pom2 = 0; pom2 < wielkosc; pom2++) //pom2 = zmienna pomocnicza, w tym przypadku będzie oznaczała indeks wierszu
		{
				msas[pom][pom2] = 0;
		}
	}
	int pom2 = 0; //zmiena która będzie służyła do poruszania się po indeksie kolumn macierzy
	int pom3 = 0; //zmiena która będzie służyła do poruszania się po indeksie wierszy macierzy
	int krawedzie = 0;//ilość krawedzi w macierzy sasiedztwa
	for (int pom = 0; pom < liczbakrawedzi; pom++) //iteracja dodająca krawedzie do grafu
	{
		
		if (krawedzie < liczbakrawedzi) //jesli ilosc w krawedzi w macierzy jest mniejsza od ilosci krawedzi ktore powinny byc w krawedzi
		{

			while (pom2 > pom3 || pom2 == pom3) //wypełniamy górny trójkąt macierzy jedynkami
			{
				pom3++; //zwiekszamy indeks drugiego wymiaru
				if (pom3 > wielkosc - 1) //jezeli indeks wyjdzie poza rozmiar tablicy
				{
					pom3 = 0; //ustawiamy go z powrotem na pierwszy element
					break;//wychodzimy z whilea
				}
			}
			if (msas[pom2][pom3] == 0) //sprawdzamy czy nie ma już krawedzi w tej czesci macierzy
			{
				msas[pom2][pom3] = 1; //jesli nie ma, ustawiamy krawedz
				krawedzie++; //ilosc krawedzi zwieksza sie
			}
			else if (pom3 < wielkosc) //jezeli jest krawedz i nie wyszliśmy poza zakres
			{
				do
				{
					pom3++; //idziemy jeden element dalej dopóki nie spotkamy takiego miejsca w macierzy w którym nie ma krawedzi
				} while (msas[pom2][pom3] == 1); 

				msas[pom2][pom3] = 1; //ustawiamy krawedz
				krawedzie++; //ilośc krawedzi zwieksza się
			}

			pom3 = 0; //wracamy do początku macierzy
			pom2++; //zwiekszamy indek wierzchołka
			if (pom2 > wielkosc - 1 && krawedzie < liczbakrawedzi-1) //jeżeli wyjdziemy po za liczbę wierzchołków w macierzy
			{
				pom2--; //zmniejszamy z powrotem do zakresu
				if (msas[pom2][pom3] == 1) //jeśli istnieje krawędź w tym miejscu zwiększamy indeks i wtam wstawiamy jedynkę operacja ta sprawia, że graf staje się spójny
				{
					pom3++;
					msas[pom2][pom3] = 1;
					krawedzie++;
				}
				else
				{
					msas[pom2][pom3] = 1;
					krawedzie++;
				}
				pom2 = 0; //po wstawieniu krawedzi w tym miejscu zerujemy macierz i przechodzimy ją od nowa
				pom3 = 0;
			}
		}
		
	}

	//Zamieniamy krawędź tak by z tej macierzy powstał graf spójny wciąż acykliczny i o nasyceniu 50%
	/*if (msas[wielkosc - 2][wielkosc - 1] == 1)
		swap(msas[0][wielkosc - 1], msas[wielkosc - 1][0]);*/


	//Wyswietlanie macierzy sasiedztwa
	for (int i = 0; i < wielkosc; i++)
	{
		cout << i << " ";
		for (int j = 0; j < wielkosc; j++)
		{
			cout << msas[i][j];
		}

		cout << endl;
	}
	
	cout << endl;

	return msas;
}


list <int> *listasasiedztwa(int **macierzsasiedztwa, int n)
{
	
	list <int> *krawedzie = new list <int>[n + 1]; //utworzenie listy ktora bedzie przechowywała wierzchołki
	for (int pom = 0; pom < n; pom++)
	{
		for (int pom2 = 0; pom2 < n; pom2++)
		{
			if (macierzsasiedztwa[pom][pom2] == 1)
				krawedzie[pom].push_back(pom2+1); //wstawianie na listę następników danego wierzchołka
		}
	}

	list<int>::iterator it; //iterator listy
	for (int i = 0; i < n; i++)
	{
		cout << i + 1 << ": ";
		for (it = krawedzie[i].begin(); it != krawedzie[i].end(); ++it)
		{
			cout << *it << " "; //wypisanie listy nastepnikow
		}

		cout << endl;
	}

	cout << endl;

	return krawedzie;
} 

// Macierz Incydencji niedziałająca - nie potrafię przekonwertować macierzy sąsiedztwa na macierz incydencji
/*int **macierzincydencji(int **macierzsasiedztwa, int n)
{
	int ilosckrawedzii;
	
	ilosckrawedzii = liczbakrawedzi;
	//Tworzenie tablicy dynamicznej dwuwymiarowej
	int **mincy = new int *[n]; //mincy = macierzincydencji

	for (int i = 0; i < n; i++)
		mincy[i] = new int[ilosckrawedzii];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < liczbakrawedzi; j++)
			mincy[i][j] = 0;
	}
	
	int pom2=0, pom3=0;

	for (int pom = 0; pom < ilosckrawedzii; pom++) //pom = pomocnicza która będzie przechodziła przez macierz incydencji
	{
	
		while (macierzsasiedztwa[pom2][pom3] !=1)
			pom3++;
		if (pom > n-1)
		{
			pom3++;
			if (pom3 > n - 1)
			{
				pom2++;
				if (pom2 > n - 1)
				{
					pom2--;
				}
				pom3=1;
				mincy[pom2][pom] = -1;
				mincy[pom3][pom] = 1;
				continue;
			}
			
			mincy[pom2][pom] = -1;
			mincy[pom3][pom] = 1;
		}
		else
		{
			
			mincy[pom2][pom] = -1;
			mincy[pom3][pom] = 1;
		}
		       
		
		pom3 = 0;
		pom2++;
		if (pom2 > n - 1)
		{
			pom2--;
			mincy[pom2][pom] = -1;
			mincy[pom3][pom] = 1;
			pom2 = 0;
		}
			
	}
	
	for (int i = 0; i < n; i++)
	{
		cout << i + 1 << ": ";
		for (int j = 0; j < liczbakrawedzi; j++)
		{

			cout << mincy[i][j] << " ";
		}

		cout << endl;
	}

	cout << endl;

	return mincy;
}
*/ 

void BFS(int **macierzsasiedztwa, int v1, int n) //przekazujemy 3 argumenty, macierz sasiedztwa, wierzchołek startowy i wielkosc macierzy
{
	queue <int> kolejka;
	
	char *odwiedzony = new char[n]; //Tablica odwiedzonych wierzchołków przechowuje wartości kolorów
	int *czasodwiedzin = new int[n]; //czas odwiedzin
	int *poprzednik = new int[n]; //poprzednik 
	for (int i = 0; i < n; i++)
	{
		odwiedzony[i] = 'B';
		czasodwiedzin[i] = NULL;
		poprzednik[i] = NULL;
	}

	odwiedzony[v1] = 'S';
	czasodwiedzin[v1] = 0;
	poprzednik[v1] = NULL;

	kolejka.push(v1);
	cout << endl;

	while (!kolejka.empty())        
	{
		v1 = kolejka.front();      

		kolejka.pop();             

		cout << v1+1 << " : ";   

		

		for (int i = 0; i < n; i++)
		if (macierzsasiedztwa[v1][i] == 1 && odwiedzony[i] == 'B')  
		{
			odwiedzony[i] = 'S'; 
			czasodwiedzin[i] = czasodwiedzin[v1] + 1;
			poprzednik[i] = v1;
			kolejka.push(i);               
		}
		odwiedzony[v1] = 'C';
	}

	cout << endl << endl;
	//usuwamy dynamiczne elementy
	delete[] odwiedzony;
	delete[] czasodwiedzin;
	delete[] poprzednik;

} 

void BFSlist(list <int> *lista, int v1, int n) //przekazujemy 3 argumenty, liste sasiedztwa, wierzchołek startowy i wielkosc macierzy
{
	queue <int> kolejka;

	char *odwiedzony = new char[n];
	int *czasodwiedzin = new int[n];
	int *poprzednik = new int[n];
	for (int i = 0; i < n; i++)
	{
		odwiedzony[i] = 'B';
		czasodwiedzin[i] = NULL;
		poprzednik[i] = NULL;
	}

	odwiedzony[v1] = 'S';
	czasodwiedzin[v1] = 0;
	poprzednik[v1] = NULL;

	kolejka.push(v1);
	cout << endl;

	while (!kolejka.empty())
	{
		v1 = kolejka.front();

		kolejka.pop();

		cout << v1 + 1 << " : ";



		for (int i = 0; i < n; i++)
		if (lista[i]._Nextnode != NULL  && odwiedzony[i] == 'B')
		{
			odwiedzony[i] = 'S';
			czasodwiedzin[i] = czasodwiedzin[v1] + 1;
			poprzednik[i] = v1;
			kolejka.push(i);
		}
		odwiedzony[v1] = 'C';
	}

	cout << endl << endl;

	delete[] odwiedzony;
	delete[] czasodwiedzin;
	delete[] poprzednik;

}

void DFSvisit(int **macierzsasiedztwa, int v1, int n, char *odwiedzeni) //przekazujemy cztery argumenty, maceirz sasiedztwa, wierzchołek startowy = v1 oraz ilosc wierzchoków =n, oraz tablicę odwiedzen
{
	
	int *czasodwiedzin = new int[n];
	int *poprzednik = new int[n];
	int *czasprzetworzenia = new int[n];
	int czas = 0;
	
	
	

	odwiedzeni[v1] = 'S';
	cout << v1+1 << " : ";
	czas = czas + 1;
	czasodwiedzin[v1] = czas;
	for (int i = 0; i < n; i++)
	{
		if (macierzsasiedztwa[v1][i] == 1 && odwiedzeni[i] == 'B')
		{
			poprzednik[i] = v1;
			DFSvisit(macierzsasiedztwa, i, n, odwiedzeni);
		}
	}
	odwiedzeni[v1] = 'C';
	czasprzetworzenia[v1] = czas = czas + 1;

	
	delete[] czasodwiedzin;
	delete[] poprzednik;
}

void DFS(int **macierzsasiedztwa, int v1, int n) //przekazujemy 3 argumenty, macierz sasiedztwa, wierzchołek startowy=v1 i ilość wierzchołków =n
{
	char *odwiedzony = new char[n];

	for (int i = 0; i < n; i++)
	{
		odwiedzony[i] = 'B';
	}
	
	DFSvisit(macierzsasiedztwa, v1, n, odwiedzony);
		
	

	cout << endl;
	delete[] odwiedzony;
}

void DFSvisitlista(list <int> *lista, int v1, int n, char *odwiedzeni) //przekazujemy cztery argumenty, liste sasiedztwa, wierzchołek startowy = v1 oraz ilosc wierzchoków =n, oraz tablicę odwiedzen
{

	int *czasodwiedzin = new int[n];
	int *poprzednik = new int[n];
	int *czasprzetworzenia = new int[n];
	int czas = 0;




	odwiedzeni[v1] = 'S';
	cout << v1 + 1 << " : ";
	czas = czas + 1;
	czasodwiedzin[v1] = czas;
	for (int i = 0; i < n; i++)
	{
		if (lista[v1]._Nextnode != NULL && odwiedzeni[i] == 'B')
		{
			poprzednik[i] = v1;
			DFSvisitlista(lista, i, n, odwiedzeni);
		}
	}
	odwiedzeni[v1] = 'C';
	czasprzetworzenia[v1] = czas = czas + 1;


	delete[] czasodwiedzin;
	delete[] poprzednik;
}

void DFSlista(list <int> *lista, int v1, int n) //przekazujemy 3 argumenty, liste sasiedztwa, wierzchołek startowy=v1 i ilość wierzchołków =n
{
	char *odwiedzony = new char[n];

	for (int i = 0; i < n; i++)
	{
		odwiedzony[i] = 'B';
	}

	DFSvisitlista(lista, v1, n, odwiedzony);



	cout << endl;
	delete[] odwiedzony;
}

int _tmain(int argc, _TCHAR* argv[])
{
		
	
	n = 6;
	int ilosckrawedzii = liczbakrawedzi;
	list <int> *lista = new list <int>[n + 1]; //lista następnikow

	//Tworzenie tablicy dynamicznej dwuwymiarowej - dla macierzy sasiedztwa
	int **macierzsas = new int *[n];  //macierzsas = macierz sasiedztwa

	for (int i = 0; i < n; i++)
		macierzsas[i] = new int[n];
	
	//Tworzenie tablicy dynamicznej dwuwymiarowej
	int **macierzincy = new int *[n]; //mincy = macierzincydencji

	for (int i = 0; i < n; i++)
		macierzincy[i] = new int[ilosckrawedzii];
	
	macierzsas = macierzsasiedztwa(n);
	lista = listasasiedztwa(macierzsas, n);
	//macierzincy = macierzincydencji(macierzsas, n);

	BFS(macierzsas, 2, n);
	BFSlist(lista, 3, n);
	DFS(macierzsas, 4, n);
	DFSlista(lista, 1, n);

	delete[] macierzsas;
	delete[] lista;
	delete[] macierzincy;
	system("PAUSE");
	return 0;
}

