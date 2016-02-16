#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <istream>




//BAZA FILMÓW
//PROJEKT NA ZALICZENIE Podstaw Programowania
//CREATED BY MACIEJ KACZOR



using namespace std;

unsigned int globalID = 1;

struct Film
{
    int ID; //unikalne ID
    string title; // Tytuł filmu
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
    struct Film *PNext;  //wsjaźnik na nastepny
    struct Film *PPrev; //wskaźnik na poprzedni

    Film() // konstruktor
    {

        ID = globalID++;
        cout << "ID zostalo przypisane[" << ID << "]" << endl;
        cout << "Podaj tytul: ";
        cin.clear();
        cin.ignore();
        getline(cin, title); // przypisanie tytulu
        cout << "Data Produkcji: "<< endl;

        while(1)
        {
            cout << "Podaj dzien produkcji :";
            cin >> date.day;//przypisanie dnia produkcji podajemy wartosc poki bedzie cyfra
            if(!cin)
            {
                cout << "Wpisales slowo wpisz odpowiednia date" << endl;
                cin.clear();
                cin.ignore();
            }
            else if(date.day > 31 || date.day < 1 ) // jesli data wychodzi poza zarkes wyswietla sie komunikat, jesli nie idzie dalej
            {
                cout << "Podales zly dzien miesiaca" << endl;
            }
            else
                break;



        }

          while(1)
        {
            cout << endl << "Podaj miesiac produkcji: ";
            cin >> date.month;//przypisanie miesiaca produkcji podajemy wartosc poki bedzie cyfra
            if(!cin)
            {
                cout << "Wpisales slowo wpisz odpowiednia date" << endl;
                cin.clear();
                cin.ignore();
            }
            else   if(date.month > 12 || date.month < 1 )// jesli data wychodzi poza zarkes wyswietla sie komunikat, jesli nie idzie dalej
            {
                cout << "Podales zly miesiaca" << endl;
            }
            else
                break;


        }

          while(1)
        {
            cout << endl << "Podaj rok produkcji: ";
            cin >> date.year;
            if(!cin) //przypisanie roku produkcji podajemy wartosc dopoki bedzie cyfra
            {
                cout << "Wpisales slowo wpisz odpowiednia date" << endl;
                cin.clear();
                cin.ignore();
            }
               if(date.year < 1900 )// jesli data wychodzi poza zarkes wyswietla sie komunikat, jesli nie idzie dalej
            {
                cout << "Podales rok w ktorym nie produkowali filmow/albo wpisales slowo";

            }
            else
                break;

        }
        cin.clear();
        cin.ignore();
        cout << endl << "Podaj imie rezysera: ";
        getline(cin, director_name); //przypisanie imienia rezysera
        cout << endl << "Podaj nazwisko rezysera: ";
        getline(cin, director_surname); //przypisanie nazwiska rezysera
        cout << endl << "Podaj nazwe studia: ";
        getline(cin, studio); //przypisanie studia
        cout << endl << "Gatunek: ";
        getline(cin, genre); //przypisanie gatunku
        cout << endl << "Opis(nagrody etc.): ";
        getline(cin, other); //przypisanie opisu
        PNext = NULL; //ustawienie wskaźnika na następny na pusty element
        PPrev = NULL; //ustawienie wskaźnika na poprzedni na pusty element
    }

