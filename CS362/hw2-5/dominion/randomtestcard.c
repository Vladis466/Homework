#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"
#include <time.h>
//testing card salvager using RANDOM testing.
//Reveal cards from your deck until you get two treasure cards. put all revealed cards
// in the discard pile and those two treasure cards in your hand.


int main(int argc, char** argv){
	int j = 0;
	int trigger = 0;
//	int testVal = 0;
	struct gameState myGame;
    int card = salvager; 
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int players = 0;
	int handPos = 0;
	int* Bonus = 0;
	int oldCount = 0;
	int currPlay = 0;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};	
		   
	srand(time(NULL));
//	int r = rand() % 20;
	players = (int) rand() % 5;
	if(players < 2){ players = 2; }   //Setting our rand amount of players.
	
	
	
	
	
	for (j = 1; j < 100; j++){ 
		for(currPlay = 0; currPlay < players; currPlay++){
			initializeGame(players, k, j, &myGame); 
									//reset coin counter
		

//Randomize the player's stats.		
			myGame.deckCount[currPlay] = (int) rand() % 501;
		    myGame.discardCount[currPlay] = (int) rand() % 501;
			myGame.handCount[currPlay] = (int) rand() % 11;
			myGame.playedCardCount = (int) rand() % 501;

			handPos = myGame.handCount[currPlay] - 1;
			
			oldCount = myGame.handCount[currPlay];  //current players hand count

	

		
		
			int numCheck = myGame.numBuys;	//Get initial number of actions possible
	//			printf("amount of actions %d \n", numCheck); 

			cardEffect(card, choice1, choice2, choice3, &myGame, handPos, Bonus);
	//			printf("amount of actions %d \n", myGame.numBuys); 			
			if ( numCheck != myGame.numBuys - 1) {    //should be equal cuz you get 1 more action.
				printf("amount of buys is incorrect, salvager card does not work correctly. %d\n", j);
				
				trigger = 1;
			}
			if( myGame.handCount[currPlay] == oldCount ) { break; }
			//printf("%d", oldCount);
			//printf("----- %d\n", myGame.handCount[currPlay]);
			
///Aserrrt that the handcount is one less that before.
			assert(myGame.handCount[currPlay] == oldCount -1);
	
		}
			
	}	

	if(trigger == 0){ printf("Salvager card is working correctly congrats \n");}
	
	return 0;
}