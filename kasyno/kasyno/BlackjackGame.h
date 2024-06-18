#pragma once
#include "Deck.h"
#include "Player.h"
#include "BlackjackHand.h"

using namespace std;

class BlackjackGame
{
	Deck deck;			//definiuje talie kart
	Player player;		//definiuje gracza
	BlackjackHand dealerHand;	//definiuje reke krupiera
	int bet;			//okresla wielkosc zakladu
	bool doubleDown;

public:
	BlackjackGame(int initialChips);
	void gameOn();		//funkcja odpowiadajaca za toczenie sie rozgrywki
	void placeBet();	//funkcja odpowiadajaca za umieszcanie zakladu
	void addChips();	//funkcja dodajaca zetony do salda gracza
	void initialHand();	//funkcja rozdajaca dwie poczatkowe karty graczowi i krupierowi
	void playerTurn();	//funkcja odpowiadajaca za ture gracza
	void dealerTurn();	//funkcja odpowiadajaca za ture krupiera
	void checkWin();	//funckja sprawdzajaca wygrana i okreslajaca jej wielkosc
	void askContinue();	//funkcja pytajaca czy gracz chce grac dalej
	int getPlayerChips() const;	//funkcja pobierajaca ilosc zetonow gracza
};