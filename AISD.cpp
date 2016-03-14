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
void QSzobliczeniem(int *x, int n);

int _tmain(int argc, _TCHAR* argv[])
{

	srand(time(NULL));//wlaczenie zegara dla randomowania zmiennych
	int n, *ciag; //deklaracja dlugosci ciagu, i wskaznika na ciag
	cout << "Podaj liczbe elementow ciagu: ";
	cin >> n; //podanie wielkosci ciagu
	ciag = new int[n]; //stworzenie nowej tablicy dynamicznej o wielkosci podanej przez uzytkownika
	//wypelnijtablicerosnaco(ciag, n);
	//wypelnijtablicemalejaco(ciag, n);
	//wypelnijtablicelosowo(ciag, n);
	//wypelnijtablicestala(ciag, n);
	//wypelnijtabliceaksztalt(ciag, n);
	//ss(ciag, n);
	//is(ciag, n);
	//ShellS(ciag, n);
	//HeapSort(ciag, n);
	//QSzobliczeniem(ciag, n);

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
		x[i - 1] = i;
		//cout << x[i] << endl;
	}

}

void wypelnijtablicemalejaco(int *x, int n)
{
	int pom = n;
	for (int i = 1; i <= n; i++)
	{

		x[i - 1] = pom;
		//cout << x[i] << endl;
		pom--;
	}

}

void wypelnijtablicelosowo(int *x, int n)
{
	for (int i = 1; i <= n; i++)
	{
		x[i - 1] = rand() % n;
		//cout << x[i-1] << endl;
	}
	//cout << "--------" << endl;
}

void wypelnijtabliceaksztalt(int *x, int n)
{
	int pom;
	pom = 0;
	for (int i = 1; i <= n / 2; i++)
	{
		while (pom % 2 != 0)
			pom++;
		pom++;
		x[i - 1] = pom;
	}

	for (int i = n / 2; i <= n; i++)
	{
		while (pom % 2 == 0)
			pom--;
		pom--;
		x[i - 1] = pom;
	}
}

void wypelnijtablicestala(int *x, int n)
{
	int liczba;
	cout << "Jaka liczba ma byc wypelniona tablica?" << endl;
	cin >> liczba;
	for (int i = 1; i <= n; i++)
	{
		x[i - 1] = liczba;

	}
}

