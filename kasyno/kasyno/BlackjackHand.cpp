#include "BlackjackHand.h"

BlackjackHand::BlackjackHand() : cardCount(0), sum(0)
{
	cards = new Card[21];		//tworzenie tablicy kart na rece
};

BlackjackHand::~BlackjackHand()
{
	delete[] cards;
}

void BlackjackHand::addCard(const Card& card)
{
	cards[cardCount] = card;
	cardCount++;
	sum += card.value;
	if (sum > 21)				//sprawdzanie czy sa jakies asy jesli tak to zmiana wartosci asa z 11 na 1
	{
		for (int i = 0; i < cardCount; ++i)
		{
			if (cards[i].figure == 'A' && cards[i].value == 11)
			{
				cards[i].value = 1;
				sum -= 10;
				break;
			}
		}
	}
}

int BlackjackHand::getSum() const		//pobieranie sumy wartosci kart na rece
{
	return sum;
}

void BlackjackHand::display() const		//wyswietlanie kart na rece 
{
	for (int i = 0; i < cardCount; ++i)
	{
		cards[i].display();
	}
	cout << "| Suma: " << sum << endl;
}

int BlackjackHand::getCardCount() const	//pobieranie ilosci kart na rece
{
	return cardCount;
}

void BlackjackHand::clear()				//czyszczenie reki
{
	cardCount = 0;
	sum = 0;
}



