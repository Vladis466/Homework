// unit test for isGameOver()

#include "dominion.h"
#include "rngs.h"
#include <stdio.h>

int main(int argc, char ** argv) {
	struct gameState state;
	int k[] = {great_hall, council_room, embargo, village,
		minion, mine, cutpurse, sea_hag, tribute, smithy};
	
	printf("unittest2 for isGameOver(): ");
	
	initializeGame(2, k, 5330, &state);
	
	state.supplyCount[curse] = 0;
	state.supplyCount[mine] = 0;
	if (isGameOver(&state) == 1) { // failure
		printf("expected isGameOver() to be false, but it's true\n");
		return 0;
	}
	
	state.supplyCount[curse] = 4;
	state.supplyCount[mine] = 3;
	state.supplyCount[province] = 0;
	if (isGameOver(&state) == 0) { // failure
		printf("expected isGameOver() to be true by province, but it's false\n");
		return 0;
	}
	
	state.supplyCount[province] = 5;
	state.supplyCount[curse] = 0;
	state.supplyCount[mine] = 0;
	state.supplyCount[treasure_map] = 0;
	if (isGameOver(&state) == 0) { // failure
		printf("expected isGameOver() to be true by 3 empty piles, but it's false\n");
		return 0;
	} // success
	
	printf("success\n");
	return 0;
}
