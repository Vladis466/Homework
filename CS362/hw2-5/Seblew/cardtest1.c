#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

//testing great_Hall card.

//great_Hall card increases the number of actions by 1 discard pile by 1 and reduces players hand by 1

int main(int argc, char** argv){
	int i = 0;
	int j = 0;
	int trigger = 0;
//	int testVal = 0;
	struct gameState myGame;
    int card = great_hall; 
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
		
		int numCheck = myGame.numActions;	//Get initial number of actions possible
//			printf("amount of actions %d \n", numCheck); 
		
		cardEffect(card, choice1, choice2, choice3, &myGame, handPos, Bonus);
		if ( numCheck != myGame.numActions - 1)  {    //should be equal cuz you get 1 more action.
			printf("amount of actions is incorrect for player %d \n", i);
			trigger = 1;
		}
			
	if( trigger == 0) 
		printf("correct amount of actions added. \n");
	
		
	}
	
	
	return 0;
}


