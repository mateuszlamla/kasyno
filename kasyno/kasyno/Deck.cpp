#include "Deck.h"

//generowanie liczb losowych
mt19937 generatorBlackjack(time(nullptr));
uniform_int_distribution<> distributionBlackjack(0, 51);


Deck::Deck() : currentCardIndex(0)
{
	cards = new Card[deckSize];		//tablica talii
	initialize();
	shuffle();
}

Deck::~Deck()
{
	delete[] cards;
}

void Deck::initialize()
{
	const char figures[] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
	int index = 0;
	for (char fig : figures)		//nadawanie figurom wartosci
	{
		int val;
		if (fig == 'A')
		{
			val = 11;
		}
		else if (fig >= '2' && fig <= '9')
		{
			val = fig - '0';
		}
		else
		{
			val = 10;
		}

		for (int i = 0; i < 4; i++)	//dodawanie kart do talii
		{
			cards[index++] = Card(fig, val);
		}
	}
}

void Deck::shuffle()				//tasowanie kart w talii
{
	for (int i = 0; i < deckSize; ++i)
	{
		int j = distributionBlackjack(generatorBlackjack);
		swap(cards[i], cards[j]);
	}
	currentCardIndex = 0;
}

Card Deck::draw()					//wybranie jednej kart z talii
{
	if (currentCardIndex >= deckSize)
	{
		shuffle();
		currentCardIndex = 0;
	}
	return cards[currentCardIndex++];
}