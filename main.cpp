#include <iostream>
#include <stdlib.h>
#include <string>





using namespace std;

unsigned int globalID = 1;

struct Film
{
    int ID; //unikalne ID
    string title; // TytuĹ filmu
    struct //Data produkcji
    {
        int year; //rok produkcji
        int month; //miesiac produkcji
        int day; //dzien produkcji
    } date;
    string director_name; //imie rezysera
    string director_surname; //nazwisko rezysera
    string studio; //studio nagraniowe
    string genre; //gatunek
    string other; //inne dane
    struct Film *PNext;  //wsjaĹşnik na nastepny
    struct Film *PPrev; //wskaĹşnik na poprzedni

     Film() // konstruktor
    {

        ID = globalID++;
        cout << "ID zostalo przypisane[" << ID << "]" << endl;
        cout << "Podaj tytul: ";
        cin >> title;
        cout << endl << "Podaj date produkcji w formie rok, miesiac, dzien: ";
        cin >> date.year;
        cin >> date.month;
        cin >> date.day;
        cout << endl << "Podaj imie rezysera: ";
        cin >> director_name;
        cout << endl << "Podaj nazwisko rezysera: ";
        cin >> director_surname;
        cout << endl << "Podaj studio w ktorym byl nagrany film: ";
        cin >> studio;
        cout << endl << "Podaj gatunek: ";
        cin >> genre;
        cout << endl << "Podaj inne dane na temat filmu(nagrody, opis, itd, itp): ";
        cin >> other;
        PNext = NULL;
        PPrev = NULL;
    }

    void wypisz()
    {
        cout << "ID: " << ID << endl << "Tytul: " << title << endl << "Data produkcji: " << date.day << "/";
        cout << date.month << "/" << date.year << endl << "Rezyser: ";
        cout << director_name << " " << director_surname << endl << "Studio: " << studio << endl << "Gatunek: " << genre << endl << "Inne: " << other << endl;
    }

    void wyswietl()
    {
        cout << "Tytul:" << title;
        cout << "\tData produkcji: " << date.day << "/";
        cout << date.month << "/" << date.year << endl;
    }

};


Film *HEAD = NULL;



void menu();
void Dodaj_Film(Film **HEAD);
void WyswietlFilmy(Film *HEAD);
Film *WyszukajFilmNazwa(Film *HEAD, string title, int status);
Film *WyszukajFilmID(Film *HEAD, int IDl, int status);
void UsunFilm(Film **HEAD);
void Edytuj(Film **HEAD);
void Sortowanie();



int main()
{

    menu();
    return 0;
}



void menu()
{
    system("CLS");
    short int opcja; //zmienna opcji
    int IDl; //zmienna pomocnicza do wyszukiwania ID
    int z; // zmienna pomkocnicza
    string title1; //zmienna pomocnicza do wyszukiwania tytuĹu
    cout << "1. Dodaj nowy film" << endl << "2. Usun film" << endl << "3. Wyszukaj film" << endl << "4. Wyswietl wszystkie filmy" << endl << "5. Edytuj dane filmu" << endl << "6. Zapisz do pliku" << endl << "7. Odczytaj z pliku" << endl << "8. Koniec pracy" << endl;
    cin >> opcja; // Ktora opcje wybrac

    if(opcja <= 0 || opcja > 8)
    {
        system("CLS");
        cout <<"Wybrales nieodpowiednia opcje. Nacisnij dowolny przycisk" << endl;
        system("PAUSE");
        system("CLS");


    }
    else
    {
        switch (opcja)
        {
        case 1:
            system("CLS");
            Dodaj_Film(&HEAD);
            break;
        case 2:
            system("CLS");
            UsunFilm(&HEAD);
            break;
        case 3:
            system("CLS");
            cout << "Wyszukac po" << endl <<  "1.ID" << endl << "2.Tytul" << endl;
            cin >> z;
            if(z == 1)
            {
                cout << "Wpisz ID: " << endl;
                cin >> IDl;
                WyszukajFilmID(HEAD, IDl, 0);
            }
            else if(z == 2)
            {
                cout << "Podaj tytul: ";
                cin >> title1;
                WyszukajFilmNazwa(HEAD, title1, 0);
            }
            break;
        case 4:
            system("CLS");
            Sortowanie();
            WyswietlFilmy(HEAD);
            break;
        case 5:
            system("CLS");
            Edytuj(&HEAD);
            break;
        case 6:
            system("CLS");
            cout << "Funkcja zapis do pliku";
            break;
        case 7:
            system("CLS");
            cout << "Funkcja odczyt z pliku";
            break;
        case 8:
            system("CLS");
            cout << "Program zamyka sie";
            system("EXIT");
            break;
        default:
            system("CLS");
            menu();

        }

    }
}


