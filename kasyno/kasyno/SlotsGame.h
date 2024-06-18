#pragma once
#include <iostream>
#include <random>
#include "Player.h"
using namespace std;

class SlotsGame
{
	string symbols[6];	//symbole wyswietlane na rolkach
	string rolls[3];	//rolki
	Player player;		//gracz
	int bet;			//zaklad
	int buyMore;

public:
	SlotsGame(int initialChips);
	void gameOn();				// funkcja odpowiadajaca za rozgrywke
	void placeBet();			// funkcja odpowiadajaca za umieszczenie zakladu
	void addChips();
	int getPlayerChips() const;	// funkcja pobierajaca ilosc zetonow gracz

private:
	void spinRolls();			// funkcja losujaca symbole na kazdej z rolek
	void displayRolls();		// funkcja wyswietlajaca rolki
	void checkWin();			// funkcja sprawdzajaca wygrana
	void askContinue();			// funkcja sprawdzajaca chec do dalszej gry
	
};
