// unit test for updateCoins()

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>

int main(int argc, char ** argv) {
	int coins;
	int bonus;
	int player;
	struct gameState state;
	int k[] = {great_hall, council_room, embargo, village,
		minion, mine, cutpurse, sea_hag, tribute, smithy};
	
	printf("unittest4 for updateCoins(): ");
	
	initializeGame(2, k, 1157, &state);
	
	state.hand[0][0] = copper;
	state.hand[0][1] = silver;
	state.hand[0][2] = gold;
	state.hand[0][3] = curse;
	state.hand[0][4] = copper;
	bonus = 5;
	coins = 1 + 2 + 3 + 1 + 5;
	player = 0;
	
	updateCoins(player, &state, bonus);
	
	if (state.coins != coins) { // failure
		printf("expected coins of value %d, found value %d\n",
			coins, state.coins);
	} else { // success
		printf("success\n");
	}
	
	return 0;
}
