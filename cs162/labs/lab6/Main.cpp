#include "Dice.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

int rollTwoDice(const Dice& d1, const Dice& d2) {
	return d1.roll() + d2.roll();
}

int main(int argc, char** argv) {

	Dice first(5);
	Dice second(10);
	
	
	
	
	 for(int i=0; i<10; i++){
		cout << rollTwoDice(first, second) << endl;
			
	}
	 
	return 0; 
}