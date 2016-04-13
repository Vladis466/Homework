// randomly tests mine card

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


#define FILE_OUT "randomtestcard.out"
#define ITERATIONS 10000


int main(int argc, char ** argv) {
	FILE *f;
	struct gameState gs;
	int k[] = {adventurer, council_room, embargo, village,
		minion, mine, cutpurse, sea_hag, tribute, smithy};
	int choice1;
	int choice2;
	int handPos;
	int card;
	int numPlayers;
	int result;
	int handSize;
	int player;
	int i;
	int numFailures;
	int predictSuccess;
	
	srand(time(NULL));
	f = fopen(FILE_OUT, "w");
	numFailures = 0;
	for (i = 0; i < ITERATIONS; i++) {
		numPlayers = (rand() % (MAX_PLAYERS-1)) + 2;
		initializeGame(numPlayers, k, rand(), &gs);
		// set player turn, get size and choices
		gs.whoseTurn = player = 0; //rand() % numPlayers;
		handSize = gs.handCount[player];
		choice1 = rand() % handSize;
		handPos = (choice1 + 1 + (rand() % (handSize-1))) % handSize;
		// set choice cards
		switch (rand() % 3) {
			case 0:
				gs.hand[player][choice1] = card = copper;
				switch (rand() % 2) {
					case 0: choice2 = copper; break;
					default: choice2 = silver; break;
				}
				break;
			case 1:
				gs.hand[player][choice1] = card = silver;
				switch (rand() % 3) {
					case 0: choice2 = copper; break;
					case 1: choice2 = silver; break;
					default: choice2 = gold; break;
				}
				break;
			default:
				gs.hand[player][choice1] = card = gold;
				switch (rand() % 3) {
					case 0: choice2 = copper; break;
					case 1: choice2 = silver; break;
					default: choice2 = gold; break;
				}
				break;
		}
		
		// randomly adds a fault
		if (rand() % 2) {
			switch (rand() % 3) {
				case 0: // choice 1 is not a coin
					if (rand()%2) { // positive
						gs.hand[player][choice1] =
							(gold+1+(rand()%20000))%(20001+gold-copper);
					} else { // negative
						gs.hand[player][choice1] = -1*(rand()%20000);
					}
					break;
				case 1: // choice 2 is not a card
					if (rand()%2) { // positive
						gs.hand[player][choice1] = 
							treasure_map+1+(rand()%20000);
					} else { // negative
						gs.hand[player][choice1] = -1*(rand()%20000);
					}
					break;
				default: // bad coin choices; replacing copper with gold
					gs.hand[player][choice1] = copper;
					choice2 = gold;
					break;
			}
			predictSuccess = 0;
		} else {
			predictSuccess = 1;
		}
		
		result = cardEffect(mine, choice1, choice2, 0, &gs,
			handPos, (int *) NULL);
			
		if (!predictSuccess) { // predictSuccess == 0
			if (!result) { // failure
				fprintf(f, "unexpected result of %d"
					"\nchoice1 == %d\nchoice2 == %d\nhandPos == %d"
					"\nnumPlayers == %d\nplayer == %d\n",
					result, choice1, choice2, handPos, numPlayers, player);
				numFailures++;
			} else { // success
				fprintf(f, "success\n");
			}
			continue;
		} // predictSuccess == 1
		
		
		if (result) { // failure
			fprintf(f, "unexpected result of %d\n"
				"choice1 == %d\nchoice2 == %d\nhandPos == %d\n"
				"numPlayers == %d\nplayer == %d\n",
				result, choice1, choice2, handPos, numPlayers, player);
			numFailures++;
		} else if (gs.handCount[player]!= handSize - 1) { // failure
			fprintf(f, "handsize wrong; expected %d, found %d:\n"
				"choice1 == %d\nchoice2 == %d\nhandPos == %d\n"
				"numPlayers == %d\nplayer == %d\n",
				handSize - 1, gs.handCount[player], choice1,
				choice2, handPos, numPlayers, player);
			numFailures++;
		} else if (getCost(gs.hand[player][gs.handCount[player]-1]) >
				getCost(card) + 3) { // failure
			fprintf(f, "new card wrong; expected cost <= %d, found %d\n",
				getCost(card) + 3,
				getCost(gs.hand[player][gs.handCount[player]-1]));
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
