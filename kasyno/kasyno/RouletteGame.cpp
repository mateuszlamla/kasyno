#include "RouletteGame.h"

RouletteGame::RouletteGame(int initialChips) :player(initialChips), buyMore(0) {}

int RouletteGame::getPlayerChips() { // funkcja przekazujaca zetony do glownej funkcji
	return player.getChips();
}

int payout(string type, int chips, int number, int result) { // funkcja sprawdzajaca czy uzytkownik wygral
	if (type[0] == '1') { // wygrana po postawieniu na liczbe
		if (number == result) {
			return 1;
		}
	}
	else if (type[0] == '2') { // wygrana po obstawieniu koloru
		if ((result % 2 == 0 && number % 2 == 0 && result != 0 && number != 0) || (result % 2 == 1 && number % 2 == 1) || (number == 0 && result == 0)) {
			return 1;
		}
	}
	return 0;
}

void RouletteGame::addChips()
{
	if (player.getChips() <= 0)
	{
		cout << "Masz " << player.getChips() << " zetonow. Ile chcesz dokupic?";
		cin >> buyMore;
		try
		{
			player.addChips(buyMore);
		}
		catch (const invalid_argument& e)
		{
			cout << e.what() << endl;
			addChips();
		}
	}
}


void RouletteGame::play() { // funkcja gry
	cout << "Aktualne saldo zetonow: " << player.getChips() << endl;
	string yesno; // zmienna czy uzytkownik chce grac dalej
	string type; // obstawiony przez uzytkownika typ zakladu oraz wartosc zakladu
	int bet;
	int number;
	do {

		bool validType = false;
		bool validNumber = false;
		bool validChips = false;
		bool valid = false;
		bool validAmount = false;
		while (!validType) { // petla sprawdzajaca poprawnosc podania typu zakladu
			cout << "\nPodaj typ zakladu (liczba - 1, kolor - 2): ";
			cin >> type;
			try {
				if ((type[0] != '1' && type[0] != '2') || type.length() != 1) {
					throw invalid_argument("Podana liczba jest spoza zakresu");
				}
				validType = true;
			}
			catch (const invalid_argument& e) {
				cout << e.what() << endl;
			}
		}
		while (!validNumber) { // petla sprawdzajaca poprawnosc podania koloru/liczby obstawianej
			if (type[0] == '1') {
				cout << "Podaj liczbe, jaka chcesz obstawic (0-36): ";
			}
			else {
				cout << "Podaj kolor, jaki chcesz obstawic (1 - czerwony, 2 - czarny): ";
			}
			cin >> number;
			try {
				if (type[0] == '1' && ((number < 0 || number>36) || !(validAmount = cin.good()))) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					throw invalid_argument("Podana liczba jest spoza zakresu");
				}
				else if (type[0] == '2' && ((number < 1 || number>2) || !(validAmount = cin.good()))) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					throw invalid_argument("Podana liczba jest spoza zakresu");
				}
				validNumber = true;
				validAmount = true;
			}
			catch (const invalid_argument& e) {
				cout << e.what() << endl;
			}
		};
		while (!validChips) {// petla sprawdzajaca poprawnosc podania ilosci zetonow zakladu
			cout << "Masz " << player.getChips() << " zetonow. Ile obstawiasz?";
			cin >> bet;
			try {
				player.placeBet(bet);
				validChips = true;
			}
			catch (const invalid_argument& e)
			{
				cout << e.what() << endl;
			}
		}
		cout << "\n===Co wypadlo===\n";
		int result_number = wheel.spin(); // losowanie wygranego pola
		const char* color = wheel.wheelResult(result_number);
		cout << "Liczba: " << result_number << "\nKolor: " << color << endl;
		int win = payout(type, bet, number, result_number);
		if (win == 0) { // sprawdzenie czy uzytkownik wygral
			cout << "Przegrales\n\n" << endl;
		}
		else if (win == 1 && type[0] == '2') {
			cout << "Wygrales " << bet << " zetonow!\n\n" << endl;
			player.win(bet * 2);
		}
		else if (win == 1 && type[0] == '1') {
			cout << "Wygrales " << (bet * 35) - bet << " zetonow!\n\n" << endl;
			player.win(bet * 35);
		}
		int buyMore;
		addChips();
		while (!valid) // petla sprawdzajaca poprawnosc podania checi do dalszej gry
		{
			cout << "Masz " << player.getChips() << " zetonow. Chcesz grac dalej [Tak-1, Nie-0]";
			cin >> yesno;
			try
			{
				if ((yesno[0] != '0' && yesno[0] != '1') || yesno.length() != 1)
				{
					throw invalid_argument("Zly wybor.");
				}
				valid = true;
			}
			catch (const invalid_argument& e)
			{
				cout << e.what() << endl;
			}
		}
	} while (yesno[0] != '0');
}