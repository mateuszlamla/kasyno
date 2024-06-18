#include "BlackjackGame.h"

BlackjackGame::BlackjackGame(int initialChips) : player(initialChips), bet(0), doubleDown(0) {};

void BlackjackGame::gameOn()			//toczenie sie calej gry
{
	while (player.getStillPlaying())
	{
		placeBet();			//obstawianie
		initialHand();		//rozdanie kart przed gra
		if (player.getSum() != 21 && dealerHand.getSum() != 21)		//sprawdzenie blackjackow
		{
			playerTurn();		//tura gracza
			if (player.getSum() <= 21)	//sprawdzenie czy gracz nie przekroczyl progu 21
			{
				dealerTurn();	//tura dealera
			}
		}
		else if (player.getSum() == 21 && dealerHand.getSum() == 21)
		{
			cout << "Karty krupiera: ";
			dealerHand.display();
			cout << "Gracz i krupier maja blackjacka. ";
		}
		checkWin();				//sprawdzenie kto wygral
		addChips();
		try
		{
			askContinue();
		}
		catch (const invalid_argument& e)	//sprawdzenie czy gracz chce grac dalej
		{
			cout << e.what() << endl;
			askContinue();
		}

		player.resetHand();		//czyszczenie reki gracza
		dealerHand.clear();		//czyszczenie reki krupiera
	}
}

void BlackjackGame::placeBet()
{
	cout << "Masz " << player.getChips() << " zetonow. Ile obstawiasz?";
	cin >> bet;
	try 
	{			//sprawdzanie czy gracz dobrze obstawil
		player.placeBet(bet);
	}
	catch (const invalid_argument& e)
	{
		cout << e.what() << endl;
		placeBet();
	}
}

void BlackjackGame::initialHand()
{										//rozdanie dwoch poczatkowych kart
	player.addCard(deck.draw());
	dealerHand.addCard(deck.draw());
	player.addCard(deck.draw());

	cout << "Karta krupiera: ";
	dealerHand.display();
	player.displayHand();
	dealerHand.addCard(deck.draw());

	if (dealerHand.getSum() == 21 && player.getSum() != 21)		//sprawdzanie czy dealer ma blackjacka
	{
		cout << "Karty krupiera: ";
		dealerHand.display();
		cout << "Dealer ma blackjacka. ";
	}
}

void BlackjackGame::playerTurn()
{
	while (player.getSum() <= 21)
	{
		string choice;

		if (player.getCardCount() == 2 && player.getChips() >= bet)
		{
			cout << "Stand [1], Hit[2], Double Down[3]: ";
		}
		else
		{
			cout << "Stand [1], Hit[2]: ";
		}

		cin >> choice;
		if (choice.length() == 1)
		{
			if (choice[0] == '1')
			{
				break;
			}
			else if (choice[0] == '2' && player.getSum() != 21)
			{
				player.addCard(deck.draw());
				player.displayHand();
			}
			else if (choice[0] == '3' && player.getCardCount() == 2 && player.getChips() >= bet)
			{
				player.placeBet(bet);
				player.addCard(deck.draw());
				player.displayHand();
				doubleDown = true;
				break;
			}
			else
			{
				cout << "Zly wybor" << endl;
			}
		}
		else
		{
			cout << "Zly wybor" << endl;
		}
		
	}
}

void BlackjackGame::dealerTurn()
{
	while (dealerHand.getSum() < 17)
	{
		dealerHand.addCard(deck.draw());
	}
	cout << "Karty krupiera: ";
	dealerHand.display();
}

void BlackjackGame::checkWin()
{
	int playerSum = player.getSum();
	int dealerSum = dealerHand.getSum();

	if (dealerSum != 21 && playerSum == 21 && player.getCardCount() == 2)		//blackjack
	{
		cout << "Blackjack!, wygrales " << ceil(bet * 2.5) - bet << " zetonow" << endl;
		player.win(ceil(bet * 2.5));
	}
	else if (((playerSum == dealerSum) && playerSum <= 21) && doubleDown)						//remis
	{
		cout << "Remis" << endl;
		player.win(bet * 2);
	}
	else if (((playerSum == dealerSum) && playerSum <= 21) && !doubleDown)						//remis
	{
		cout << "Remis" << endl;
		player.win(bet);
	}
	else if (((playerSum > dealerSum && playerSum <= 21) || (playerSum <= 21 && dealerSum > 21)) && doubleDown)		//win
	{
		cout << "Wygrales po Double Down " << bet * 2 << " zetonow" << endl;
		player.win(bet * 4);
	}
	else if (((playerSum > dealerSum && playerSum <= 21) || (playerSum <= 21 && dealerSum > 21)) && !doubleDown)	//win
	{
		cout << "Wygrales " << bet << " zetonow" << endl;
		player.win(bet * 2);
	}
	else if ((playerSum > 21 || (dealerSum <= 21 && dealerSum > playerSum)) && doubleDown)
	{
		cout << "Przegrales " << bet * 2 << " zetonow" << endl;
	}
	else if ((playerSum > 21 || (dealerSum <= 21 && dealerSum > playerSum)) && !doubleDown)		//przegrana
	{
		cout << "Przegrales " << bet << " zetonow" << endl;
	}
	doubleDown = false;
}

void BlackjackGame::addChips()
{
	if (player.getChips() <= 0)
	{
		cout << "Masz " << player.getChips() << " zetonow. Ile chcesz dokupic?";
		cin >> bet;
		try
		{
			player.addChips(bet);
		}
		catch (const invalid_argument& e)
		{
			cout << e.what() << endl;
			addChips();
		}
	}
}

void BlackjackGame::askContinue()
{
	string choice;
	bool valid = false;
	while (!valid)
	{
		cout << "Masz " << player.getChips() << " zetonow. Chcesz grac dalej [Tak-1, Nie-0]";
		cin >> choice;
		try
		{
			if ((choice[0] != '0' && choice[0] != '1') || choice.length() != 1)
			{
				throw invalid_argument("Zly wybor.");
			}	
			valid = true;
			player.setStillPlaying(choice[0] == '1');
		}
		catch (const invalid_argument& e)
		{
			cout << e.what() << endl;
		}
	}
}

int BlackjackGame::getPlayerChips() const
{
	return player.getChips();
}