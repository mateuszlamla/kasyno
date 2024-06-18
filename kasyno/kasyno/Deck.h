#pragma once
#include "Card.h"
#include <random>
#include <ctime>
using namespace std;

class Deck
{
	Card* cards;	//wskaznik potrzebny do utworzenia tablicy talii
	int currentCardIndex;	//okresla ile kart z talii zostalo uzytych
	static const int deckSize = 52;	//rozmiar talii

	void initialize();	//funkcja przypisujaca figurom wartosci

public:
	Deck();
	~Deck();
	void shuffle();		//funkcja tasujaca karty
	Card draw();		//funkcja wybierajaca jedna karte z talii
};