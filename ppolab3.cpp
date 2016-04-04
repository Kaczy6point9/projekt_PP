// molecue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>

using namespace std;
class Molecule
{
protected:
	char symbol;
public:
	virtual	string get_name() = 0;
	Molecule(char symobl1)
	{
		this->symbol = symobl1;
	}
};



class Nucleotide :public Molecule
{
public:
	string get_name();
	Nucleotide(char symbol1) :Molecule(symbol1)
	{
		
	}
};

string Nucleotide::get_name()
{
	
	if (this->symbol == 'a')
		return "adeina";
	else if (this->symbol == 'g')
		return "guanina";
	else if (this->symbol == 't')
		return "tymina";
	else if (this->symbol == 'c')
		return "cytozyna";
	else if (this->symbol == 'u')
		return "Uracyl";
	else
		return "Podales zly symbol";
}

class Aminoacid :public Molecule
{
public:
	string get_name();
	Aminoacid(char symbol1) :Molecule(symbol1)
	{
		Aminoacid::get_name();
	}
};

string Aminoacid::get_name()
{
	if (this->symbol == 'a')
		return "Alanina";
	else if (this->symbol == 'g')
		return "Glicyna";
	else if (this->symbol == 't')
		return "Treonina";
	else if (this->symbol == 'c')
		return "Cysteina";
	else if (this->symbol == 'f')
		return "Fenyloalanina";
	else
		cout << "Podales zly symbol";
}

list <Molecule *> lista;

int menu()
{
	
	int opcja;
	
	list <Molecule *> ::iterator it;
	string lel;
	
	system("CLS");
	cout << "Stworzyc 1.Nukleodyt czy 2.Aminokwas? 3.Wypisac liste" << endl;
	cin >> opcja;
	
	
	switch (opcja)
	{
	case 1:
	{
		char symbol;
		cout << "Podaj symbol" << endl;
		cin >> symbol;
		Nucleotide *n = new Nucleotide(symbol);
		lista.push_back(n);
	}
		
		menu();
		break;
	case 2:
	{
		char symbol;
		cout << "Podaj symbol" << endl;
		cin >> symbol;
		Aminoacid *a = new Aminoacid(symbol);
		lista.push_back(a);
	}
		
		menu();
		break;
	case 3:
		system("CLS");
		for (it = lista.begin(); it != lista.end(); ++it)
		{
			cout << "" << (*it)->get_name() << endl;
		}
		system("PAUSE");
		break;
	default:
		cout << "Podales zly numer";

		return 0;


	}
}

int _tmain(int argc, _TCHAR* argv[])
{

	
	menu();
		
	system("PUASE");
	return 0;
}

