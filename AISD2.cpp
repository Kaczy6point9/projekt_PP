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
	
		if (wartosc < this->wartosc) {
			if (lewy == NULL) {
				lewy = new BSTkorzen(wartosc);
				lewy->rodzic = this;
				return true;
			}
			else
				return lewy->dodaj(wartosc);
		}
		else if (wartosc >= this->wartosc) {
			if (prawy == NULL) {
				prawy = new BSTkorzen(wartosc);
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
		korzen = NULL;
	}

	//szukanie wartosci maks i minimum
	BSTkorzen *Minimum(BSTkorzen *start)//zwraca wartość minimalną w drzewie
	{
		while (start->lewy != NULL)
		{
			start = start->lewy;
		}

		return start;
	}
	BSTkorzen *Maximum(BSTkorzen *start)//zwraca wartosc maksymalna drzewa
	{
		while (start->prawy != NULL)
		{
			start = start->prawy;
		}

		return start;
	}

	//dodawanie do drzewa
	bool dodaj(int wartosc)
	{
		if (korzen == NULL) {
			korzen = new BSTkorzen(wartosc);
			return true;
		}
		else
			return korzen->dodaj(wartosc);
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
		if (start == NULL || start->wartosc == element) return start;

		if (element < start->wartosc) return wyszukiwanie(element, start->lewy);
		else return wyszukiwanie(element, start->prawy);
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
	



	drzewoAVL(int x[], int n)
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
		
	
		if (start > koniec) return NULL;
		int srodek = start + (koniec - start) / 2;
		drzewoAVL *korzen = new drzewoAVL(x[srodek]);
		korzen->ustawLewy(dodaj(x, start, srodek - 1, korzen));
		korzen->ustawPrawy(dodaj(x, srodek + 1, koniec, korzen));
		korzen->rodzic = rodzic;
		return korzen;

			
	}
	drzewoAVL *dodaj(int x[], int n)
	{
		return dodaj(x, 0, n - 1, NULL);
	}
	bool dodajwartosc(int wartosc)
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

	for (int i = 0; i < n; i++)
	{
		drzewkoBST->dodaj(ciaglosowy[i]);
	}
	drzewoAVL *drzewkoAVL = new drzewoAVL(ciag, n);
	drzewoBST *zdegenerowaneBST = new drzewoBST;
	//wyszukiwania
	for (int i = 0; i < n; i++)
	{
		zdegenerowaneBST->dodaj(ciag[i]);
	}
	for (int i = 0; i < n / 10; i++)
	{
		int szukana = rand() % n;
		cout << "Wartosci wyszukane w drzewie BST to: " << drzewkoBST->wyszukiwanie(szukana, drzewkoBST->korzen)->wartosc << endl;
	}
	cout << endl;
	for (int i = 0; i < n / 10; i++)
	{
		int szukana = rand() % n;
		cout << "Wartosci wyszukane w drzewie AVL to: " << drzewkoAVL->wyszukiwanie(szukana, drzewkoAVL->korzenglowny)->wartosc << endl;
	}
	cout << endl;
	for (int i = 0; i < n / 10; i++)
	{
		int szukana = rand() % n;
		cout << "Wartosci wyszukane w zdegenerowanym drzewie BST to: " << zdegenerowaneBST->wyszukiwanie(szukana, zdegenerowaneBST->korzen)->wartosc << endl;
	}
	cout << endl;
	 
	//dodawanie elementu
	int pom = n - 1;
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


	drzewkoBST->InorderTreeWalk(drzewkoBST->korzen);
	cout << endl;
	drzewkoAVL->InorderTreeWalk(drzewkoAVL->korzenglowny);
	cout << endl;
	zdegenerowaneBST->InorderTreeWalk(zdegenerowaneBST->korzen);
	cout << endl;
	drzewkoBST->UsunDrzewo(drzewkoBST->korzen);
	drzewkoAVL->UsunDrzewo(drzewkoAVL->korzenglowny);
	zdegenerowaneBST->UsunDrzewo(zdegenerowaneBST->korzen);
	
	
	
			
	
	
	
	
	system("PAUSE");
	return 0;
}

