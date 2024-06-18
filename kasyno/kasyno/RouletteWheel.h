#pragma once
#include <iostream>
#include <random>
using namespace std;
class RouletteWheel
{
	int* numbers; //tablica zawierajaca liczby na polach ruletki
	const char** colors; //tablica zawierajaca kolory dla okreslonych liczb na polach ruletki
public:
	RouletteWheel(); //konstruktor kola ruletki
	int spin(); //metoda zwracajaca losowa liczbe z zakresu ilosci pol
	const char* wheelResult(int number); //metoda zwracajaca kolor do wylosowanej liczby
};
