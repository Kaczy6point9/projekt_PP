// molecue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <map>

using namespace std;

map < string, int > wyrazy;

int _tmain(int argc, _TCHAR* argv[])
{
	map<string, int >::iterator it;
	it = wyrazy.begin();
	/*ifstream plik;
	string nazwaPliku;
	plik.open(nazwaPliku.c_str());
	if (!plik.good())
		return false;
		*/
	string linia;
	int n = 0;
	while (n<10)
	{
		cin >> linia;
		wyrazy[linia]++;
		n++;
	}

	for (it = wyrazy.begin(); it != wyrazy.end(); it++)
	{
		cout << it->first << ": " << it->second << endl;
	}
	
	system("PAUSE");
	return 0;
}

