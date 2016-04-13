// randomly tests adventurer card

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


#define FILE_OUT "randomtestadventurer.out"
#define ITERATIONS 10000


int main(int argc, char ** argv) {
	FILE *f;
	struct gameState gs;
	int k[] = {adventurer, council_room, embargo, village,
		minion, mine, cutpurse, sea_hag, tribute, smithy};
	int numPlayers;
	int handPos;
	int result;
	int player;
	int handSize;
	int i;
	int numFailures;
	int deckAndDiscard;
	
	srand(time(NULL));
	f = fopen(FILE_OUT, "w");
	numFailures = 0;
	for (i = 0; i < ITERATIONS; i++) {
		numPlayers = (rand() % (MAX_PLAYERS-1)) + 2;
		initializeGame(numPlayers, k, rand(), &gs);
		gs.whoseTurn = player = 0; //rand() % numPlayers;
		handSize = gs.handCount[player];
		handPos = rand() % handSize;
		deckAndDiscard = gs.deckCount[player] + gs.discardCount[player];
		
		result = cardEffect(adventurer, 0, 0, 0, &gs, handPos, (int *) NULL);
		if (result) { // failure
			fprintf(f, "unexpected result of %d\n"
				"handPos == %d\nnumPlayers == %d\nplayer == %d\n",
				result, handPos, numPlayers, player);
			numFailures++;
		} else if (gs.handCount[player]!= handSize + 2) { // failure
			fprintf(f, "handsize wrong; expected %d, found %d:\n"
				"handPos == %d\nnumPlayers == %d\nplayer == %d\n",
				handSize + 2, gs.handCount[player],
				handPos, numPlayers, player);
			numFailures++;
		} else if (gs.deckCount[player]+gs.discardCount[player] !=
				deckAndDiscard - 2) {
			fprintf(f, "deck+discard count wrong; expected %d, found %d:\n"
				"handPos == %d\nnumPlayers == %d\nplayer == %d\n",
				deckAndDiscard-2, gs.deckCount[player]+gs.discardCount[player],
				handPos, numPlayers, player);
			numFailures++;
		} else { // success
			fprintf(f, "success\n");
		}
	}
	
	fprintf(f, "\nfound %d failures out of %d tests\n",
		numFailures, ITERATIONS);
	
	fclose(f);
	return 0;
}
