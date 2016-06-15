// AISD4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stack>
#include <time.h>
#include <list>

using namespace std;


int n; // ilość wierzchołków
bool *visited = new bool[n]; //tablica odwiedzin

int **graf(int wielkosc, double nasycenie)
{
	//Tworzenie tablicy dynamicznej dwuwymiarowej - dla macierzy sasiedztwa
	int **msas = new int *[wielkosc];  //msas = macierz sasiedztwa
	for (int i = 0; i < wielkosc; i++) // tworzenie tablicy dwuwymiarowej
		msas[i] = new int[wielkosc];

		srand(time(NULL));
	//Tworzenie macierzy sasiedztwa dla grafu spojnego acyklicznego
	double liczbakrawedzi = 0; //liczba krawedzi
	liczbakrawedzi = (wielkosc*(wielkosc - 1)) * 0.5 * nasycenie; //ilość krawedzi w grafie liczona ze wzoru n(n-1)/2 * nasycenie grafu
	liczbakrawedzi = floor(liczbakrawedzi); //bierzeym podłogę z wyniku wzoru
	int krawedzie = 0;
	krawedzie = liczbakrawedzi; // liczba krawedzi do wstawienia do grafu
	for (int pom = 0; pom < wielkosc; pom++) //pom = zmienna pomocnicza, w tym przypadku będzie oznaczała indeks kolumny
	{
		for (int pom2 = 0; pom2 < wielkosc; pom2++) //pom2 = zmienna pomocnicza, w tym przypadku będzie oznaczała indeks wierszu
		{
			msas[pom][pom2] = 0;
		}
	}

	int *stopienwierzcholka = new int[n]; //tablica przechowująca wierzchołek i jego stopień nasycenia
	for (int i = 0; i < n-1; i++)//pętla która będzie wypełniała nam graf
	{
		msas[i][i + 1] = 1;      //losowy element z wiersza staje się jedynk
		krawedzie--;                     //zmniejszamy ilość pozostałych krawedzi do wstawienia
		
	}
	msas[n - 1][0] = 1;              //aby graf był hamiltonowski łączymy ostatni element z pierwszym
	krawedzie--; //zmniejszamy ilość pozostałych krawedzi do wstawienia
	

	while(krawedzie>0) //dopóki trzeba wstawić jeszcze krawędź
	{
		int i = rand() % (n - 1);     //losujemy wiersz macierzy
		int j = i + rand() % (n - i - 1) + 1; //losujemy kolumne macierzy
		if (msas[i][j] == 0)     //jeżeli wylosowane pole jest puste
		{
			msas[i][j] = 1; // wstawiamy jedynkę 
			krawedzie--; //zmniejszamy ilość pozostałych krawędzi
		}
	}
	for (int i = 0; i<n; i++) //uzupełniamy graf by był nieskierowany
	{
		for (int j = 0; j<n; j++)
		{
			if (msas[i][j] == 1) //tam gdzie mamy krawędz
				msas[j][i] = 1; //to krawędź łączy się także w drugą strone
		}
	}
	
	
	
	
		for (int k = 0; k < n; k++) //pętla specjalnie po to by po losowaniu wierzchołki były parzyste, bez tej pętli raz działały raz nie - nierozumiem
		{

			for (int i = 0; i < n; i++) //przesuwamy się po wierszach
			{
				int parzystosc = 0;//zmienna do sprawdzania czy stopień jest parzysty

				for (int j = 0; j < n; j++)        //poruszamy się po kolumnach    
				{
					if (msas[i][j] == 1)//sprawdzamy jaki jest stopień krawędzi
						parzystosc++;
				}
				if (parzystosc % 2 == 1)             //jeżeli wierzchołek jest nieparzysty
				{
					int j = rand() % n; // losujemy wierzchołek
					while (i == j || j == i + 1 || j == i - 1 || (i == 0 && j == n - 1) || (i == n - 1 && j == 0)) //dopóki J będzie spełniało te warunki szukamy kolejnego
						j = rand() % n;
					//szukamy j tak długo aż spełnia wszystkie warunki miejsca

					if (msas[i][j] == 1 )        //jeżeli miejsce jest zajęte to je zerujemy
					{
						msas[i][j] = 0; 
						msas[j][i] = 0;
					}
					else                                        //a jeżeli jest puste to zapełniamy
					{
						msas[i][j] = 1;
						msas[j][i] = 1;
					}
				}
			}
		}

	
	
	
	
	
	for (int i = 0; i < n; i++) //zerujemy stopnie wierzchołków do wszystkich wierzchołków
	{

		stopienwierzcholka[i] = 0; 

	}
	for (int i = 0; i < n; i++) //sprawdzamy wierzchołki i badamy ich stopnie
	{
		for (int j = 0; j < n; j++)
		{
			if (msas[i][j] == 1)
			{
				stopienwierzcholka[i] += 1;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		visited[i] = false; //dla wszystkich wierzchołków ustawiamy że nie zostały odwiedzone potrzebne w późniejszym etapie do cyklu Hamiltona
	}
	
	//Wyswietlanie macierzy sasiedztwa
	for (int i = 0; i < wielkosc; i++)
	{
		cout << stopienwierzcholka[i] << "    ";
		for (int j = 0; j < wielkosc; j++)
		{
			cout << msas[i][j] << "  ";
		}

		cout << endl;
	}

	cout << endl;

	return msas; // zwraca nam macierz
}

list <int> *listasasiedztwa(int **macierzsasiedztwa, int n)
{

	list <int> *krawedzie = new list <int>[n + 1]; //utworzenie listy ktora bedzie przechowywała wierzchołki
	for (int pom = 0; pom < n; pom++)
	{
		for (int pom2 = 0; pom2 < n; pom2++)
		{
			if (macierzsasiedztwa[pom][pom2] == 1)
				krawedzie[pom].push_back(pom2); //wstawianie na listę następników danego wierzchołka
		}
	}

	list<int>::iterator it; //iterator listy
	for (int i = 0; i < n; i++)
	{
		cout << i << ": ";
		for (it = krawedzie[i].begin(); it != krawedzie[i].end(); ++it)
		{
			cout << *it << " "; //wypisanie listy nastepnikow
		}

		cout << endl;
	}

	cout << endl;

	return krawedzie;
}


stack <int> euler; //stos do cyklu eulera
void Euler(int **graf, int v) //podajemy na wejście graf, wierzchołek wejsciowy, oraz stos na którym będzie zapisywany cykl
{
	for (int i = 0; i < n; i++) //zmienna i służy do poruszania się po wierzchołkach, odpowiada ona wierzchołkowi który jest sąsiadem wierzchołka v 
	{
		while (graf[v][i] == 1) // jezeli wierzcholek i jest sasiadem wierzcholka v
		{
			graf[v][i] = 0; //usuwamy krawedz miedzy nimi
			graf[i][v] = 0; //usuwamy krawedz miedzy nimi
			Euler(graf, i); //przechodzimy do wierzchołka i
		}
		
	}
	euler.push(v); //wstawiamy na stos wierzchołek V
}

int index = 0; //index do poruszania się po stosie
int *hamilton = new int[n]; //stos z cyklem Hamiltona

void Hamilton(list <int> *listasasiedztwa, int v) //podajemy liste sasiedztwa oraz wierzchołek startowy
{
	
	bool test; // pomocnicza zmienna do testowania cyklu Hamiltona

	hamilton[index++] = v; //wkładamy na stos wierzchołek
	if (index < n) //jeżeli index jest mniejszy od ilosci wierzchołków
	{
	
		visited[v] = true; //odwiedzamy wierzchołek
		list <int>::iterator it2 = listasasiedztwa[v].begin(); //iterator listy 
		for (it2; it2 != listasasiedztwa[v].end(); it2++) //sprawdzamy następników danego wierzchołka
		{
			if (visited[*it2] == false)                                       //w poszukiwaniu nieprzejrzanych wierzchołków
				Hamilton(listasasiedztwa, *it2); //rekurencyjnie przechodzimy dalej
				
					
		}
		visited[v] = false; //gdy się wycofujemy zaznaczamy, że nie odwiedzieliśmy jeszcze tego wierzchołka
	}
	else //sprawdzamy czy mam cykl czy drogę
	{
		test = false; //nasz test jest fałszem ponieważ zakładamy że to droga
		list <int>::iterator it1 = listasasiedztwa[v].begin(); //iterator listy
		for (it1; it1 != listasasiedztwa[v].end(); it1++)//przeglądamy sąsiadów danego wierzcholka
		{
			if (*it1 == 0) //jezeli sasiad wskazuje na początek
			{
				test = true;//mamy cykl
				break; //przerywamy szukanie
			}
		}
		if (test) //jezeli jest cyklem to wypisujemy
		{

			/*cout << "Hamiltonian Cycle :";
			for (int i = 0; i < index; i++)
			{
				cout << hamilton[i];
			}
			cout << 0; //dopisujemy zero poniewaz jest to cykl
			cout << endl;
			*/
		}
		
	}
	
	index--; //ściągamy wierzchołek ze stosu kiedy się wycofujemy
	
	
}



int _tmain(int argc, _TCHAR* argv[])
{
	
	n = 8; //ilość wierzchołków
	double nasycenie;//nasycenie grafu
	nasycenie = 0.3; 
	list <int> *lista1 = new list <int>[n + 1]; //inicjacja listy1 do cyklu hamiltona
	list <int> *lista2 = new list <int>[n + 1]; //inicjacja listy2 do cyklu hamiltona
	list <int> *lista3 = new list <int>[n + 1]; //inicjacja listy3 do cyklu hamiltona
	//Tworzenie tablicy dynamicznej dwuwymiarowej - dla grafu1
	int **graf1 = new int *[n];  //macierzsas = macierz sasiedztwa

	for (int i = 0; i < n; i++)
		graf1[i] = new int[n];
	//Tworzenie tablicy dynamicznej dwuwymiarowej - dla grafu2
	int **graf2 = new int *[n];  //macierzsas = macierz sasiedztwa

	for (int i = 0; i < n; i++)
		graf2[i] = new int[n];

	graf1 = graf(n, nasycenie);
	lista1 = listasasiedztwa(graf1, n);
	Euler(graf1, 0);
	cout << endl;
	cout << "Euler Cycle:  ";
	while (!euler.empty()) //dopóki coś jest na stosie Eulera
	{
		cout << euler.top() << " "; //wypisujemy górę 
		euler.pop(); //ściągamy wartość ze stosu
	}
	cout << endl;
	Hamilton(lista1, 0); //wywołanie cyklu hamiltona
	
	cout << endl;

	cout << endl;
	nasycenie = 0.7;
	graf2 = graf(n, nasycenie);
	lista2 = listasasiedztwa(graf2, n);
	Euler(graf2, 0);
	cout << "Euler Cycle:  ";
	while (!euler.empty())
	{
		cout << euler.top() << " ";
		euler.pop();
	}
	cout << endl;
	Hamilton(lista2, 0);
	cout << endl;
	//Tworzenie tablicy dynamicznej dwuwymiarowej - dla grafu1
	int **graf3 = new int *[n];  //macierzsas = macierz sasiedztwa

	for (int i = 0; i < n; i++)
		graf3[i] = new int[n];
	//Zadanie B wariant 2
	graf3 = graf(n, 0.50);
	lista3 = listasasiedztwa(graf3, n);
	Hamilton(lista3, 0);

	system("PAUSE");
	//usuwanie dynamicznych zmiennych
	delete[] lista1;
	delete[] lista2;
	delete[] lista3;
	delete[] graf1;
	delete[] graf2;
	delete[] graf3;
	return 0;
}

