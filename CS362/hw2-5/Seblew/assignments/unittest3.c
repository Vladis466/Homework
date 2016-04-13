#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>

void checkGameOver(struct gameState *state) {
	int ret = isGameOver(state);
	assert(ret != -1); 
	printf("Is it over? - ");
	if(ret==1){printf("Game Over, man! Game Over!\n");}
	else if(ret==0){printf("Keep Playing!\n");}
	else{printf("something went wrong\n");}
}

int main () {
	
	struct gameState G;
	struct gameState *state = &G;
	struct gameState G2;
	
	int kingdomCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, minion, cutpurse };
	
	initializeGame(2, kingdomCards, 69, state);
	memcpy(&G2, &G, sizeof(struct gameState));
	struct gameState *pre = &G2;
	
	printf("Number of Province cards: %d\n", state->supplyCount[province]);
	checkGameOver(state);

	printf("Emptying Provinces...\n");
	state->supplyCount[province] = 0;
	checkGameOver(state);
	
	printf("Refilling Provinces...\n");
	state->supplyCount[province] = pre->supplyCount[province];
	printf("Number of Province cards: %d\n", state->supplyCount[province]);
	checkGameOver(state);
	
	printf("Emptying some supply piles...\n");
	state->supplyCount[minion] = 0;
	state->supplyCount[great_hall] = 0;
	state->supplyCount[village] = 0;
	checkGameOver(state);
	
	return 0;
}