void Dodaj_Film(Film **HEAD)
{
    Film *nowy = new Film;
    Film *tmp = (*HEAD);

	if((*HEAD) == NULL) // nowy element bedzie gĹowÄ listy
	{
		*HEAD = nowy;
	}
	else // jeĹli mamy gĹowÄ dodajemy film na koncu listy
	{
        tmp = *HEAD;
		while (tmp->PNext != NULL) // przechodzimy na koniec listy
			tmp = tmp->PNext; //krok do nastÄpnego elementu
		tmp->PPrev = tmp; //ustawiamy obecnt element na poprzedni
		tmp->PNext = nowy;//Nastepny element bedzie nowym obiektem i koncem listy

	}


    menu();


}


void WyswietlFilmy(Film *HEAD)
{


	Film *tmp;
    tmp = HEAD;
	if(tmp == NULL)
	{
	    cout << "Baza jest pusta" << endl;
	}
    else
    {


	cout << "Twoja baza filmow" << endl;
	while(tmp != NULL)
	{
		tmp->wyswietl(); // wypisanie filmĂłw
		cout << endl;
		tmp = tmp->PNext; // przejscie na kolejny element
	}
    }
    system("PAUSE");
    menu();

}

Film *WyszukajFilmNazwa(Film *HEAD, string titlel, int status)
{
    Film *tmp; //pomocniczy wskaĹşnik

	tmp = HEAD;
	while (tmp != NULL && (tmp->title).compare(titlel) != 0) // PÄtla dziaĹa dopĂłki lista jest peĹna
		tmp = tmp->PNext;

    if (tmp == NULL)
    {
    cout << "Nie ma takiego filmu";
    system("PAUSE");
    menu();
    }

    if(status == 0)
    {
    system("CLS");
    tmp->wypisz();
    system("PAUSE");
    menu();
    }
    else
    {
    return tmp;
    }

return 0;
}

Film *WyszukajFilmID(Film *HEAD, int IDl, int status)
{
  Film *tmp; //pomocniczy wskaĹşnik

	tmp = HEAD;

    while (tmp != NULL && (tmp->ID) != IDl)
		tmp = tmp->PNext;


    if (tmp == NULL)
    {
    cout << "Nie ma takiego filmu";
    system("PAUSE");
    menu();
    }

    if(status == 0)
    {
    system("CLS");
    tmp->wypisz();
    system("PAUSE");
    menu();
    }
    else
    {
    return tmp;
    }



    return 0;

}

void UsunFilm(Film **HEAD)
{
    Film *tmp, *tmp1;
    int opcja; //opcja film usuwany po id lub tytule
    string nazwa; //pomocna do wyszukiwania tytulu
    int IDl;//pomocna do wyszukiwania id
    cout << "Po czym chcesz wyszukac film ktory ma byc usuniety?";
    cout << endl << "1.ID" << endl << "2.Tytul" << endl;
    cin >> opcja;
    if(opcja == 1)
    {
        cout << "Podaj ID filmu" << endl;
        cin >> IDl;
        tmp = WyszukajFilmID(*HEAD, IDl, 1);
        if (tmp == NULL)
        cout << "Nie ma takiego filmu";
        else
        {
            if (tmp == *HEAD)
            {
                if(tmp->PNext == NULL)
                {
                    delete tmp;
                    cout << endl << "Film usniety" << endl;
                    *HEAD = NULL;
                    menu();
                }
                else
                {
                *HEAD = (*HEAD)->PNext;
                delete tmp;
                cout << endl << "Film usniety" << endl;
                menu();
                }
            }
            else
            {
                tmp1 = *HEAD;
                while ((tmp1->PNext->ID) != (tmp->ID))
                    tmp1 = tmp1->PNext;
                if (tmp->PNext != NULL)
                    tmp1->PNext->PPrev = tmp->PPrev;
                tmp1->PNext = tmp->PNext;
                delete tmp;
                cout << endl << "Film usniety" << endl;
                system("PAUSE");
                menu();
            }
        }
    }
    else if(opcja == 2)
    {
        cout << "Podaj tytul filmu ktory ma byc usuniety" << endl;
        cin >> nazwa;
        tmp = WyszukajFilmNazwa(*HEAD, nazwa, 1);
        if (tmp == NULL)
        cout << "Nie ma takiego filmu";
        else
        {
            if (tmp == *HEAD)
            {
                if(tmp->PNext == NULL)
                {
                    delete tmp;
                    cout << endl << "Film usniety" << endl;
                    *HEAD = NULL;
                    menu();
                }
                else
                {
                *HEAD = (*HEAD)->PNext;
                delete tmp;
                cout << endl << "Film usniety";
                menu();
                }
            }
            else
            {
                tmp1 = *HEAD;
                while (((tmp1->PNext->title).compare(tmp->title)) != 0)
                    tmp1 = tmp1->PNext;

                if (tmp->PNext != NULL)
                    tmp1->PNext->PPrev = tmp->PPrev;
                tmp1->PNext = tmp->PNext;

                delete tmp;

                cout << endl << "Film usniety";
                menu();
            }
        }
    }
}


