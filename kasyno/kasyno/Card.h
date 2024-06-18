#pragma once
#include <iostream>
using namespace std;

class Card
{
public:
	char figure;	//okresla figure karty
	int value;		//wartosc danej karty

	Card(char fig = '0', int val = 0);

	void display();	//wyswietlanie karty
};