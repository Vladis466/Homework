#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"
#include <stdbool.h>

//testing salvager card.

//Salvager card trashed a card and increases number of buys by 1.

int main(int argc, char** argv){
	int i = 0;
	int j = 0;
	bool trigger = false;
//	int testVal = 0;
	struct gameState myGame;
    int card = salvager; 
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int handPos = 0;
	int* Bonus = 0;
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};	
	


	for(i = 2; i < 5; i++){
		j = 1;
		initializeGame(i, k, j, &myGame); 
		
		int numCheck = myGame.numBuys;	//Get initial number of actions possible
//			printf("amount of actions %d \n", numCheck); 
		
		cardEffect(card, choice1, choice2, choice3, &myGame, handPos, Bonus);
//			printf("amount of actions %d \n", myGame.numBuys); 			
		if ( numCheck != myGame.numBuys - 1) {    //should be equal cuz you get 1 more action.
			printf("amount of buys is incorrect, salvager card does not work correctly. \n");
			trigger = true;
		}	
	
	}
		
	if(trigger == false){ printf("Salvager card is working correctly congrats \n");}
	
	
	
	return 0;
}