void ss(int *x, int n)
{
	int min; //wartosć minimalna 
	double roznica; //liczenie czasu algorytmu bardziej opisane w QSzobliczeniem
	cout.setf(ios::fixed);
	cout.precision(5);
	clock_t start, koniec;
	start = clock();
	for (int i = 0; i < n - 1; i++) //od poczatku tablicy do n-1 elementu 
	{

		min = i; //ustawiamy naszego mina na pierwszy element tablicy
		for (int j = i + 1; j < n; j++) //j to zmienna do poruszania się po tablicy, będzie wskazywała na element kolejny
		{
			if (x[j] < x[min]) // jesli element kolejny jest mniejszy od aktualnego to nasz kolejny staje się minimum
			{
				min = j;
			}

		}
		if (min != i) //jesli minimum jest inne niż nasz aktualny to zamieniamy miejscami elementy
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
	int tmp, el; // zmienne pomocnicze jedna bedzie wszkazywala element, a druga chwilowo przechowywala wartosc elementu
	double roznica;
	cout.setf(ios::fixed);
	cout.precision(5);
	clock_t start, koniec;
	start = clock();
	for (int i = 1; i < n; i++) // od drugiego elementu tablic do ostatniego
	{
		tmp = x[i]; //w tmp przechowujemy wartosc pierwszego elementu
		for (el = i - 1; el >= 0 && x[el] > tmp; el--)//zmienna el przechowuje poprzedni element tablicy, jeśli element jest wiekszy o 0 i jesli jest wiekszy od tmp to wykonujemy krok czyli zmniejszamy go o 1
			x[el + 1] = x[el]; //zamieniamy miejscami elementy

		x[el + 1] = tmp; //ponowna zmiana elementów
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

	for (int i = (n - 1) / 2; i >= 0; i--) //tworzymy kopiec z schodząc kolejno do pierwszego elementu
		HeapIfy(x, n, i); //przywracamy własność kopca

}

void HeapIfy(int *x, int n, int el)
{
	int l = 2 * el; //lewy element
	int r = 2 * el + 1; //pawy element
	int i; //najwiekszy z tej dwojki
	while (l <= n) //dopoki lewy jest mniejszy lub równy wielkosci kopca
	{
		if (r <= n) //jesli prawy jest mniejszy lub rowny wielkosci kopca
		{
			if (x[r] < x[l]) //jesli prawy mniejszy od lewego
				i = l; //najwiekszy jest lewy
			else
				i = r; //w innym wypadku najwiekszy jest prawy
		}
		else
			i = l; //jesli prawy jest wiekszy od wielkosci kopca czyli wykracza poza niego to najwiekszy automatycznie jest lewy
		if (x[i] > x[el]) //jesli najwiekszy jest wiekszy od rodzica
		{
			swap(x[i], x[el]); //zamieniamy rodzica z najwiekszym
			el = i; //rodzicem staje sie najwiekszy
			l = 2 * el; //ustawiamy nowe dzieci nowego rodzica
			r = 2 * el + 1;
		}
		else
			break;

	}

}

void HeapSort(int *x, int n)
{
	double roznica;            //tu ogólnie liczy się czas algorytmu, opisane szczegółowo w QSzolbiczeniem
	cout.setf(ios::fixed);
	cout.precision(5);
	clock_t start, koniec;
	start = clock();
	BuildHeap(x, n); //budujemy heap
	for (int i = n - 1; i > 0; i--) //schodzimy do naszego korzenia i zamieniamy elementy, po czym odcinamy element posortowany
	{
		swap(x[i], x[0]);
		n--;
		HeapIfy(x, i - 1, 0); //przywracamy własnosć kopca
	}
	koniec = clock();
	roznica = (koniec - start) / (double)CLOCKS_PER_SEC;
	cout << "Czas wykonania algorytmu HeapSort: " << roznica << endl;
}

void QS(int *x, int l, int r)
{
	int i = l; //nasza lewa wartość
	int j = r; // nasza prawa wartość
	int tmp = x[r]; //bierzemy naszego x z połowy naszej tablicy
	//int tmp = x[rand() % n];
	do
	{
		while (x[i] < tmp) //dopóki element lewy tablicy jest mniejszy od naszego "x" czyli tmp to przechodzimy na kolejny element - idziemy w prawo
			i++;
		while (x[j] > tmp) //dopóki element prawy tablicy jest wiekszy od naszego "x" czyli tmp to przechodzimy na kolejny element - idziemy w lewo
			j--;
		if (i <= j) //jesli nasza lewy jest mniejszy od prawego to zmieniamy i przechodzimy na kolejene elementy
		{
			swap(x[i], x[j]);
			i++;
			j--;
		}

	} while (i <= j); //pętla wykonuje się tak długo dopóki nie zajdzie zmiana
	if (l < j) QS(x, l, j); //rekurencja
	if (r > i) QS(x, i, r); //rekurencja

}

void QSzobliczeniem(int *x, int n)
{
	double roznica; //nasz czas koncowy
	cout.setf(ios::fixed); //ustawienie porpawnego wyswietlania czasu
	cout.precision(5); //z dokładnościa do 5 zer
	clock_t start, koniec; //ustawiamy zmienne czasowe
	start = clock(); //zbieramy czas startowy
	QS(x, 0, n - 1); //odpalamy quicksorta
	koniec = clock(); //zabieramy czas po ukończeniu algorymtu
	roznica = (koniec - start) / (double)CLOCKS_PER_SEC; //odejmujemy od siebie dwa czasy i dzielimy przez sekundy
	cout << "Czas wykonania algorytmu QS: " << roznica << endl; // wyswietlamy wynik

}
