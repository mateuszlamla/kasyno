#pragma once
#include "Card.h"
using namespace std;
class BlackjackHand
{
	Card* cards;	//wskaznik potrzebny do utworzenia tablicy reki gracza
	int cardCount;	//ilosc kart ktore gracz ma na rece
	int sum;		//suma wartosci kart na rece gracza

public:
	BlackjackHand();
	~BlackjackHand();
	void addCard(const Card& card);	//dodanie karty do reki
	int getSum() const;				//zwraca sume wartosci kart na rece
	void display() const;			//wyswietla karty na rece
	int getCardCount() const;		//zwraca ilosc kart na rece
	void clear();					//czysci reke
};