    Film(string row) //konstruktor z argumentem
    {
        string split; // zmienna przechowujaca podzielona czesc stringa
        int counter=0; //pomocniczy licznik pokazuje jakie pole aktualnie przypisuje
        int data; //zmienna przechowujace zmienne typu stalego
        PNext = NULL; //ustawia następnik na pusty element
        PPrev = NULL; //ustawia poprzednik na pusty element
        istringstream iss(row); //zmienia stringa na strumien wyjsciowy dla getline
        while(getline(iss, split, ';')) //getline rozdziela rekord na oddzielne slowa/dane ktore beda przypisane do elementu
        {

            switch (counter) //zaleznie od tego na co wskazuje nasz counter
            {
                case 0: //przypisuje do ID
                    data = atoi(split.c_str());//zmienia stringa na inta
                    ID = data;
                    globalID=ID+1;
                    break;
                case 1: //przypisuje tytul
                    title = split;
                    break;
                case 2: // przypisuje dzien produkcji
                    data = atoi(split.c_str()); //zmienia stringa na inta
                    date.day = data;
                case 3: //przypisuje miesiac daty
                    data = atoi(split.c_str());//zmienia stringa na inta
                    date.month = data;
                    break;
                case 4: //przypisuje rok produkcji
                    data = atoi(split.c_str());//zmienia stringa na inta
                    date.year = data;
                    break;
                case 5: //przypisuje imie rezysera
                    director_name = split;
                    break;
                case 6:
                    director_surname = split; // przypisuje nazwisko rezysera
                    break;
                case 7:
                    studio = split; //przypisanie studia
                    break;
                case 8:
                    genre = split; //przypisanie rodzaju
                    break;
                case 9:
                    other = split; //przypisanie opisu
                    break;
                default:
                    cout << "Cos poszlo nie tak" << endl; //jesli cos nie tak wywala komunikat
            }
            counter++; //zwieksza sie counter ktory wskazuje pole
        }
    }

    void wypisz() //funkcja wypisuje wszystkie wiadomosci o filmie
    {
        cout << "ID: " << ID << endl << "Tytul: " << title << endl << "Data produkcji: " << date.day << "/";
        cout << date.month << "/" << date.year << endl << "Rezyser: ";
        cout << director_name << " " << director_surname << endl << "Studio: " << studio << endl << "Gatunek: " << genre << endl << "Inne: " << other << endl;
    }

    void wyswietl() // funkcja wyswietla tytul i date produkcji
    {
        cout << "Tytul:" << title;
        cout << "\tData produkcji: " << date.day << "/";
        cout << date.month << "/" << date.year << endl;
    }

};


Film *HEAD = NULL; // ustawia nasza głowe na pustą



void menu(); // funkcja wywołuje menu
void Dodaj_Film(Film **HEAD); //funkcja dodaje film
void WyswietlFilmy(Film *HEAD); //funkcja wswietla wszystkie filmy
void WyswietlFilmyRezysera(Film *HEAD, string directro); //wyswuetka fukny dabegi rezysera
void WyswietlFilmyStudia(Film *HEAD, string studio_name); //wyswietla filmy danego studia
void WyswietlFilmyRok(Film *HEAD, int prodyear); //wyswietla filmy wyprudokowane w danym roku
Film *WyszukajFilmNazwa(Film *HEAD, string title, int status); //wyszukuje film po nazwie
Film *WyszukajFilmID(Film *HEAD, int IDl, int status); //wyszukuje film po ID
void UsunFilm(Film **HEAD); //funkcja usuwa film
void Edytuj(Film **HEAD); //edytuje film
void Sortowanie(Film **HEAD); //sortuje baze
void zapisz_do_pliku(Film *HEAD); //zapis bazy do pliku
void odczyt_z_pliku(Film **HEAD); // wczytanie bazy z pliku




int main()
{

    menu(); //wywoluje funce menu
    return 0;
}



