// AISD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>

using namespace std;

void wypelnijtablicerosnaco(int *x, int n);
void wypelnijtablicemalejaco(int *x, int n);
void wypelnijtablicelosowo(int *x, int n);
void wypelnijtablicestala(int *x, int n);
void wypelnijtabliceaksztalt(int *x, int n);
void ss(int *x, int n);
void is(int *x, int n);
void ShellS(int *x, int n);
void HeapSort(int *x, int n);
void HeapIfy(int *x, int n, int el);
void BuildHeap(int *x, int n);
void QS(int *x, int l, int r);

int _tmain(int argc, _TCHAR* argv[])
{
	
	srand(time(NULL));//wlaczenie zegara dla randomowania zmiennych
	int n, *ciag; //deklaracja dlugosci ciagu, i wskaznika na ciag
	cout << "Podaj liczbe elementow ciagu: ";
	cin >> n; //podanie wielkosci ciagu
	ciag = new int[n]; //stworzenie nowej tablicy dynamicznej o wielkosci podanej przez uzytkownika
	//wypelnijtablicerosnaco(ciag, n);
	//wypelnijtablicemalejaco(ciag, n);
	wypelnijtablicelosowo(ciag, n);
	//wypelnijtablicestala(ciag, n);
	//wypelnijtabliceaksztalt(ciag, n);
	//ss(ciag, n);
	//is(ciag, n);
	//ShellS(ciag, n);
	//HeapSort(ciag, n);
	QS(ciag, 0, n-1);

	/*for(int i = 0; i < n; i++) //wyswietla elementy posortowanego ciagu
	{
		cout << ciag[i] << endl;
	}
	*/
	system("PAUSE");
	delete[] ciag;
	return 0;
}

void wypelnijtablicerosnaco(int *x, int n)
{
	
	for (int i = 1; i <= n; i++)
	{
		x[i-1] = i;
		//cout << x[i] << endl;
	}

}

void wypelnijtablicemalejaco(int *x, int n)
{
	int pom=n;
	for (int i = 1; i <= n; i++)
	{
		
		x[i-1] = pom;
		//cout << x[i] << endl;
		pom--;
	}

}

void wypelnijtablicelosowo(int *x, int n)
{
	for (int i = 1; i <= n; i++)
	{
		x[i-1] = rand() % n;
		//cout << x[i-1] << endl;
	}
	//cout << "--------" << endl;
}

void wypelnijtabliceaksztalt(int *x, int n)
{
	int pom;
	pom = 0;
	for (int i = 1; i <= n/2; i++)
	{
		while(pom % 2 != 0)
			pom++;
		pom++;
		x[i-1] = pom;
	}

	for (int i = n / 2; i <= n; i++)
	{
		while (pom % 2 == 0)
			pom--;
		pom--;
		x[i-1] = pom;
	}
}

void wypelnijtablicestala(int *x, int n)
{
	int liczba;
	cout << "Jaka liczba ma byc wypelniona tablica?" << endl;
	cin >> liczba;
	for (int i = 1; i <= n; i++)
	{
		x[i-1] = liczba;
		
	}
}

void ss(int *x, int n)
{
	int min;
	double roznica;
	cout.setf(ios::fixed);
	cout.precision(5);
	clock_t start, koniec;
	start = clock();
	for (int i = 0; i < n-1; i++)
	{
	
		min = i;
		for (int j = i + 1; j < n; j++)
		{
			if (x[j] < x[min])
			{
				min = j;
			}
			
		}
		if (min != i)
		{
			swap(x[min], x[i]);
		}
		
	}
	koniec = clock();
	roznica = (koniec - start) / (double)CLOCKS_PER_SEC;
	cout << "Czas wykonania algorytmu SS: " << roznica << endl;

}

