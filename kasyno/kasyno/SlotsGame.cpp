#include "SlotsGame.h"

mt19937 generator(time(nullptr));
uniform_int_distribution<> distribution(0, 5);

SlotsGame::SlotsGame(int initialChips) : player(initialChips), bet(0)
{	//zdefiniowanie nazw symboli
	symbols[0] = "7";
	symbols[1] = "Wisnia";
	symbols[2] = "Jackpot";
	symbols[3] = "Pomarancza";
	symbols[4] = "Diament";
	symbols[5] = "Serduszko";
}

void SlotsGame::gameOn()				//rozgrywka
{
	while (player.getStillPlaying())
	{
		placeBet();

		spinRolls();
		displayRolls();
		checkWin();
		addChips();
		try
		{
			askContinue();
		}
		catch (const invalid_argument& e)
		{
			cout << e.what() << endl;
			askContinue();
		}
	}
}

void SlotsGame::placeBet()
{
	cout << "Masz " << player.getChips() << " zetonow. Ile obstawiasz?";
	cin >> bet;
	try {			//sprawdzanie czy gracz dobrze obstawil
		player.placeBet(bet);
	}
	catch (const invalid_argument& e)
	{
		cout << e.what() << endl;
		placeBet();
	}
}

void SlotsGame::addChips()
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

void SlotsGame::spinRolls()					//losowanie symboli na rolkach
{
	for (int i = 0; i < sizeof(rolls) / sizeof(rolls[0]); i++)
	{
		int randIdx = distribution(generator);
		rolls[i] = symbols[randIdx];
	}
}

void SlotsGame::displayRolls()				// wyswietlanie rolek
{
	for (int i = 0; i < sizeof(rolls) / sizeof(rolls[0]); i++)
	{
		cout << "[ " << rolls[i] << " ]";
	}
	cout << endl;
}

void SlotsGame::checkWin()			//sprawdzanie wygranej
{
	if (rolls[0] == rolls[1] && rolls[1] == rolls[2] && rolls[0] == "Jackpot")
	{
		cout << "Jackpot!, wygrales " << bet * 10 << " zetonow" << endl;
		player.win(bet * 10);
	}
	else if ((rolls[0] == rolls[1] && rolls[0] == "Jackpot") 
		|| (rolls[1] == rolls[2] && rolls[1] == "Jackpot")
		|| (rolls[0] == rolls[2] && rolls[2] == "Jackpot"))
	{
		cout << "2 z 3, prawie jackpot, wygrales " << bet * 5 << " zetonow" << endl;
		player.win(bet * 5);
	}
	else if (rolls[0] == rolls[1] && rolls[1] == rolls[2] && rolls[0] == "7")
	{
		cout << "Siodemki, wygrales " << bet * 7 << " zetonow" << endl;
		player.win(bet * 7);
	}
	else if ((rolls[0] == rolls[1] && rolls[0] == "7")
		|| (rolls[1] == rolls[2] && rolls[1] == "7")
		|| (rolls[0] == rolls[2] && rolls[2] == "7"))
	{
		cout << "2 z 3 siodemek, wygrales " << bet * 4 << " zetonow" << endl;
		player.win(bet * 4);
	}
	else if (rolls[0] == rolls[1] && rolls[1] == rolls[2] && rolls[0] == "Diament")
	{
		cout << "Diamenty, wygrales " << bet * 5 << " zetonow" << endl;
		player.win(bet * 5);
	}
	else if ((rolls[0] == rolls[1] && rolls[0] == "Diament")
		|| (rolls[1] == rolls[2] && rolls[1] == "Diament")
		|| (rolls[0] == rolls[2] && rolls[2] == "Diament"))
	{
		cout << "2 z 3 diamentow, wygrales " << bet * 3 << " zetonow" << endl;
		player.win(bet * 3);
	}
	else if (rolls[0] == rolls[1] && rolls[1] == rolls[2])
	{
		cout << "3 z jednego rodzaju, wygrales " << bet * 3 << " zetonow" << endl;
		player.win(bet * 3);
	}
	else if (rolls[0] == rolls[1] || rolls[1] == rolls[2] || rolls[0] == rolls[2])
	{
		cout << "2 z 3, wygrales " << bet * 2 << " zetonow" << endl;
		player.win(bet * 2);
	}
	else
	{
		cout << "Przegrales" << endl;
	}
}

void SlotsGame::askContinue()
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

int SlotsGame::getPlayerChips() const
{
	return player.getChips();
}