void menu()
{
    system("CLS"); //czysci ekran
    short int opcja; //zmienna opcji
    int IDl; //zmienna pomocnicza do wyszukiwania ID
    int z; // zmienna pomkocnicza
    string title1; //zmienna pomocnicza do wyszukiwania tytułu
    cout << "1. Dodaj nowy film" << endl << "2. Usun film" << endl << "3. Wyszukaj film" << endl << "4. Wyswietl wszystkie filmy" << endl << "5. Edytuj dane filmu" << endl << "6. Zapisz do pliku" << endl << "7. Odczytaj z pliku" << endl << "8. Koniec pracy" << endl;
    cin >> opcja; // Ktora opcje wybrac

    if(!cin)// jesli podales ciag nie liczbowy
    {
        cout << "Nie podales cyfry!";
        system("PAUSE");
        menu(); // wywoluje menu od nowa
    }
    else if(opcja <= 0 || opcja > 8) // jesli opcja wychodzi za zakres
    {
        system("CLS");
        cout <<"Wybrales nieodpowiednia opcje. Nacisnij dowolny przycisk" << endl;
        system("PAUSE");
        system("CLS");
        menu(); //wywoluje od nowa film


    }
    else
    {
        switch (opcja)
        {
        case 1:
            system("CLS");
            Dodaj_Film(&HEAD); //wywolanie funkcji dodwania
            break;
        case 2:
            system("CLS");
            UsunFilm(&HEAD);
            break;
        case 3:
            system("CLS");
            cout << "Wyszukac po" << endl <<  "1.ID" << endl << "2.Tytul" << endl;
            cin >> z;
            if(z == 1) //pytanie o to czy wyszukac film po ID czy po nazwie
            {
                cout << "Wpisz ID: " << endl;
                cin >> IDl; // id ktore ma byc porownane
                WyszukajFilmID(HEAD, IDl, 0); //wywoluje funkcje wyszukiwania ze statusem 0
            }
            else if(z == 2)
            {
                cout << "Podaj tytul: ";
                cin >> title1; // tytul ktory ma byc porownany
                WyszukajFilmNazwa(HEAD, title1, 0); //wywoluje funkcje wyszukiwania ze statusem 0
            }
            break;
        case 4:
            system("CLS");
            Sortowanie(&HEAD); //wywoluje funkcje sortujaca w ktorej znajduje sie funkcja wyswietlajaca
            break;
        case 5:
            system("CLS");
            Edytuj(&HEAD); //wywoluje funkcje edycji
            break;
        case 6:
            system("CLS");
            zapisz_do_pliku(HEAD); //wywolanie funkcji zapisu
            break;
        case 7:
            system("CLS");
            odczyt_z_pliku(&HEAD); //wywolanie funkcji odczytu
            break;
        case 8:
            system("CLS");
            cout << "Program zamyka sie";
            system("EXIT"); //program zamyka sie po prostu
            break;
        default: //jakbys cos zepsul wraca do menu
            system("CLS");
            menu();

        }

    }
}


void Dodaj_Film(Film **HEAD)
{
    Film *nowy = new Film; //wywolanie konstruktora ktory tworzy nowy element
    Film *tmp = (*HEAD); //przypisanie glowy do naszego pomocnika

	if((*HEAD) == NULL) // nowy element bedzie głową listy jeli nasz poczatek jest pusty
	{
		*HEAD = nowy;
	}
	else // jeśli mamy głowę dodajemy film na koncu listy
	{
        tmp = *HEAD;
		while (tmp->PNext != NULL) // przechodzimy na koniec listy
			tmp = tmp->PNext; //krok do następnego elementu
		tmp->PPrev = tmp; //ustawiamy obecnt element na poprzedni
		tmp->PNext = nowy;//Nastepny element bedzie nowym obiektem i koncem listy

	}


    menu(); //wraca do menu


}


void WyswietlFilmy(Film *HEAD)
{


	Film *tmp; //nasz pomocnik
    tmp = HEAD; //nasz pomocnik jest poczatkiem
	if(tmp == NULL) //jesli pomocnik jest pusty to nasza lista tez jest pusta
	{
	    cout << "Baza jest pusta" << endl;
	}
    else
    {


	cout << "Twoja baza filmow" << endl;
	while(tmp != NULL)
	{
		tmp->wyswietl(); // wypisanie filmów
		cout << endl;
		tmp = tmp->PNext; // przejscie na kolejny element
	}
    }
    system("PAUSE");
    menu(); // wracamy do menu

}

