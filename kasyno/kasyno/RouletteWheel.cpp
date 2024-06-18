#include "RouletteWheel.h"

mt19937 generatorRoulette(time(nullptr)); //generator liczb losowych
uniform_int_distribution<> distributionRoulette(0, 36);
int random;

RouletteWheel::RouletteWheel() {
	int size = 37;
	numbers = new int[size];
	colors = new const char* [size];

	for (int i = 0; i < size; ++i) { //petla przypisujaca liczby i kolory do komorek tablic
		numbers[i] = i;
		if (i == 0) {
			colors[i] = "Zielony";
		}
		else if (i % 2 == 0) {
			colors[i] = "Czarny";
		}
		else {
			colors[i] = "Czerwony";
		}
	}
}

int RouletteWheel::spin() {
	random = distributionRoulette(generatorRoulette); // losowanie liczby z zakresu
	return numbers[random];
}

const char* RouletteWheel::wheelResult(int number) {
	return colors[number];
}