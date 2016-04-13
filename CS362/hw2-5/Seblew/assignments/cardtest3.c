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

	int currentPlayer = whoseTurn(state);
		
	printf("hand: ");
	int i;
	for(i=0; i < MAX_HAND;i++){
		if((state->hand[currentPlayer][i] != 0) && (state->hand[currentPlayer][i] != -1)){printf("%d ", state->hand[currentPlayer][i]);}
	}
	printf("\n");
	
	printf("Putting cutpurse (21) in hand...\n");
	state->hand[currentPlayer][5] = cutpurse; //putting cutpurse in hand
	
 	printf("hand: ");
	for(i=0; i < MAX_HAND;i++){
		if((state->hand[currentPlayer][i] != 0) && (state->hand[currentPlayer][i] != -1)){printf("%d ", state->hand[currentPlayer][i]);}
	}
	printf("\n"); 
	
	printf("coins: %d\n", state->coins);
	printf("Playing cutpurse...\n");
	int ret = playCard(5,0,0,0,state); //playing cutpurse from hand. handPos,choice1,choice2,choice3,state
	assert(ret != -1);
	
	printf("hand: ");
	for(i=0; i < MAX_HAND;i++){
		if((state->hand[currentPlayer][i] != 0) && (state->hand[currentPlayer][i] != -1)){printf("%d ", state->hand[currentPlayer][i]);}
	}
	printf("\n");

	printf("coins: %d\n", state->coins);


	return 0;
}