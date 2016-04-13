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
	
	int kingdomCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, minion, cutpurse };
	
	initializeGame(2, kingdomCards, 69, state);
	
	int ret = fullDeckCount(0, estate,state);
	assert(ret != -1); //ensure count succeeded
	printf("Number of Estates in deck:  %d\n", ret);
	
	ret = fullDeckCount(0, copper,state);
	assert(ret != -1); //ensure count succeeded
	printf("Number of Coppers in deck:  %d\n", ret);
	
	ret = fullDeckCount(0, village,state);
	assert(ret != -1); //ensure count succeeded
	printf("Number of Villages in deck: %d\n", ret);
	
	
	
	return 0;
}