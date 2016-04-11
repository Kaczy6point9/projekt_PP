// molecue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

template <typename T> 
class StackInFile
{

private:
	fstream f;
	int licznik=0;
public:
	
	void push(T strumien)
	{
		f.write((char*)&strumien, sizeof(T));
		licznik+=1;

	}
	T pop()
	{
		licznik -= 1;
		T pom;
		f.seekg(sizeof(T) * licznik);
		f.read((char*)&pom, sizeof(T));
		f.seekg(sizeof(T) * licznik);
		return pom;
	}

	StackInFile(string nazwapliku)
	{
		
		f.open(nazwapliku.c_str(), ios::in | ios::out | ios::binary|ios::trunc);
		
	}

	~StackInFile()
	{
		f.close();
	}
};



int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Podaj nazwe stosu" << endl;
	string nazwa;
	cin >> nazwa;
	StackInFile <int> stos(nazwa);
	stos.push(5);
	stos.push(6);
	stos.push(7);
	cout << stos.pop() << endl;
	cout << stos.pop() << endl;
	stos.push(10);
	cout << stos.pop() << endl;
	cout << stos.pop() << endl;
	system("PAUSE");
	return 0;
}


