#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

int main(int argc, char const *argv[]){
	//salvager
	struct gameState* gstate = malloc(sizeof(struct gameState));
	int j,k;
	int returnno;
	int card = salvager;
	int choice1 = -1;
	int handPos = 1;
	int* bonus = 0;
	SelectStream(2);
	PutSeed(4);
	gstate->whoseTurn = 0;
	gstate->hand[0][0] = card;
	gstate->hand[0][1] = province;
	gstate->handCount[0] = 2;
	choice1 = handPos;
	gstate->numBuys = 0;
	for(j = 0; j < 27; j++)
	{
		for(k = 0; k < 10; k++)
			gstate->supplyCount[j]++;
	}
	returnno = cardEffect(card, choice1, -1, -1, gstate, handPos, bonus);
	if (gstate->numBuys != 1)
	{
		printf("wrong number of buys\n");
	}
	else
	{
		printf("test passed\n");
	}
	if (gstate->coins != 8)
	{
		printf("wrong number of coins\n");
	}
	else
	{
		printf("test passed\n");
	}
	if(returnno != 0)
	{
		printf("wrong return value\n");
	}
	else
	{
		printf("test passed\n");
	}
	free(gstate);
	return 0;
}