void WyswietlFilmyRezysera(Film *HEAD, string directro)
{
    Film *tmp; //pomocnik
    tmp = HEAD; //pomocnik jest poczatkiem
	if(tmp == NULL) // jesli pusty
	{
	    cout << "Baza filmow jest pusta" << endl;
	}
    else
    {


	cout << "Filmy rezysera: " << directro << endl;
	while(tmp != NULL)
	{
		if(tmp->director_surname.compare(directro) == 0) // wypisujemy tylko wtedy kiedy pomocnik ma takigo samego rezysera jak  podany sprawdza tylko nazwiskiem
        {
            tmp->wyswietl(); // wypisanie filmów
            cout << endl;
        }
		tmp = tmp->PNext; // przejscie na kolejny element
	}

    }
    system("PAUSE");
    menu();
}

void WyswietlFilmyStudia(Film *HEAD, string studio_name) //ta sama analogia jak wyzej
{
    Film *tmp;
    tmp = HEAD;
	if(tmp == NULL)
	{
	    cout << "Baza filmow jest pusta" << endl;
	}
    else
    {


	cout << "Filmy studia: " << studio_name << endl;
	while(tmp != NULL);
	{
		if(tmp->studio.compare(studio_name) == 0)
        {
            tmp->wyswietl(); // wypisanie filmów
            cout << endl;
        }

		tmp = tmp->PNext; // przejscie na kolejny element
	}

    }
    system("PAUSE");
    menu();
}

void WyswietlFilmyRok(Film *HEAD, int prodyear) // to samo co wyzej
{
    Film *tmp;
    tmp = HEAD;
	if(tmp == NULL)
	{
	    cout << "Baza filmow jest pusta" << endl;
	}
    else
    {


	cout << "Filmy wyprudokowane w roku: " << prodyear << endl;
	while(tmp != NULL)
	{
	    if(tmp->date.year == prodyear)
        {
            tmp->wyswietl(); // wypisanie filmów
            cout << endl;
        }

		tmp = tmp->PNext; // przejscie na kolejny element
	}

    }
    system("PAUSE");
    menu();
}

