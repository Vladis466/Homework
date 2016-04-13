// unit test for cardEffect() for council_room

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>

int main(int argc, char ** argv) {
	int handPos;
	int currentPlayer;
	struct gameState state;
	int numCards;
	int numBuys;
	int otherNumCards;
	int k[] = {great_hall, council_room, embargo, village,
		minion, mine, cutpurse, sea_hag, tribute, smithy};
	
	printf("cardtest3 for cardEffect() for council_room: ");
	
	initializeGame(2, k, 150, &state);
	handPos = 0;
	currentPlayer = 0;
	numCards = state.handCount[currentPlayer];
	numBuys = state.numBuys;
	otherNumCards = state.handCount[currentPlayer + 1];
	
	cardEffect(council_room, 0, 0, 0, &state, handPos, (int *) NULL);
	
	if (state.handCount[currentPlayer] != numCards + 3) { // failure
		printf("expected %d cards, found %d\n",
			numCards + 3, state.handCount[currentPlayer]);
	} else if (state.numBuys != numBuys + 1) { // failure
		printf("expected %d buys, found %d\n",
			numBuys + 1, state.numBuys);
	} else if (state.handCount[currentPlayer + 1] != otherNumCards + 1) { // failure
		printf("expected other player to have %d cards, found %d\n",
			otherNumCards + 1, state.handCount[currentPlayer + 1]);
	} else { // success
		printf("success\n");
	}
	
	return 0;
}
