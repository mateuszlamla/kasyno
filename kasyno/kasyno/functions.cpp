#include "functions.h"

void start() {
	int chips{};
	string choice;
	cout << "=-=-=-=-=KASYNO=-=-=-=-=" << endl;
	do {
		cout << "\nMENU:" << endl;
		cout << "Masz " << chips << " zetonow" << endl;
		cout << "[1] Blackjack" << endl;
		cout << "[2] Ruletka" << endl;
		cout << "[3] Jednoreki bandyta" << endl;
		cout << "[4] Dodaj zetony" << endl;
		cout << "[5] Wyjscie" << endl;
		cin >> choice;
		if (choice.length() != 1)
		{
			cout << "Podaj poprawna liczbe" << endl;
		}
		else
		{
			if (choice[0] == '1' && chips > 0)
			{
				//obiekt blackjack
				cout << "\n**********BLACKJACK**********\n\n";
				BlackjackGame blackjack(chips);
				blackjack.gameOn();
				chips = blackjack.getPlayerChips();
			}
			else if (choice[0] == '2' && chips > 0)
			{
				//obiekt ruletka
				cout << "\n**********RULETKA**********\n\n";
				RouletteGame roulette(chips);
				roulette.play();
				chips = roulette.getPlayerChips();
			}
			else if (choice[0] == '3' && chips > 0)
			{
				//obiekt sloty
				cout << "\n**********JEDNOREKI BANDYTA**********\n\n";
				SlotsGame slots(chips);
				slots.gameOn();
				chips = slots.getPlayerChips();
			}
			else if (choice[0] == '4')
			{
				int buyMore;
				bool validAmount = false;
				cout << "\n**********ZAKUP ZETONOW**********\n\n";
				cout << "Ile zetonow chcesz zakupic?";
				cin >> buyMore;

				while (!validAmount)
				{
					try
					{
						if (buyMore <= 0 || !(validAmount = cin.good()))
						{
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							throw invalid_argument("Bledne dane.");
						}
						validAmount = true;
						chips += buyMore;
					}
					catch (const invalid_argument& e)
					{
						cout << e.what() << endl;
						cout << "Ile zetonow chcesz zakupic?";
						cin >> buyMore;
					}
				}
			}
			else if (choice[0] == '5')
			{
				//wyjscie
				cout << "\n**********DZIEKUJEMY ZA GRE**********\n\n";
			}
			else if ((choice[0] == '1' || choice[0] == '2' || choice[0] == '3') && chips == 0)
			{
				cout << "Musisz zakupic zetony" << endl;
			}
			else
			{
				cout << "Podaj poprawna liczbe" << endl;
			}
		}	
	} while (choice[0] != '5');
}