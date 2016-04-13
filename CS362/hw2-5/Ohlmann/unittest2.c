#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>



//This function will test the updateCoins() function to make sure all values are in the range limits.
int main(){
	int i = 0;
	struct gameState testGame;
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};	
	
	initializeGame(2, k, 1, &testGame);

	testGame.numPlayers = 4;
	int noBonus = 0;
	
	for(i = 0; i < 4; i++)
	{
		updateCoins(i, &testGame, noBonus);
		
	}

	if(testGame.coins == 0){printf("test passed, no coins in game");}
		
	else{ printf("test failed, there are coins in the game");}

	return (0);
	
}


