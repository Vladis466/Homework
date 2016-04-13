// unit test for cardEffect() for village

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>

int main(int argc, char ** argv) {
	int handPos;
	int currentPlayer;
	struct gameState state;
	int numCards;
	int numActions;
	int k[] = {great_hall, council_room, embargo, village,
		minion, mine, cutpurse, sea_hag, tribute, smithy};
	
	printf("cardtest4 for cardEffect() for village: ");
	
	initializeGame(2, k, 900, &state);
	handPos = 0;
	currentPlayer = 0;
	numCards = state.handCount[currentPlayer];
	numActions = state.numActions;
	
	cardEffect(village, 0, 0, 0, &state, handPos, (int *) NULL);
	
	if (state.handCount[currentPlayer] != numCards) { // failure
		printf("expected %d cards, found %d\n",
			numCards, state.handCount[currentPlayer]);
	} else if (state.numActions != numActions + 2) { // failure
		printf("expected %d actions, found %d\n",
			numActions + 2, state.numActions);
	} else { // success
		printf("success\n");
	}
	
	return 0;
}
