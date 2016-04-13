#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>

void checkCoins(struct gameState *state, int bonus){
	int ret = updateCoins(1, state, bonus);
	assert(ret != -1);
	printf("Current coins: %d\n", state->coins);
	assert(state->coins >= 0);
}

int main () {
	
	struct gameState G;
	struct gameState *state = &G;
	
	int kingdomCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, minion, cutpurse };
	int bonus = 0;
	
	initializeGame(2, kingdomCards, 69, state);
	
	printf("Starting coins: %d\n", state->coins);

	printf("Updating with no bonus...\n");
	checkCoins(state,bonus);
	
	printf("Updating with +3 bonus...\n");
	bonus = 3;
	checkCoins(state,bonus);
	
	return 0;
}
