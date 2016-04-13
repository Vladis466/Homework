#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

//testing card outpost.

//ou only draw 3 cards (instead of 5) in this turns Clean-up phase. Take an extra turn after this one. 

int main(int argc, char** argv){
	int i = 0;
	int j = 0;
//	int testVal = 0;
	struct gameState myGame;
    int card = outpost; 
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int handPos = 0;
	int* Bonus = 0;
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};	
	


	for(i = 2; i < 5; i++){
		for (j = 1; j < 10; j++){ 
			initializeGame(i, k, j, &myGame); 
			
			int numCheck = myGame.outpostPlayed;
			
			cardEffect(card, choice1, choice2, choice3, &myGame, handPos, Bonus);
			
			if ( numCheck != myGame.outpostPlayed - 1)     //should be equal cuz you get 1 more action.
				printf("Outpost card being played was not detected. \n");
			else
				printf(".");
		
	
		}
			
	}	
	printf("If no error messages were seen then the outpost card is being played correctly.  \n");
	
	return 0;
}
