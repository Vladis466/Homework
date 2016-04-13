#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

//testing smithy card..

//Using the smithy card increased your hand size by 3 and discards smithy card(increase of 2).

int main(int argc, char** argv){
	int i = 0;
	int j = 0;
//	int testVal = 0;
	struct gameState myGame;
    int card = smithy; 
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int handPos = 0;
	int* Bonus = 0;
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};	
	


	for(i = 2; i < 5; i++){
		for (j = 1; j < 7; j++){ 
			initializeGame(i, k, j, &myGame); 
			
			int numCheck = myGame.handCount[0];	//Get initial number of cards player has.
		//	printf("amount of cards %d \n", numCheck); 
			
			cardEffect(card, choice1, choice2, choice3, &myGame, handPos, Bonus);
		//	printf("amount of cards %d \n", myGame.handCount[0]); 
			if ( numCheck != myGame.handCount[0] - 2)     //should be equal cuz you			get 3 more cards.
				printf("amount of cards in hand is incorrect. Smithy not working correctly.\n");
			else
				printf(".");

		
	
		}
	}
	printf("If no error messages were seen then the smithy card is being played correctly.  \n");
	
	return 0;
}