void is(int *x, int n)
{
	int tmp, el;
	double roznica;
	cout.setf(ios::fixed);
	cout.precision(5);
	clock_t start, koniec;
	start = clock();
	for (int i = 1; i < n; i++)
	{
		tmp = x[i];
		for (el = i - 1; el >= 0 && x[el] > tmp; el--)
			x[el + 1] = x[el];
		
		x[el + 1] = tmp;
	}
	koniec = clock();
	roznica = (koniec - start) / (double)CLOCKS_PER_SEC;
	cout << "Czas wykonania algorytmu IS: " << roznica << endl;
}

void ShellS(int *x, int n)
{
	int h; //odstep pomiedzy kolejnymi elementami
	int j; //zmienna sterujaca petli
	int i; //indeks elementu tablicy uporzadkowanej
	int el; //wybrany element tablicy
	
	double roznica;
	cout.setf(ios::fixed);
	cout.precision(5);
	clock_t start, koniec;
	start = clock();
	for (h = 1; h < n; h = 3 * h + 1); //ustalamy poczatkową wartość odstepu według Knutha
	h /= 9;
	if (!h) //jeśli odstęp jest zero 
		h++; //to zwiekszamy go o jeden
	while (h) //dopóki mamy odstęp
	{
		for (j = n - h - 1; j >= 0; j--)//dzielimy naszą tablice na odstepy, które zmniejszamy co krok
		{
			el = x[j]; //wybieramy element tablicy wskazany przez odstep
			i = j + h; //ustawiawmy indeks na kolejny element danego odstepu
			while ((i<n) && (el > x[i])) //wkonujemy dopóki indeks jest mniejszy od wielkosci tablciy i element jest wiekszy od elementu wskazanego przez i 
			{
				x[i - h] = x[i]; //wymieniamy elementy
				i += h; //zwiekszamy indeks o odstep
			}
			x[i - h] = el; //wymieniamy elementy
		}
		h /= 3; //zmniejszamy odstep
	}
	koniec = clock();
	roznica = (koniec - start) / (double)CLOCKS_PER_SEC;
	cout << "Czas wykonania algorytmu ShellS: " << roznica << endl;
}

void BuildHeap(int *x, int n)
{
	
	for (int i = (n - 1) / 2; i >= 0; i--)
		HeapIfy(x, n, i);

}

void HeapIfy(int *x, int n, int el)
{
	int l = 2 * el;
	int r = 2 * el + 1;
	int i;
	while (l <= n)
	{
		if (r <= n)
		{
			if (x[r] < x[l])
				i = l;
			else
				i = r;
		}
		else
			i = l;
		if (x[i] > x[el])
		{
			swap(x[i], x[el]);
			el = i;
			l = 2 * el;
			r = 2 * el + 1;
		}
		else
			break;

	}
	
}

void HeapSort(int *x, int n)
{
	double roznica;
	cout.setf(ios::fixed);
	cout.precision(5);
	clock_t start, koniec;
	start = clock();
	BuildHeap(x, n);
	for (int i = n-1; i > 0; i--)
	{
		swap(x[i], x[0]);
		n--;
		HeapIfy(x, i-1, 0);
	}
	koniec = clock();
	roznica = (koniec - start) / (double)CLOCKS_PER_SEC;
	cout << "Czas wykonania algorytmu HeapSort: " << roznica << endl;
}

void QS(int *x, int l, int r)
{
	int i = l;
	int j = r;
	int tmp = x[(l + r) / 2];
	double roznica;
	cout.setf(ios::fixed);
	cout.precision(5);
	clock_t start, koniec;
	start = clock();
	do
	{
		while (x[i] < tmp)
			i++;
		while (x[j] > tmp)
			j--;
		if (i <= j)
		{
			swap(x[i], x[j]);
			i++;
			j--;
		}

	} while (i <= j);
	if (l < j) QS(x, l, j);
	if (r > i) QS(x, i, r);
	koniec = clock();
	roznica = (koniec - start) / (double)CLOCKS_PER_SEC;
	cout << "Czas wykonania algorytmu HeapSort: " << roznica << endl;
}