Film *WyszukajFilmNazwa(Film *HEAD, string titlel, int status)
{
    Film *tmp; //pomocniczy wskaźnik

	tmp = HEAD; //pomocnik to poczatek
	while (tmp != NULL && (tmp->title).compare(titlel) != 0) // Pętla działa dopóki lista jest pełna, i szukany tytul zgadza sie z ktoryms z bazy
		tmp = tmp->PNext; //przechodzimy poki nie znajdziemy

    if (tmp == NULL)
    {
    cout << "Nie ma takiego filmu"; //po prostu nie ma filmu jak nie znajdzie
    system("PAUSE");
    menu();
    }

    if(status == 0)// jesli status jest zero to wypisuje nam wszystkie rzeczy o filmie jestli status jest inny zwraca nam tmp ktore bedzie potrzebne do usuwania i edycji
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

Film *WyszukajFilmID(Film *HEAD, int IDl, int status) // ta sama analogia co wyzej
{
  Film *tmp; //pomocniczy wskaźnik

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
    Film *tmp, *tmp1; // nasi pomocjnicy tmp - pomocnik 1 tmp1 - pomocnik 2
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
        tmp = WyszukajFilmID(*HEAD, IDl, 1); // wyszukujemy film z statusem 1 i on bedzie naszym pomocnikiem
        if (tmp == NULL)
        cout << "Nie ma takiego filmu"; // jesli nie ma filmu nie ma co usuwac
        else
        {
            if (tmp == *HEAD) // jesli usuwany jest poczatkiem musmy przeniesc poczatek na nastepny element
            {
                if(tmp->PNext == NULL) // jestli jest tylko ten jeden usuwamy go i ustawiamy glowe na pusta
                {
                    delete tmp;
                    cout << endl << "Film usniety" << endl;
                    *HEAD = NULL;
                    menu();
                }
                else
                {
                *HEAD = (*HEAD)->PNext; // przenosimy glowe na nastepny element wszyscy sie cieszymy bo nic nam nie ucieka
                delete tmp; //usuwamy film ktory jest pod pomocnikiem
                cout << endl << "Film usniety" << endl;
                menu();
                }
            }
            else
            {
                tmp1 = *HEAD; // nasz drugi pomocnik staje sie poczzatkiem listy
                while ((tmp1->PNext->ID) != (tmp->ID)) // dopoki  id nastepnika pomocnika 2 nie zgadza sie z id pomocnika 1 robimy krok w przod pomocnikiem 2
                    tmp1 = tmp1->PNext;
                if (tmp->PNext != NULL) // jesli nasz nastepnik nie jest pusty
                    tmp1->PNext->PPrev = tmp->PPrev; //poprzednika pomocnika 1 ustawiamy jako poprzednika nastepnika pomocnika 2
                tmp1->PNext = tmp->PNext; //nastepnik pomocnika 2 = nastepnik pomoncnika 1
                delete tmp; //usuwamy film
                cout << endl << "Film usniety" << endl;
                system("PAUSE");
                menu();
            }
        }
    }
    else if(opcja == 2) // ta sama analogia co wyzej tylko dla wyszukiwaniu po tytule
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


void Edytuj(Film **HEAD) // edycja filmu
{
    Film *tmp; //to jest nasz pomocnik
    int opcja; // to jest nasza opcja czy lecimy po ID czy po tytule
    string nazwa; // to jest nazwa naszego filmu
    string line; //to jest zmienna ktora bedzie przechowywac nasze zmiany
    int data; //to rowniez jest zmienna ktora przechowuje nasze zmiany ale ma typ int
    int IDl; // to nasze id po ktorym wyszukujemy
    cout << "Po czym chcesz wyszukac film ktory ma byc edytowany?";
    cout << endl << "1.ID" << endl << "2.Tytul" << endl;
    cin >> opcja;
    if(opcja == 1) //wiadomo o co chodzi znowu wyszukujemy ze statusem 1
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
        cout << "Podaj tytul filmu ktory ma byc edytowany" << endl;
        cin >> nazwa;
        tmp = WyszukajFilmNazwa(*HEAD, nazwa, 1);
        if (tmp == NULL)
        {
            cout << "Nie ma takiego filmu";
            system("PAUSE");
            menu();
        }

    }
    cin.clear();//clearujemy nasz wczesniejszy input zeby nie bylo bledow
    cout << "Edytujesz film o ID: [" <<tmp->ID << "] " << "o tytule: [" << tmp->title << "]:" << endl;
    cout << "Nowy tytul(wcisnij enter by pozostal bez zmian)[" << tmp->title <<"]: ";
    cin.ignore();
    getline(cin, line);
    if(!line.empty()) //jesli wpisalismy cos to nasz tytul sie zmienia jesli nie lecimy dalej i tak samo dzieje sie z resztą
        tmp->title = line;
    cout << endl << "Nowy Tytul: " << tmp->title << endl;
    cout << "Data Produkcji(wcisnij enter by pozostal bez zmian)[" << tmp->date.day << "/" << tmp->date.month << "/" << tmp->date.year <<"]: "<< endl;
    cout << "Podaj dzien produkcji :";
    cin.clear();
    while(1)
    {
         getline(cin, line);
        if(!line.empty())
        {
        data = atoi(line.c_str());
        if(data > 31 || data < 1)
        {
            cout << "Podales zly dzien - podaj ponownie: " << endl;
        }
        else
        {
            tmp->date.day = data;
            break;
        }

        }
        else
            break;
    }


    cout << endl << "Podaj miesiac produkcji: ";
    while(1)
    {
        getline(cin, line);
    if(!line.empty())
    {
        data = atoi(line.c_str());
        if(data > 12 || data < 1)
        {
            cout << "Podales zly miesiac - podaj ponownie: " << endl;
        }
        else
        {
            tmp->date.month = data;
            break;
        }

    }
    else
        break;
    }

    cout << endl << "Podaj rok produkcji: ";
     while(1)
    {
        getline(cin, line);
    if(!line.empty())
    {
        data = atoi(line.c_str());
        if(data < 1900)
        {
            cout << "Podales zly rok - podaj ponownie: " << endl;
        }
        else
        {
            tmp->date.year = data;
            break;
        }

    }
    else
        break;
    }
    cout << endl << "Data: " << tmp->date.day << "/" << tmp->date.month << "/" << tmp->date.year << endl;
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
    cout << "Nowa nazwa studia(wcisnij enter by pozostal bez zmian)[" << tmp->studio <<"]: ";
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
    cout << endl << "Zmieniony opis: " << tmp->other << endl;


    system("PAUSE");
    menu();
}