void Edytuj(Film **HEAD)
{
    Film *tmp;
    int opcja;
    string nazwa;
    string line;
    int data;
    int IDl;
    cout << "Po czym chcesz wyszukac film ktory ma byc edytowany?";
    cout << endl << "1.ID" << endl << "2.Tytul" << endl;
    cin >> opcja;
    if(opcja == 1)
    {
        cout << "Podaj ID filmu" << endl;
        cin >> IDl;
        tmp = WyszukajFilmID(*HEAD, IDl, 1);
        if (tmp == NULL)
        {
            cout << "Nie ma takiego filmu";
            system("PAUSE");
            menu();
        }

    }
    else if(opcja == 2)
    {
        cout << "Podaj tytul filmu ktory ma byc usuniety" << endl;
        cin >> nazwa;
        tmp = WyszukajFilmNazwa(*HEAD, nazwa, 1);
        if (tmp == NULL)
        {
            cout << "Nie ma takiego filmu";
            system("PAUSE");
            menu();
        }

    }
    cin.clear();
    cout << "Edytujesz film o ID: [" <<tmp->ID << "] " << "o tytule: [" << tmp->title << "]:" << endl;
    cout << "Nowy tytul(wcisnij enter by pozostal bez zmian)[" << tmp->title <<"]: ";
    cin.ignore();
    getline(cin, line);
    if(!line.empty())
        tmp->title = line;
    cout << endl << "Nowy Tytul: " << tmp->title << endl;
    cout << "posortowana Data Produkcji(wcisnij enter by pozostal bez zmian)[" << tmp->date.day << "/" << tmp->date.month << "/" << tmp->date.year <<"]: "<< endl;
    cout << "Podaj dzien produkcji :";
    cin.clear();
    getline(cin, line);
    if(!line.empty())
    {
        data = atoi(line.c_str());
        tmp->date.day = data;
    }

    cout << endl << "Podaj miesiac produkcji: ";
    getline(cin, line);
    if(!line.empty())
    {
        data = atoi(line.c_str());
        tmp->date.month = data;
    }
    cout << endl << "Podaj rok produkcji: ";
    getline(cin, line);
    if(!line.empty())
    {
        data = atoi(line.c_str());
        tmp->date.year = data;
    }
    cout << endl << "posortowana data: " << tmp->date.day << "/" << tmp->date.month << "/" << tmp->date.year << endl;
    cout << "Zmien imie rezysera (wcisnij enter by pozostal bez zmian)[" << tmp->director_name <<"]: ";
    cin.ignore();
    getline(cin, line);
    if(!line.empty())
        tmp->director_name = line;
    cout << endl << "Imie Rezysera Teraz: " << tmp->director_name << endl;
    cout << "Zmien nazwisko rezysera(wcisnij enter by pozostal bez zmian)[" << tmp->director_surname <<"]: ";
    cin.ignore();
    getline(cin, line);
    if(!line.empty())
        tmp->director_surname = line;
    cout << endl << "Nazwisko rezysera teraz: " << tmp->director_surname << endl;
    cout << "posortowana nazwa studia(wcisnij enter by pozostal bez zmian)[" << tmp->studio <<"]: ";
    cin.ignore();
    getline(cin, line);
    if(!line.empty())
        tmp->studio = line;
    cout << endl << "Zmienione Studio: " << tmp->studio << endl;
    cout << "Zmien gatunek(wcisnij enter by pozostal bez zmian)[" << tmp->genre <<"]: ";
    cin.ignore();
    getline(cin, line);
    if(!line.empty())
        tmp->genre = line;
    cout << endl << "Zmieniony gatunek: " << tmp->genre << endl;
    cout << "Nowy opis(wcisnij enter by pozostal bez zmian)[" << tmp->other <<"]: ";
    cin.ignore();
    getline(cin, line);
    if(!line.empty())
        tmp->other = line;
    cout << endl << "Zmienione Studio: " << tmp->other << endl;


    system("PAUSE");
    menu();
}

void Sortowanie()
{

 if (HEAD != NULL)
    {
        Film *curr = HEAD;
        curr->PPrev = NULL;
        Film *temp = NULL;
        bool changeFlag = false;
        while(HEAD != NULL)
        {


            while (curr->PNext != NULL)
            {
                temp = curr->PNext;

                if (curr->title > temp->title)
                {
                    changeFlag = true;
                    curr->PNext = temp->PNext;
                    temp->PNext = curr;
                    if (curr->PPrev != NULL)
                        curr->PPrev->PNext = temp;
                    curr->PPrev = temp;
                    if (HEAD == curr)
                        HEAD = temp;
                    if (curr->PNext == NULL)
                        break;
                }
                else
                {

                        curr->PPrev = curr;
                        curr = curr->PNext;


                }

            }

        if (changeFlag == false)
        {
            break;
        }

        else
        {
        curr->PPrev = NULL;
        curr = HEAD;
        changeFlag = false;
        }

        }

    }

}




