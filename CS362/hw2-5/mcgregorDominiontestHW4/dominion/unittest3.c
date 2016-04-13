// unit test for getWinners()

#include "dominion.h"
#include "rngs.h"
#include <stdio.h>

int main(int argc, char ** argv) {
	int players[] = {-1, -1};
	struct gameState state;
	int k[] = {great_hall, council_room, embargo, village,
		minion, mine, cutpurse, sea_hag, tribute, smithy};
	
	printf("unittest3 for getWinners(): ");
	
	initializeGame(3, k, 2609, &state);
	
	state.hand[0][0] = province;
	state.hand[0][1] = province;
	state.hand[0][2] = province;
	state.hand[0][3] = province;
	state.hand[0][4] = province;
	getWinners(players, &state);
	if (players[0]==0 || players[1]==1 || players[2]==1) { // failure
		printf("expected winner to be 1, found 1 is %d, 2 is %d, 3 is %d\n",
			players[0], players[1], players[2]);
		return 0;
	}
	
	
	state.hand[0][0] = curse;
	state.hand[0][1] = curse;
	state.hand[0][2] = curse;
	state.hand[0][3] = curse;
	state.hand[0][4] = curse;
	state.hand[1][0] = province;
	state.hand[1][1] = province;
	state.hand[1][2] = province;
	state.hand[1][3] = province;
	state.hand[1][4] = province;
	getWinners(players, &state);
	if (players[0]==1 || players[1]==0 || players[2]==1) { // failure
		printf("expected winner to be 2, found 1 is %d, 2 is %d, 3 is %d\n",
			players[0], players[1], players[2]);
		return 0;
	}
	
	
	state.hand[2][0] = province;
	state.hand[2][1] = province;
	state.hand[2][2] = province;
	state.hand[2][3] = province;
	state.hand[2][4] = province;
	getWinners(players, &state);
	if (players[0]==1 || players[1]==0 || players[2]==0) { // failure
		printf("expected winners to be 2 and 3, found 1 is %d, 2 is %d, and 3 is %d\n",
			players[0], players[1], players[2]);
		return 0;
	} // success
	
	printf("success\n");
	return 0;
}
