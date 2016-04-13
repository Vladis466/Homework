#include <iostream>
#include <time.h>
#include "Dice.hpp"

Dice::Dice() {
	numSides = 6;
	srand(time(NULL)); /* seeds random number generator */
}

Dice::Dice(int numSides) {
	this->numSides =  numSides;
	srand(time(NULL)); /* seeds random number generator */
}

int Dice::roll() const {
	return( rand() % numSides) + 1;
}

LoadedDice1::LoadedDice1(){
	numSides = 6;
	srand(time(NULL)); /* seeds random number generator */
}

LoadedDice1::LoadedDice1(int numSides){
	this->numSides =  numSides;
	srand(time(NULL)); /* seeds random number generator */
}


int LoadedDice1::roll() const {


}

LoadedDice2::LoadedDice2(){
	numSides = 6;
	srand(time(NULL)); /* seeds random number generator */
}

LoadedDice2::LoadedDice2(int numSides){
	this->numSides =  numSides;
	srand(time(NULL)); /* seeds random number generator */
}


int LoadedDice2::roll() const {


}