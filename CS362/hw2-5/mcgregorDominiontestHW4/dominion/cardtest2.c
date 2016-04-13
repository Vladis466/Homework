// unit test for cardEffectGreatHall()

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
	
	printf("cardtest2 for cardEffectGreatHall(): ");
	
	initializeGame(2, k, 35, &state);
	handPos = 0;
	currentPlayer = 0;
	numCards = state.handCount[currentPlayer];
	numActions = state.numActions;
	
	cardEffectGreatHall(handPos, currentPlayer, &state);
	
	if (state.handCount[currentPlayer] != numCards) { // failure
		printf("expected %d cards, found %d\n",
			numCards, state.handCount[currentPlayer]);
	} else if (state.numActions != numActions + 1) { // failure
		printf("expected %d actions, found %d\n",
			numActions + 1, state.numActions);
	} else { // success
		printf("success\n");
	}
	
	return 0;
}
