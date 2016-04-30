// AIDS3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>

using namespace std;

class BSTkorzen
{

public:
	int wartosc;
	BSTkorzen *rodzic;
	BSTkorzen *lewy;
	BSTkorzen *prawy;


	
	BSTkorzen(int wart) //konstruktor ktory przypisuje wartosc korzeniowi
	{
		this->wartosc = wart; //przypisanie wartosci do korzenia
		this->lewy = NULL;//lewy jest pusty
		this->prawy = NULL; //prawy tez jest ustawiony na pusty
		this->rodzic = NULL;

	}

	bool dodaj(int wartosc)
	{
	
		if (wartosc < this->wartosc) { //jezeli wartośc jest mniejsza od wartości tego korzenia
			if (lewy == NULL) { //sprawdzamy czy lewe podrzewo jest puste
				lewy = new BSTkorzen(wartosc); //jezeli jest puste tworzymy nowe poddrzewo
				lewy->rodzic = this; //ustawiamy rodzica nowego poddrzewa
				return true;
			}
			else
				return lewy->dodaj(wartosc); //jesli nie jest puste schodzimy niżej w lewą stronę
		}
		else if (wartosc >= this->wartosc) { //jeżeli wartość jest wieksza 
			if (prawy == NULL) { //idziemy w prawo
				prawy = new BSTkorzen(wartosc); //analogia jak wyżej
				prawy->rodzic = this;
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

	//konstruktor drzewa
	drzewoBST()
	{
		korzen = NULL; //ustawiamy korzen głowny na pusty przy tworzeniu drzewa
	}

	//szukanie wartosci maks i minimum
	BSTkorzen *Minimum(BSTkorzen *start)//zwraca wartość minimalną w drzewie
	{
		while (start->lewy != NULL)
		{
			start = start->lewy; //dopoki jest lewe poddrzewo schodzimy w lewo
		}

		return start; //zwracamy wartość najbardziej lewego poddrzewa
	}
	BSTkorzen *Maximum(BSTkorzen *start)//zwraca wartosc maksymalna drzewa
	{
		while (start->prawy != NULL) //dopóki jest prawe poddrzewo 
		{
			start = start->prawy; //schodzimy prawo
		}

		return start; //zwaracamy wartosc najbardziej prawego poddrzewa
	}

	//wysokosc drzewa
	int wysokosc(BSTkorzen *start)
	{
		if (start == NULL)
			return 0;
		else
		{
			int lewawysokosc = wysokosc(start->lewy);
			int prawawysokosc = wysokosc(start->prawy);

			if (lewawysokosc > prawawysokosc)
				return (lewawysokosc + 1);
			else return (prawawysokosc + 1);
		}

	}
	void wyswysokosc(BSTkorzen *start)
	{
		if (start != NULL)
		{
			cout << start->wartosc << "|" << wysokosc(start) << endl;
			wyswysokosc(start->lewy);
			wyswysokosc(start->prawy);

		}

	}

	
	//dodawanie do drzewa
	bool dodaj(int wartosc)
	{
		if (korzen == NULL) { //jesli drzewo jest puste
			korzen = new BSTkorzen(wartosc); //tworzymy nowy korzen głowny
			return true;
		}
		else
			return korzen->dodaj(wartosc); //jesli nie jest puste sprawdzamy dzieci kod opisany wyżej
	}

	//chodzenie po drzewie
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

	//wyszukiwanie elementu
	BSTkorzen *wyszukiwanie(int element, BSTkorzen *start)
	{
		if (start == NULL || start->wartosc == element) return start; //jeżeli korzen jest pusty, albo jest równy szukanemu elementowi zwaracamy szukany element

		if (element < start->wartosc) return wyszukiwanie(element, start->lewy); //jeśli szukany element jest mniejszy od wartosci przy której jesteśmy, schodzimy rekurencyjnie w lewo
		else return wyszukiwanie(element, start->prawy); // w przeciwnym wypadku w prawo
	}
	
	//Usuwanie
	void UsunKorzen(BSTkorzen *usuwany)
	{
		
		if (usuwany->lewy == NULL && usuwany->prawy == NULL) //Jeżeli nasz korzeń nie ma dzieci
		{
			if (usuwany->rodzic == NULL) //i nasz korzen jest korzeniemglownym
			{
				korzen = NULL; //staje się pusty
			}
			else if (usuwany->rodzic->lewy == usuwany) //jesli jest on lewym podrzewem
			{
				usuwany->rodzic->lewy = NULL; //wtedy ustawiamy,że lewe podrzewo jego rodzica staje sie puste
			}
			else //jesli jest on prawym podrzewem
			{	
				usuwany->rodzic->prawy = NULL;  //wtedy ustawiamy, że prawe podrzewo jego rodzica staje się puste
			}
			delete usuwany; //czyscimy pamiec z tego elementu
		}
		
		else if (usuwany->lewy == NULL || usuwany->prawy == NULL) //Jeżeli korzeń ma tylko jedno dziecko
		{
			if (usuwany->lewy == NULL) //i usuwany korzen nie ma lewego dziecka
			{
				if (usuwany->rodzic == NULL) //i jest korzeniem głownym
				{
					korzen = usuwany->prawy; //naszym korzeniem głownym staje się prawe podrzewo
				}
				
				else if (usuwany->rodzic->lewy == usuwany) //jezeli korzen jest po lewej stronie swojego rodzica
				{
					
					usuwany->rodzic->lewy = usuwany->prawy; //to lewe dziecko rodzica teraz staje się prawym podrzewem usuwanego podrzewa
				}
				else //jeżeli jest po prawej stronie swojego rodzica
				{
					
					usuwany->rodzic->prawy = usuwany->prawy; //to prawe dziecko rodzica teraz staje się prawym podrzewem usuwanego podrzewa
				}
			}
			else //jeżeli usuwany korzen nie ma prawego dziecka
			{
				
				if (usuwany->rodzic == NULL)//i jest korzeniem głownym
				{
					korzen = usuwany->lewy; // naszym korzeniem głownym staje się lewe podrzewo
				}
				else if (usuwany->rodzic->lewy == usuwany) //jezeli korzen jest po lewej stronie swojego rodzica
				{
					usuwany->rodzic->lewy = usuwany->lewy; //to lewe dziecko rodzica teraz staje się lewym podrzewem usuwanego podrzewa
				}
				else //jeżeli jest po prawej stronie swojego rodzica
				{
					usuwany->rodzic->prawy = usuwany->lewy; //to prawe dziecko rodzica teraz staje się lewym podrzewem usuwanego podrzewa
				}
			}
			delete usuwany; //zwalniamy pamięć z tego elementu
		}
		else //jeżeli ma oba dzieci
		{
			//Wstawiamy w miejsce usuwanego elementu najmniejszą wartość prawego podrzewa
			BSTkorzen *temp; 
			temp = Minimum(usuwany->prawy);
			usuwany->wartosc = temp->wartosc;
			UsunKorzen(temp);
		}

	}
	void UsunDrzewo(BSTkorzen *start)
	{
		if (start != NULL)
		{
			UsunDrzewo(start->lewy);
			UsunDrzewo(start->prawy);
			delete start;
		}
	}

	
};

int wielkosctablicydorownowazenia = 0; //wielkość tablicy która rownoważy drzewo
class drzewoAVL
{

public:
	int wartosc;
	drzewoAVL *korzenglowny;
	drzewoAVL *rodzic;
	drzewoAVL *lewy;
	drzewoAVL *prawy;
	



	drzewoAVL(int x[], int n) //konstruktor który przypisuje do korzenia głownego drzewo które powstaje poprzez bisekcje
	{
		korzenglowny = dodaj(x, n); 
	}
	
	drzewoAVL(int wart) //konstruktor ktory przypisuje wartosc korzeniowi
	{
		this->wartosc = wart; //przypisanie wartosci do korzenia
		this->lewy = NULL;//lewy jest pusty
		this->prawy = NULL; //prawy tez jest ustawiony na pusty
		this->rodzic = NULL; //jego rodzic jest pusty
	}

	void ustawLewy(drzewoAVL *lewy) 
	{
		this->lewy = lewy;
	}
	void ustawPrawy(drzewoAVL *prawy) 
	{
        this->prawy = prawy;
	}
	//wyswietlanie wysokosci
	int wysokosc(drzewoAVL *start)
	{
		if (start == NULL)
			return 0;
		else
		{
			int lewawysokosc = wysokosc(start->lewy);
			int prawawysokosc = wysokosc(start->prawy);

			if (lewawysokosc > prawawysokosc)
				return (lewawysokosc + 1);
			else return (prawawysokosc + 1);
		}
		
	}
	void wyswysokosc(drzewoAVL *start)
	{
		if (start != NULL)
		{
			cout << start->wartosc << "|" << wysokosc(start) << endl;
			wyswysokosc(start->lewy);
			wyswysokosc(start->prawy);

		}
		
	}

	//szukanie wartosci maks i minimum
	drzewoAVL *Minimum(drzewoAVL *start)//zwraca wartość minimalną w drzewie
	{
		while (start->lewy != NULL)
		{
			start = start->lewy;
		}

		return start;
	}
	drzewoAVL *Maximum(drzewoAVL *start)//zwraca wartosc maksymalna drzewa
	{
		while (start->prawy != NULL)
		{
			start = start->prawy;
		}

		return start;
	}

	//Dodawanie wartosci do drzewa
	drzewoAVL *dodaj(int x[], int start, int koniec, drzewoAVL *rodzic)
	{
		
	
		if (start > koniec) return NULL; //jeżeli początek jest większy od zwracamy nic, zapobiega overflow
		int srodek = start + (koniec - start) / 2; // ustawiamy srodek
		drzewoAVL *korzen = new drzewoAVL(x[srodek]); //tworzymy nowy korzen który ma wartość środka tablicy
		korzen->ustawLewy(dodaj(x, start, srodek - 1, korzen)); //lewy podrzewo jest lewą stroną podzielonej tablicy
		korzen->ustawPrawy(dodaj(x, srodek + 1, koniec, korzen)); //prawe poddrzewo jest prawą stroną podzielonej tablicy
		korzen->rodzic = rodzic; //rodzic jest równy rodzicowi podanemu w argmuencie czyli w tym wypadku poprzednim poddrzewem
		return korzen; //zwraca podrzewo

			
	}
	drzewoAVL *dodaj(int x[], int n)
	{
		return dodaj(x, 0, n - 1, NULL);
	}
	bool dodajwartosc(int wartosc) //opisane wyżej
	{

		if (wartosc < this->wartosc) {
			if (lewy == NULL) {
				lewy = new drzewoAVL(wartosc);
				return true;
			}
			else
				return lewy->dodajwartosc(wartosc);
		}
		else if (wartosc >= this->wartosc) {
			if (prawy == NULL) {
				prawy = new drzewoAVL(wartosc);
				return true;
			}
			else
				return prawy->dodajwartosc(wartosc);
		}
		return false;
	}

	//Równoważenie drzewa
	void InorderWTablicy(drzewoAVL *start)
	{
		if (start != NULL)
		{
			InorderWTablicy(start->lewy);
			wielkosctablicydorownowazenia++;
			InorderWTablicy(start->prawy);
		}
	}
	int InorderDoTablicy(drzewoAVL *start, int x[], int i)
	{
		if (start != NULL)
		{
			i = InorderDoTablicy(start->lewy, x, i);
			x[i] = start->wartosc;
			i++;
			i = InorderDoTablicy(start->prawy, x, i);

			return i;
		}
		else return i;
	}
	drzewoAVL *rownowazenie()
	{
		int *tablicadorownowazenia;
		int pom = 0;
		InorderWTablicy(korzenglowny);
		tablicadorownowazenia = new int[wielkosctablicydorownowazenia];
		InorderDoTablicy(korzenglowny, tablicadorownowazenia, pom);
		UsunDrzewo(korzenglowny);
		
		return korzenglowny = dodaj(tablicadorownowazenia, wielkosctablicydorownowazenia);

	}

	

	
	//wyszukiwanie elementu w drzewie
	drzewoAVL *wyszukiwanie(int element, drzewoAVL *start)
	{
		if (start == NULL || start->wartosc == element) return start;

		if (element < start->wartosc) return wyszukiwanie(element, start->lewy);
		else return wyszukiwanie(element, start->prawy);
	}

	//chodzenie po drzewie
	void InorderTreeWalk(drzewoAVL *start)
	{
		if (start != NULL)
		{
			InorderTreeWalk(start->lewy);
			cout << start->wartosc << endl;
			InorderTreeWalk(start->prawy);
		}
	}

	//usuwanie
	void UsunKorzen(drzewoAVL *usuwany)
	{

		if (usuwany->lewy == NULL && usuwany->prawy == NULL) //Jeżeli nasz korzeń nie ma dzieci
		{
			if (usuwany->rodzic == NULL) //i nasz korzen jest korzeniemglownym
			{
				korzenglowny = NULL; //staje się pusty
			}
			else if (usuwany->rodzic->lewy == usuwany) //jesli jest on lewym podrzewem
			{
				usuwany->rodzic->lewy = NULL; //wtedy ustawiamy,że lewe podrzewo jego rodzica staje sie puste
			}
			else //jesli jest on prawym podrzewem
			{
				usuwany->rodzic->prawy = NULL;  //wtedy ustawiamy, że prawe podrzewo jego rodzica staje się puste
			}
			delete usuwany; //czyscimy pamiec z tego elementu
		}

		else if (usuwany->lewy == NULL || usuwany->prawy == NULL) //Jeżeli korzeń ma tylko jedno dziecko
		{
			if (usuwany->lewy == NULL) //i usuwany korzen nie ma lewego dziecka
			{
				if (usuwany->rodzic == NULL) //i jest korzeniem głownym
				{
					korzenglowny = usuwany->prawy; //naszym korzeniem głownym staje się prawe podrzewo
				}

				else if (usuwany->rodzic->lewy == usuwany) //jezeli korzen jest po lewej stronie swojego rodzica
				{

					usuwany->rodzic->lewy = usuwany->prawy; //to lewe dziecko rodzica teraz staje się prawym podrzewem usuwanego podrzewa
				}
				else //jeżeli jest po prawej stronie swojego rodzica
				{

					usuwany->rodzic->prawy = usuwany->prawy; //to prawe dziecko rodzica teraz staje się prawym podrzewem usuwanego podrzewa
				}
			}
			else //jeżeli usuwany korzen nie ma prawego dziecka
			{

				if (usuwany->rodzic == NULL)//i jest korzeniem głownym
				{
					korzenglowny = usuwany->lewy; // naszym korzeniem głownym staje się lewe podrzewo
				}
				else if (usuwany->rodzic->lewy == usuwany) //jezeli korzen jest po lewej stronie swojego rodzica
				{
					usuwany->rodzic->lewy = usuwany->lewy; //to lewe dziecko rodzica teraz staje się lewym podrzewem usuwanego podrzewa
				}
				else //jeżeli jest po prawej stronie swojego rodzica
				{
					usuwany->rodzic->prawy = usuwany->lewy; //to prawe dziecko rodzica teraz staje się lewym podrzewem usuwanego podrzewa
				}
			}
			delete usuwany; //zwalniamy pamięć z tego elementu
		}
		else //jeżeli ma oba dzieci
		{
			//Wstawiamy w miejsce usuwanego elementu najmniejszą wartość prawego podrzewa
			drzewoAVL *temp;
			temp = Minimum(usuwany->prawy);
			usuwany->wartosc = temp->wartosc;
			UsunKorzen(temp);
		}

	}
	void UsunDrzewo(drzewoAVL *start)
	{
		if (start != NULL)
		{
			UsunDrzewo(start->lewy);
			UsunDrzewo(start->prawy);
			delete start;
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
	int n, *ciag, *ciaglosowy; //deklaracja dlugosci ciagu, i wskaznika na ciag

	cout << "Podaj liczbe elementow ciagu: ";
	cin >> n; //podanie wielkosci ciagu
	ciag = new int[n]; //stworzenie nowej tablicy dynamicznej o wielkosci podanej przez uzytkownika
	ciaglosowy = new int[n];
	wypelnijtablicerosnaco(ciag, n);
	wypelnijtablicelosowo(ciaglosowy, n);
	drzewoBST *drzewkoBST = new drzewoBST;
	/*double roznica;
	cout.setf(ios::fixed);
	cout.precision(5);
	clock_t start, koniec;
	start = clock();
	koniec = clock();
	roznica = (koniec - start) / (double)CLOCKS_PER_SEC;
	cout << "Czas wykonania algorytmu IS: " << roznica << endl;
	*/
	for (int i = 0; i < n; i++)
	{
		drzewkoBST->dodaj(ciaglosowy[i]);
	}

	drzewoAVL *drzewkoAVL = new drzewoAVL(ciag, n);
	drzewoBST *zdegenerowaneBST = new drzewoBST;
		for (int i = 0; i < n; i++)
	{
		zdegenerowaneBST->dodaj(ciag[i]);
	}
	
	//wyszukiwania
		/*
	for (int i = 0; i < n / 10; i++) //pętla wykonuje się od 0 do n/10 wartości, czyli jeśli mamy 1000 elementów pętla wykona się 100 razy
	{
		int szukana = rand() % n;
		//cout << "Wartosci wyszukane w drzewie BST to: " << drzewkoBST->wyszukiwanie(szukana, drzewkoBST->korzen)->wartosc << endl;
	}
	cout << endl;
	for (int i = 0; i < n / 10; i++)
	{
		int szukana = rand() % n;
		//cout << "Wartosci wyszukane w drzewie AVL to: " << drzewkoAVL->wyszukiwanie(szukana, drzewkoAVL->korzenglowny)->wartosc << endl;
	}
	cout << endl;
	for (int i = 0; i < n / 10; i++)
	{
		int szukana = rand() % n;
		//cout << "Wartosci wyszukane w zdegenerowanym drzewie BST to: " << zdegenerowaneBST->wyszukiwanie(szukana, zdegenerowaneBST->korzen)->wartosc << endl;
	}
	cout << endl;
	 
	//dodawanie elementu
	int pom = n - 1; // pomocnicza wartość, przechowuje numer indeksu potrzebny do chodzenia od tyłu po tablicy
	for (int i = 0; i < n/10; i++)
	{
		drzewkoBST->dodaj(ciaglosowy[pom]);
		pom--;
	}
	pom = n - 1;
	for (int i = 0; i < n / 10; i++)
	{
		drzewkoAVL->korzenglowny->dodajwartosc(ciag[pom]);
		pom--;
	}
	drzewkoAVL->rownowazenie();
	pom = n - 1;
	for (int i = 0; i < n / 10; i++)
	{
		zdegenerowaneBST->dodaj(ciag[pom]);
		pom--;
	}
	
	//usuwanie losowogo elementu
	for (int i = 0; i < n / 10; i++)
	{
		int usuwany = rand() % n;
		drzewkoBST->UsunKorzen(drzewkoBST->wyszukiwanie(usuwany, drzewkoBST->korzen));
	}
	for (int i = 0; i < n / 10; i++)
	{
		int usuwany = rand() % n;
		drzewkoAVL->UsunKorzen(drzewkoAVL->wyszukiwanie(usuwany, drzewkoAVL->korzenglowny));
	}
	for (int i = 0; i < n / 10; i++)
	{
		int usuwany = rand() % n;
		zdegenerowaneBST->UsunKorzen(zdegenerowaneBST->wyszukiwanie(usuwany, zdegenerowaneBST->korzen));
	}
	*/
		
		
	/*cout << "Tabela wysokosci dla BST:" << endl;
	drzewkoBST->wyswysokosc(drzewkoBST->korzen);
	cout << "Tabela wysokosci dla AVL:" << endl;
	drzewkoAVL->wyswysokosc(drzewkoAVL->korzenglowny);
	cout << "Tabela wysokosci dla Zdegenerowanego BST:" << endl;
	zdegenerowaneBST->wyswysokosc(zdegenerowaneBST->korzen);
	*/

	//drzewkoBST->InorderTreeWalk(drzewkoBST->korzen);
	//cout << endl;
	//drzewkoAVL->InorderTreeWalk(drzewkoAVL->korzenglowny);
	//cout << endl;
	//zdegenerowaneBST->InorderTreeWalk(zdegenerowaneBST->korzen);
	//cout << endl;
	drzewkoBST->UsunDrzewo(drzewkoBST->korzen);
	drzewkoAVL->UsunDrzewo(drzewkoAVL->korzenglowny);
	zdegenerowaneBST->UsunDrzewo(zdegenerowaneBST->korzen);
	
	
	
			
	
	
	
	
	system("PAUSE");
	return 0;
}

