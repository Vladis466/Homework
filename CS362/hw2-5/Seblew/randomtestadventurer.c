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
	
	SelectStream(2);
	PutSeed(-1);
	
	int kingdomCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, minion, cutpurse };
	
	int randseed = floor(Random() * 999999999);
	initializeGame(2, kingdomCards, randseed, state);
	
	int currentPlayer = whoseTurn(state);
		
	int j, randCard;
	int handsize = floor(Random() * 10);
	printf("handsize = %d\n",handsize);
	for (j=0;j<handsize;j++){
		randCard = kingdomCards[(int)floor(Random() * 10)];
		printf("int floor random = %d\n",(int)floor(Random() * 10));
		printf("randCard = %d\n",randCard);
		//state->hand[currentPlayer][i] = 
	}
		
	//randomize cards in deck from full range
		
	printf("hand: ");
	int i;
	for(i=0; i < MAX_HAND;i++){
		if((state->hand[currentPlayer][i] != 0) && (state->hand[currentPlayer][i] != -1)){printf("%d ", state->hand[currentPlayer][i]);}
	}
	printf("\n");
	
	state->hand[currentPlayer][5] = adventurer; //putting adventurer in hand
	
	printf("hand: ");
	for(i=0; i < MAX_HAND;i++){
		if((state->hand[currentPlayer][i] != 0) && (state->hand[currentPlayer][i] != -1)){printf("%d ", state->hand[currentPlayer][i]);}
	}
	printf("\n");
	
	printf("Playing adventurer...\n");
	int ret = playCard(5,0,0,0,state); //playing adventurer from hand. handPos,choice1,choice2,choice3,state
	assert(ret != -1);
	
	printf("hand: ");
	for(i=0; i < MAX_HAND;i++){
		if((state->hand[currentPlayer][i] != 0) && (state->hand[currentPlayer][i] != -1)){printf("%d ", state->hand[currentPlayer][i]);}
	}
	printf("\n");
	
	//...
	
	return 0;
}