void Sortowanie(Film **HEAD) //sortowanie
{
    Film *nowa= NULL, *tmp, *tmp1, *pom; //nowa lista ktora bedzie posortowana, pomocnik i dwie listy tymczasowe

    while(*HEAD != NULL) //jesli nasza glowa nie jest pusta
    {
        tmp = *HEAD; //lista tymczasowa staje sie poczatkiem
        tmp1 = tmp->PNext; //druga lista poczatkowa wskazuje na nastepnika naszej glowy ZAWSZE
        tmp->PNext = NULL; //nastepny jest pusty
        tmp->PPrev = NULL; // poprzedni tymczasowej tez jest pusty

        if(nowa == NULL) // jesli nasza lista nowa jest pusta nasza nowa lista przyjmuje wartosc naszej listy tymczasowej
        {
           nowa = tmp;
           nowa->PNext = NULL; // nastepny element jest pusty
        }
        else if(nowa->title > tmp->title) //jesli nie jest pusta to porownujemy tytul nowej z tytulem ktory znajduje sie pod tymczasowa
        {
            tmp->PNext = nowa; //jesli w nowej liscie pierwszy tytul alfabetycznie jest wiekszy od tymczasowego to nastepnik tymczasowego staje sie tym co znajduje sie pod nowa
            nowa->PPrev = tmp; //poprzednik nowej przyjmuje wartosc listy tymczasowej
            nowa = tmp;
        }
        else
        {
            pom = nowa; // dorzucamy pomocnicza liste ktora jest taka sama jak posrtowana
        while(pom->PNext != NULL && pom->PNext->title < tmp->title) //wykonujemy petle dopoki nie wyjdziemy poza liste i nie znajdziemy tytulu ktory jest mniejszy od naszej pomocniczej
            pom = pom->PNext; // wykonujemy krok
        tmp->PPrev = pom; //zamiana miejscami pomocniczej i tymczasowej
        tmp->PNext = pom->PNext;
        if(pom->PNext != NULL)//jesli byl to ostatni element teraz ostatnim elementem staje sie tymczasowa
            pom->PNext->PPrev = tmp;
        pom->PNext = tmp;

        }
        *HEAD = tmp1;//na glowe ustawiamy nastepny element starej listy

       }
        *HEAD = nowa; //nowa lista staje sie glowa

        int opcja = 0;
        while(opcja > 4 || opcja < 1) // zaleznie od opcji wyswietla filmy
        {
            cout << "1.Wyswietl wszystkie filmy." << endl << "2.Wyswietl wszystkie filmy rezysera." << endl << "3.Wyswietl wszystkie filmy studia" << endl << "4.Wyswietl wszystkie filmy wyprudokowane w roku." << endl;
            cin >> opcja;

            if(opcja > 4  || opcja < 1)
                cout << "Podales zly numer, podaj ponownie";
            system("CLS");
        }
        if(opcja == 1)
         WyswietlFilmy(*HEAD);
        if(opcja == 2)
        {
            cout << "Podaj nazwisko rezysera" << endl;
            string rezyser;
            cin >> rezyser;
            WyswietlFilmyRezysera(*HEAD, rezyser);

        }
        if(opcja == 3)
        {
            cout << "Podaj nazwe studia" << endl;
            string nazwa_studia;
            cin >> nazwa_studia;
            WyswietlFilmyStudia(*HEAD, nazwa_studia);

        }
        if(opcja == 4)
        {
            cout << "Podaj rok produkcji" << endl;
            int year;
            cin >> year;
            WyswietlFilmyRok(*HEAD, year);
        }

    }


