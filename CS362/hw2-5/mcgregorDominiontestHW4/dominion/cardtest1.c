// unit test for cardEffectSmithy()

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>

int main(int argc, char ** argv) {
	int handPos;
	int currentPlayer;
	struct gameState state;
	int numCards;
	int k[10] = {great_hall, council_room, embargo, village,
		minion, mine, cutpurse, sea_hag, tribute, smithy};
	
	printf("cardtest1 for cardEffectSmithy(): ");
	
	initializeGame(2, k, 15, &state);
	handPos = 0;
	currentPlayer = 0;
	numCards = state.handCount[currentPlayer];
	
	cardEffectSmithy(handPos, currentPlayer, &state);
	
	if (state.handCount[currentPlayer] != numCards + 2) { // failure
		printf("expected %d cards, found %d\n",
			numCards + 2, state.handCount[currentPlayer]);
	} else { // success
		printf("success\n");
	}
	
	return 0;
}
