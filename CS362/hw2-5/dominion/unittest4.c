#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

//testing gainCard working or naaa.

int main(int argc, char** argv){
	int i = 0;
	struct gameState myGame;
    
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};	
	
	initializeGame(2, k, 1, &myGame);
	myGame.handCount[0] = 0;
	myGame.discardCount[3] = 0;
	myGame.deckCount[1] = 0;
	myGame.deckCount[0] = 0;
	
	for(i = 0; i < 4; i++)
	{
		gainCard(4, &myGame, 2, i);
		if( myGame.handCount[i] != 1){ printf("player %d card count is incorrect.\n", i + 1);}
		//printf("player %d discard is %d \n", i + 1, myGame.discardCount[i]);
		//printf("player %d deck count is %d \n", i + 1, myGame.deckCount[i]);
		
		gainCard(4, &myGame, 0, i);
		if( myGame.discardCount[i] != 1){ printf("player %d discard count is incorrect.\n", i + 1);}
		//printf("player %d discard is %d \n", i + 1, myGame.discardCount[i]);
		
		gainCard(4, &myGame, 1, i);
		if( myGame.deckCount[i] != 1){ printf("player %d deck count is incorrect.\n", i + 1);}
		//printf("player %d deck count is %d \n", i + 1, myGame.deckCount[i]);
	}
	printf("If no error messages were recieved, gainCard() can be considered to be working correctly");
	
	
	return 0;
}


/* 		if( myGame.handCount[i] != 5){ printf("player %d card count is incorrect.\n", i + 1, myGame.handCount[i]);
		if( myGame.discardCount[i] != 5){ printf("player %d card count is incorrect.\n", i + 1, myGame.discardCount[i]);
		if( myGame.deckCount[i] != 5){ printf("player %d card count is incorrect.\n", i + 1, myGame.deckCount[i]); 
		printf("player %d discard is %d \n", i + 1, myGame.discardCount[i]);
		printf("player %d deck count is %d \n", i + 1, myGame.deckCount[i]);     */