// AISD3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include <queue>

using namespace std;


int liczbakrawedzi = 0;
int **macierzsasiedztwa(int wielkosc)
{
	//Tworzenie tablicy dynamicznej dwuwymiarowej
	int **msas = new int *[wielkosc]; 

	for (int i = 0; i < wielkosc; i++)
		msas[i] = new int[wielkosc];
	

	//Tworzenie macierzy sasiedztwa dla grafu spojnego acyklicznego
	for (int pom = 0; pom < wielkosc; pom++)
	{
		for (int pom2 = 0; pom2 < wielkosc; pom2++)
		{
			if (pom == pom2)
				msas[pom][pom2] = 0;
			else if (pom < pom2)
			{
				msas[pom][pom2] = 1;
				liczbakrawedzi++;
			}
			else if (pom > pom2)
				msas[pom][pom2] = 0;
		}
	}
	//Zamieniamy krawędź tak by z tej macierzy powstał graf spójny wciąż acykliczny i o nasyceniu 50%
	if (msas[wielkosc - 2][wielkosc - 1] == 1)
		swap(msas[0][wielkosc - 1], msas[wielkosc - 1][0]);

	//Sprawdzamy czy nasz graf faktycznie będzie miał nasycenie 50%
	if (liczbakrawedzi > (wielkosc*(wielkosc - 1)) * 1 / 2 && liczbakrawedzi < (wielkosc*(wielkosc - 1)) * 1 / 2)
		cout << "Warning: Ilosc krawedzi jest zlla!!";
	
	//Wyswietlanie macierzy sasiedztwa
	for (int i = 0; i < wielkosc; i++)
	{
		for (int j = 0; j < wielkosc; j++)
		{
			cout << msas[i][j];
		}

		cout << endl;
	}
	
	cout << endl;

	return msas;
}

void listimincydencji(int **x, int n)
{
	list <int> *krawedzie = new list <int>[n + 1]; //utworzenie listy ktora bedzie przechowywała wierzchołki
	for (int pom = 0; pom < n; pom++)
	{
		for (int pom2 = 0; pom2 < n; pom2++)
		{
			if (x[pom][pom2] == 1)
				krawedzie[pom].push_back(pom2 + 1); //wstawianie na listę następników danego wierzchołka
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
	//Tworzenie tablicy dynamicznej dwuwymiarowej
	int **mincy = new int *[n];

	for (int i = 0; i < n; i++)
		mincy[i] = new int[liczbakrawedzi];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < liczbakrawedzi; j++)
			mincy[i][j] = 0;
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

}

void BFS(int **x, int v1, int n)
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

		cout << v1+1 << " : ";   

		

		for (int i = 0; i < n; i++)
		if (x[v1][i] == 1 && odwiedzony[i] == 'B')  
		{
			odwiedzony[i] = 'S'; 
			czasodwiedzin[i] = czasodwiedzin[v1] + 1;
			poprzednik[i] = poprzednik[v1];
			kolejka.push(i);               
		}
		odwiedzony[v1] = 'C';
	}

	cout << endl << endl;

	// Usuwamy tablice dynamiczne

	delete[] odwiedzony;

	for (int i = 0; i < n; i++) delete[] x[i];

	delete[] x;
}

void DFSvist(int v1, int n)
{
	char *odwiedzony = new char[n];
	int *czasodwiedzin = new int[n];
	int *poprzednik = new int[n];
	int czas = 0;
	odwiedzony[v1] = 'S';
	czas = czas + 1;
	czasodwiedzin[v1] = czas;
	for (int i = 0; i < n; i++)
	{
		if (odwiedzony[i] == 'B')
		{
			poprzednik[i] = v1;
			DFSvist(i, n);
		}
	}
	odwiedzony[v1] = 'B';

}

int _tmain(int argc, _TCHAR* argv[])
{
		
	int n, v;
	n = 4;
	v = 4;
	listimincydencji(macierzsasiedztwa(n), n);
	BFS(macierzsasiedztwa(n), v-1, n);
	system("PAUSE");
	return 0;
}

