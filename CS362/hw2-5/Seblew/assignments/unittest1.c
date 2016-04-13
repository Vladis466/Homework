#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>

int main () {
	
	struct gameState G;
	struct gameState *state = &G;
	struct gameState G2;
	
	int kingdomCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, minion, cutpurse };
	
	initializeGame(2, kingdomCards, 69, state);
	
	memcpy(&G2, &G, sizeof(struct gameState));
	struct gameState *pre = &G2;
	
	printf("\nNumber of Buys:      %d\n", state->numBuys);
	printf("Number of Coins:     %d\n", state->coins);
	printf("Villages in Supply:  %d\n\n", state->supplyCount[village]);
	
	int ret = buyCard(village,state);
	assert(ret != -1); //ensure buy succeeded
	
	printf("\nNumber of Buys:      %d\n", state->numBuys);
	printf("Number of Coins:     %d\n", state->coins);
	printf("Villages in Supply:  %d\n", state->supplyCount[village]);
	
	//ensure values have decreased
	assert (pre->numBuys > state->numBuys); 
	assert (pre->coins > state->coins);
	assert (pre->supplyCount[village] > state->supplyCount[village]);
	
	return 0;
}