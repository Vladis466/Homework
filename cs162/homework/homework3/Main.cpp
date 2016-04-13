#include <iostream>
#include <cstdlib>
#include "hw3.hpp"

using namespace std;

char choose_game() {
	char choose;
	
	cout << "What game would you like to play, press s for Stud poker" << endl;
	cout << "Or press d for Draw poker" << endl;
	cin >> choose;
	
	return choose;
}
int main() {
	
	
	card_games *game;
	
	char game_choice;

	game_choice = choose_game();

	if(game_choice == 's'){
	game = new StudPoker;
	
	}else if(game_choice == 'd'){	
	game = new go_drawPoker;
	}
	

	game->play();
	
	return 0;
} 

