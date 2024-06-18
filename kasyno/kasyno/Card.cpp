#include "Card.h"

Card::Card(char fig, int val) : figure(fig), value(val) {};

void Card::display()	//wyswietlanie karty
{
	cout << figure << " ";
}