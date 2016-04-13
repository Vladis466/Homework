#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

int check(struct gameState *before, struct gameState *after)
{
	int test_flag = 0;
	int player = after->whoseTurn;
	if(before->whoseTurn != after->whoseTurn)
	{
		player = before->whoseTurn;
		printf("incorrect player turn\n");
		test_flag = -1;
	}
	if(before->numActions != after->numActions + 1)
	{
		printf("incorrect actions count\n");
		test_flag = -1;
	}
	if(before->handCount[player] != after->handCount[player] - 1)
	{
		printf("incorrect hand count\n");
		test_flag = -1;
	}
	return test_flag;
}

int main () 
{
	int num_tests = 300;
	int test_counter = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
	struct gameState *newgame, before, after;
	int i, n, num_players, seed, adventurer_pos, test, deck, player;
	printf ("Random Test Adventurer Start\n");
	num_tests = num_tests + (rand() % (num_tests / 2));
	for (n = 0; n < num_tests; n++) 
	{
		newgame = malloc(sizeof(struct gameState));
		seed = rand();
		deck = rand() % MAX_DECK + 1;
		num_players = rand() % 4 + 2;
		adventurer_pos = rand() % 5;
		while(num_players > MAX_PLAYERS || num_players < 2)
		{
			num_players = rand() % 4 + 2;
		}
		initializeGame(num_players, k, seed, newgame);						//initialize new game
		player = newgame->whoseTurn;
		for(i = 0; i < deck; i++)
		{
			newgame->hand[player][i] = rand() % 27;							//randomize deck
		}
		newgame->hand[player][adventurer_pos] = adventurer; 				//put adventurer in hand
		memcpy(&before, newgame, sizeof(struct gameState));					//save state before
		test = playCard(adventurer_pos,0,0,0,newgame); 						//play adventurer
		if(test == -1)
		{
			test_counter++;
			printf("playCard failed\n");
		}
		memcpy(&after, newgame, sizeof(struct gameState));					//save state after
		test = check(&before, &after);
		if(test == -1)
		{
			test_counter++;
			printf("check failed\n");
		}
		free(newgame);
	}
	printf ("Random Test Finished with %d failed tests out of %d\n", test_counter, num_tests);
	return 0;
}