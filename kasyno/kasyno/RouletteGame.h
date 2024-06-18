#pragma once
#include "player.h"
#include "RouletteWheel.h"
#include <iostream>
using namespace std;

class RouletteGame
{
	RouletteWheel wheel;
	Player player;
	int buyMore;
public:
	RouletteGame(int initialChips);
	void play();			// funkcja odpowiadajaca za gre
	int getPlayerChips();	// funkcja pobierajaca zetony gracza
	void addChips();
};

int payout(int type, int chips, int number, int result);
