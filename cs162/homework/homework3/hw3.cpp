#include <iostream>
#include <cstdlib>
#include "hw3.hpp"

using namespace std;







void deck::initializor(){
			string Values[] = {"ace", "2", "3" , "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
			
			for(int i = 0; i < 13; i++) {
				myDeck[i].suit = "hearts";
				myDeck[i].value = Values[i];
/* 				cout << myDeck[i].suit << endl;
				cout << myDeck[i].value << endl; */
			}
			
			for(int i = 13; i < 26; i++) { 
				myDeck[i].suit = "diamonds";
				myDeck[i].value = Values[i-13];

			}
			for(int i = 26; i < 39; i++) {
				myDeck[i].suit = "spades";
				myDeck[i].value = Values[i-26];
			}
			for(int i = 39; i < 52; i++) {
				myDeck[i].suit = "clovers";
				myDeck[i].value = Values[i-39];
				
			}
		}
		
void deck::deckshuffle(){
			card temp;
			int dum;
			
			for (int i = 0; i < 52; i++){
				dum = rand() % (51);
				cout << dum << endl;
				temp = myDeck[i];
				myDeck[i] = myDeck[dum];
				myDeck[dum] = myDeck[i];
				
				if(i == 50) {
					break;
				}
			}	
			
			
		}





	
int card_games::Judgement(int amt){
		int TheScore = 0;
		int next;
		int cardVal[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		string Valuesx[] = {"ace", "2", "3" , "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
		
		for (int i = 0; i < amt; i++){
			for (int j = 0; j < 5; j++){
				for (int k = 0; k < 13; k++){
					//histogram of card values;
					if(players[i].mycard[j].value == Valuesx[k]){
					cardVal[k]++;
					}
				} 
			}
		
			cout << "Hello player " << (i+1)  << endl;
			cout << "your highest value is" << endl;

		
			/* for (int k = 12; k > -1; k--){
				cout << cardVal[k];
			} */
			
			
			for (int k = 12; k > -1; k--){
				if(cardVal[k] == 4){
					cout << "you've got four of a kind of " << Valuesx[k] << endl;
					players[i].TheScore = 8;
					break;
				}
			}
				
			if(players[i].TheScore != 8 && players[i].TheScore != 9){
				for (int k = 12; k > -1; k--){
					if(cardVal[k] == 3){
						for (int m = 12; m > -1; m--){
							if (cardVal[m] == 2){
								cout << "you have a full house high of " << Valuesx[k] << endl;
								players[i].TheScore = 7;
								break;
							}
						}
						for (int m = 12; m > -1; m--){
							if (cardVal[m] == 1 && players[i].TheScore != 7){
								cout << "you have a three of a kind high of" << Valuesx[k] << endl;
								players[i].TheScore = 4;
								break;
							}
						}
					}
				}
				if(players[i].TheScore != 7 && players[i].TheScore != 4){	
					for (int k = 12; k > -1; k--){
						if(cardVal[k] == 2){
							int x = k;
							for (int m = 0; m < 13; m++){
								if(cardVal[m] == 2 && cardVal[m] != cardVal[x]){
									cout << "you have two pair high of " << Valuesx[k] << endl;
									players[i].TheScore = 3;
									
									break;
								}
							}
							for (int m = 12; m > -1; m--){
								if(cardVal[m] == 1 && players[i].TheScore != 3){
									cout << "you have one pair high of " << Valuesx[k] << endl;
									players[i].TheScore = 2;
									break;
								}
							}
							
						}
					}
				}
			}
				
				
				
				
				
				
				
				
			//reset the value of the counter to test the next persons hand
			for (int k = 12; k > -1; k--){
				cardVal[k] = 0;
			}
			
			cout << "Please press 1" << endl << endl << endl;
			cin >> next;
		}
		
		//lets find out who won!!!!!
		int max = players[0].TheScore;
		int winner;
		
		for(int f = 0; f < amt; f++){
		
			if (players[f].TheScore > max) {
			max = players[f].TheScore;
			}
		} 

		
		for(int i = 0; i < amt; i++){
			
			if(max == players[i].TheScore){
				cout << "The winner is player " << i+1 << ". CONGRATULATIONS!!" << endl;
				winner = i;
				break;
			}
		}
			
	return winner;	
	}

	
//void card_games::virtual play(){}
	
	
	
	
	





void StudPoker::play(){
			//3 dummies. round for the round as well as the player's card, i for player, and n for card from deck
			int games;
			char bet;
			int betamt;
			int amt; //of people playing
			int youWon;
			int trigger[] = { 0, 0, 0, 0, 0, 0}; //This bad boy switches when someone decides not to bet
			mainDeck.initializor();
			
			cout << "Insert the amount of players" << endl;
			cin >> amt;
			
			cout << "How many games would you like to play?";
			cin >> games;
			//How many rounds will be played total
			for(int f = 0; f < games; f++){
				cout << "round " << f + 1 << " begin" << endl << endl;
				//initialize the players for each round and the pot.
				for(int i = 0; i < amt; i++){
					players[i].player_init();
					
					if(f == 0){
						players[i].cash = 50;
					}
				}
				//n is a counter for each card that gets pulled from the deck
				totalpot.potInit();
				int n = 0;
				int round = 0;
				//shuffle that beezy
				mainDeck.deckshuffle();
				
				
				do{
					round++;
					
					//just a checker for proof of shuffle
					/* for(int i = 0; i < 52; i++ ){
						cout << mainDeck.myDeck[i].suit;
						cout << mainDeck.myDeck[i].value << endl;
					} */
					
					for (int i = 0; i < amt; i++){
						n++;
						players[i].mycard[round-1] = mainDeck.myDeck[n-1];
						
					}
					//	cout << players[2].mycard[round-1].value << endl;
					//	cout << players[3].mycard[round-1].suit << endl;
						
					//cout << endl << endl << n << endl;
					
					for (int i = 0; i < amt; i++){
						if (trigger[i] != 1){
							cout << "Hello player " << (i+1) << endl;
							cout << "You currently hold" << endl;
								
							for (int j = 0; j < 5; j++){
								cout << players[i].mycard[j].value << " of " << players[i].mycard[j].suit << endl;
							}
							cout << endl;
							
							
								cout << "Enter the amount of cash-points you want to bet. You currently have "<< endl;
								cout << players[i].cash << endl << endl;
								cin >> betamt;
								players[i].cash = players[i].cash - betamt;
								totalpot.cash = totalpot.cash + betamt;
							
							if(betamt == 0){
								trigger[i] = 1;
							}
						}	
					}
					//MAKE FUNCTION TO FIND WHO WINS!!!!!!! AND YOURE DONE (NOT REALLY)
					
					
				} while(round < 5);	
				
				for (int i = 0; i < amt; i++){
					if(trigger[i] == 1)
						for (int j = 0; j < 5; j++){
						players[i].mycard[j].value = j;  //scramble his cards so he has NOTHING TECHNICALLY GOD IM SO SHNEAKY BUAHAHAHAH
					}
				}
				
				youWon = Judgement(amt);
				
				cout << "The pot is now worth this many dollhairs " << totalpot.cash << endl;
				cout << "It all goes to player " << youWon + 1 << endl; 
				players[youWon].cash = players[youWon].cash + totalpot.cash;
			}
		}
		




	

void go_drawPoker::play(){
//3 dummies. round for the round as well as the player's card, i for player, and n for card from deck
			int games;
			char bet;
			int betamt;
			bool Switch;
			int amt;
			int youWon;
			mainDeck.initializor();
			int trigger[] = { 0, 0, 0, 0, 0, 0}; //This bad boy switches when someone decides not to bet
			cout << "Insert the amount of players" << endl;
			cin >> amt;
			
			cout << "How many games would you like to play?";
			cin >> games;
			//How many rounds will be played total
			for(int f = 0; f < games; f++){
				cout << "round " << f + 1 << " begin" << endl << endl;
				//initialize the players for each round and the pot. Put cards back in deck.
				for(int i = 0; i < amt; i++){
					players[i].player_init();
					
					if(f == 0){
						players[i].cash = 50;
					}
				}
				//n is a counter for each card that gets pulled from the deck
				totalpot.potInit();
				int n = 0;
				int round = 0;
				//shuffle that beezy
				mainDeck.deckshuffle();
				
					//just a checker for proof of shuffle
					/* for(int i = 0; i < 52; i++ ){
						cout << mainDeck.myDeck[i].suit;
						cout << mainDeck.myDeck[i].value << endl;
					} */
					
					
					//give everyone initial five cards
				for (int i = 0; i < 5; i++){
					for(int j = 0; j < amt; j++){
						n++;
						players[j].mycard[i] = mainDeck.myDeck[n-1];
					}
				}
					
					
					
				//	cout << players[2].mycard[round-1].value << endl;
				//	cout << players[3].mycard[round-1].suit << endl;
					
				//cout << endl << endl << n << endl;
				
										
				for (int i = 0; i < amt; i++){
					cout << "Hello player " << (i+1) << ". Press b to bet. If you bet 0, you forfeit" << endl;
					cout << "You currently hold" << endl;
						
					for (int j = 0; j < 5; j++){
						cout << players[i].mycard[j].value << " of " << players[i].mycard[j].suit << endl;
					}
					cout << endl;
					
					cin >> bet; 
					if(bet == 'b'){
						cout << "Enter the amount of cash-points you want to bet. You currently have "<< endl << endl;
						cout << players[i].cash << endl << endl;
						cin >> betamt;
						players[i].cash = players[i].cash - betamt;
						totalpot.cash = totalpot.cash + betamt;
					}		
					if(betamt == 0){
						trigger[i] = 1;
					}					
					cout <<"In order from first to last card, press 1 to switch or 0 to keep it";
					for (int j = 0; j < 5; j++){
						cin >> Switch;
						if(Switch == true){	
							n++;
							players[i].mycard[j] = mainDeck.myDeck[n-1];
						}
					}	
					
					
				}
					//MAKE FUNCTION TO FIND WHO WINS!!!!!!! AND YOURE DONE (NOT REALLY)
					
				
									
				for (int i = 0; i < amt; i++){
					if(trigger[i] != 1){
						cout << "Hello player " << (i+1) << ". Press b to bet. If you bet 0, you forfeit" << endl;
						cout << "You currently hold" << endl;
							
						for (int j = 0; j < 5; j++){
							cout << players[i].mycard[j].value << " of " << players[i].mycard[j].suit << endl;
						}
						cout << endl;
						
						cin >> bet; 
						if(bet == 'b'){
							cout << "Enter the amount of cash-points you want to bet. You currently have "<< endl;
							cout << players[i].cash << endl << endl;
							cin >> betamt;
							players[i].cash = players[i].cash - betamt;
							totalpot.cash = totalpot.cash + betamt;
							
							if(betamt == 0){
								trigger[i] = 1;
							}
						}		
					}
				}
				
					
				for (int i = 0; i < amt; i++){
					if(trigger[i] == 1)
						for (int j = 0; j < 5; j++){
						players[i].mycard[j].value = j;  //scramble his cards so he has NOTHING TECHNICALLY GOD IM SO SHNEAKY BUAHAHAHAH
						}
					}
				
				
				
				
				
				
				
				
				
				youWon = Judgement(amt);
				
				cout << "The pot is now worth this many dollhairs " << totalpot.cash << endl;
				cout << "It all goes to player " << youWon + 1 << endl; 
				players[youWon].cash = players[youWon].cash + totalpot.cash;
			}
			
}






/* char choose_game() {
	char choose;
	
	cout << "What game would you like to play, press s for Stud poker" << endl;
	cout << "Or press d for Draw poker" << endl;
	cin >> choose;
	
	return choose;
} */


/* int main() {
	
	
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
}  */

/* void yourHand(player.mycard[5]){ 
	int sameNums = 0;
	int sameSuits = 0;
	
	for(i = 0; i < 5; i++){
			if(i < 4){
				if(mycard.suit[i] == mycard.suit[i+1]){
					sameSuits++;
				}
			}
			if(i < 4){
				if(mycard.value[i] == mycard.value[i+1]){
					sameNums++;
				}
			}
	}
	
 */
 
 
	
 //int ace, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king;
	
	
		
		
 