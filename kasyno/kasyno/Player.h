#pragma once
#include"BlackjackHand.h"

class Player
{
	BlackjackHand hand;	//definiuje reke gracza
	int chips;			//okresla ilosc zetonow posiadanych przez gracza
	bool stillPlaying;	//okresla czy gracz chce dalej grac

public:

	Player(int initial_chips);
	void placeBet(int bet);				//funkcja sluzaca do umieszczania zakladu
	void addCard(const Card& card);		//funkcja dodajaca karte dla gracza
	void displayHand() const;			//funkcja wyswietlajaca reke gracza
	int getSum() const;					//funkcja zwracajaca sume wartosci kart w rece gracza
	int getChips() const;				//funkcja zwracajaca ilosc zetonow gracza
	int getCardCount() const;			//funkcja zwracajaca ilosc kart w rece gracza
	void addChips(int amount);			//funkcja pozwalajaca na zakup zetonow
	void win(int amount);				//funckja okreslajaca wygrana gracza
	void setStillPlaying(bool value);	//funkcja ustwiajaca chec gracza do dalszej gry
	bool getStillPlaying() const;		//funkcja zwracajaca czy gracz chce dalej grac
	void resetHand();					//funkcja czyszczaca reke gracza
};


