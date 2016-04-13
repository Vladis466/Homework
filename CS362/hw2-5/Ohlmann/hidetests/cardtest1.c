#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

int main(int argc, char const *argv[]){
	//steward
	struct gameState* gstate = malloc(sizeof(struct gameState));
	int j,k;
	int returnno;
	int card = steward;
	int choice1 = 3;
	int* bonus = 0; 
	SelectStream(2);
	PutSeed(4);
	gstate->whoseTurn = 0;
	gstate->hand[0][0] = card;
	gstate->hand[0][1] = province;
	gstate->hand[0][2] = province;
	gstate->deck[0][0] = province;
	gstate->deck[0][1] = province;
	gstate->handCount[0] = 3;
	gstate->deckCount[0] = 2;
	for( j = 0; j < 27; j++)
	{
		for(k = 0; k < 10; k++)
			gstate->supplyCount[j]++;
	}
	returnno = cardEffect(card, choice1, 1, 2, gstate, 1, bonus);
	if(returnno != 0)
	{
		printf("wrong return value\n");
	}
	switch(choice1)
	{
		case 1:
			if(gstate->handCount[0] != 4)
			{
				printf("wrong hand count1\n");
			}
			break;
		case 2:
			if (gstate->handCount[0]!= 0)
			{
				printf("wrong hand count2\n");
			}
			break;
		case 3:
			if (gstate->coins != 2)
			{
				printf("wrong number of coins\n");
			}
			break;
		default: break;
	}
	free(gstate);
	return 0;
}