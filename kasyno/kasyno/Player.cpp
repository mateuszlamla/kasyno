#include "Player.h"

Player::Player(int initial_chips) : chips(initial_chips), stillPlaying(true) {};

void Player::placeBet(int bet)				//umieszczenie zakladu
{
	bool validAmount = false;
	if ((bet <= 0 || bet > chips) || !(validAmount = cin.good()))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		throw invalid_argument("Nieprawidlowy zaklad.");
	}
	validAmount = true;
	chips -= bet;
}

void Player::addCard(const Card& card)		//dodawanie karty do reki gracza
{
	hand.addCard(card);
}

void Player::displayHand() const			//wyswietlanie kart na rece gracza
{
	cout << "Twoje karty: ";
	hand.display();
}

int Player::getSum() const					//pobieranie sumy wartosci kart gracza
{
	return hand.getSum();
}

int Player::getChips() const				//pobieranie ilosci zetonow gracza
{
	return chips;
}

int Player::getCardCount() const			//pobieranie ilosci kart na rece gracza
{
	return hand.getCardCount();
}

void Player::addChips(int amount)			//dodawanie zetonow do salda
{
	bool validAmount = false;
	if ((amount <= 0) || !(validAmount = cin.good()))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		throw invalid_argument("Nieprawidlowa liczba.");
	}
	validAmount = true;
	chips += amount;
}

void Player::win(int amount)				//dodawanie zetonow za wygrana
{
	chips += amount;
}

void Player::setStillPlaying(bool value)	//ustawienie checi gracza do dalszej gry
{
	stillPlaying = value;
}

bool Player::getStillPlaying() const		//sprawdzenie checi gracza do dalszej gry
{
	return stillPlaying;
}

void Player::resetHand()					//czyszczenie reki gracza
{
	hand.clear();
}