void zapisz_do_pliku(Film *HEAD)
{
	Film *tmp; // pomocnik
	string nazwa_pliku; // nasz plik
	cout << "Podaj nazwe pliku: ";
	cin >> nazwa_pliku; // podajemy nazwe pliku
    nazwa_pliku += ".txt";//do naszej nazwy dodwane jest rozszerzenie
    fstream fout; //outpu file czyli odpalamy fstreama w trybie zapisu


	if(fstream(nazwa_pliku.c_str())) //jesli nasz plik juz istnieje
    {

        cout << "Plik istnieje, czy chcesz nadpisac?" << endl;
        cout << "1.TAK\t2.NIE" << endl;
        int opcja;
        cin >> opcja;
        while(opcja < 1 && opcja > 2)
        {
            cout << "Podales zla opcje, podaj ponownie";
            system("PAUSE");
            system("CLS");
            cin >> opcja;
        }
        if(opcja == 1)
        {
            	fout.open(nazwa_pliku.c_str() );
                tmp = HEAD;
            while(tmp != NULL) //spisujemy kolejne elementy listy oddzielamy jest srednikami tak jak w bazach danych
            {
                fout << tmp->ID << ";";
                fout << tmp->title << ";";
                fout << tmp->date.day << ";" << tmp->date.month << ";" << tmp->date.year << ";";
                fout << tmp->director_name << ";";
                fout << tmp->director_surname << ";";
                fout << tmp->studio << ";";
                fout << tmp->genre << ";";
                fout << tmp->other << ";" << endl;

                tmp = tmp->PNext;
            }

            fout.close();
            cout << "Lista zapisana" << endl ;
            system("PAUSE");
            menu();
        }
        else
        {
            cout << "Plik nie został zapisany";
            system("PAUSE");
            fout.close();
            menu();
        }
    }
    else
    {
        fout.open(nazwa_pliku.c_str() );
                tmp = HEAD;
            while(tmp != NULL) //spisujemy kolejne elementy listy oddzielamy jest srednikami tak jak w bazach danych
            {
                fout << tmp->ID << ";";
                fout << tmp->title << ";";
                fout << tmp->date.day << ";" << tmp->date.month << ";" << tmp->date.year << ";";
                fout << tmp->director_name << ";";
                fout << tmp->director_surname << ";";
                fout << tmp->studio << ";";
                fout << tmp->genre << ";";
                fout << tmp->other << ";" << endl;

                tmp = tmp->PNext;
            }

            fout.close();
            cout << "Lista zapisana" << endl ;
            system("PAUSE");
            menu();
    }

}

void odczyt_z_pliku(Film **HEAD)
{


    Film *tmp1 = (*HEAD); //pomocnik ktory beidze przechowywal stara liste
    string nazwa_pliku; // nazwa pliku ktory ma byc wczytany
    cout << "Podaj sciezke pliku: ";
    cin >> nazwa_pliku; //musimy podac pelna sciezke pliku
    ifstream fd; //fstream w trybie odczytu z pliku
    string row; //nasz rzad
    fd.open(nazwa_pliku.c_str());//otwieramy plik
    if(fd)
    {


        while(getline(fd, row)) //dopoki nie dojdzie do konca pliku
        {

            //getline(fd, row);//zbiera nasza linie i zapisuje ja do zmiennej row
            Film *tmp = new Film(row); //wywolujemy konstruktro film z argumentem ktroy tworzy nowy element listy według naszego rzedu



            if(*HEAD == NULL)//ta sama zasada jak przy dodawaniu nowego filmu
                *HEAD = tmp;
            else
            {
                tmp1 = *HEAD;
            while (tmp1->PNext != NULL) // przechodzimy na koniec listy
                tmp1 = tmp1->PNext; //krok do następnego elementu
            tmp1->PPrev = tmp1; //ustawiamy obecnt element na poprzedni
            tmp1->PNext = tmp;//Nastepny element bedzie nowym obiektem i koncem listy
            }
        }
        fd.close();
    }
    else
    {
        cout << "Blad: Nie mozna otworzyc pliku :(";
        fd.close();

    }

    system("PAUSE");
    menu();




}
