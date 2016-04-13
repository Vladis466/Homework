#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

int main(int argc, char const *argv[]){
	//outpost
	struct gameState* gstate = malloc(sizeof(struct gameState));
	int j,k;
	int returnno;
	int player = 1;
	int card = outpost;
	int choice1 = -1;
	int* bonus = 0;
	int outpostno = 0;
	SelectStream(2);
	PutSeed(4);
	gstate->hand[0][0] = card;
	gstate->handCount[0] = 1;
	gstate->handCount[player] = 10;	
	for(j = 0; j < 27; j++)
	{					
		for(k = 0; k < 10; k++)
			gstate->supplyCount[j]++;
	}			
	outpostno++;	
	returnno = cardEffect(card, choice1, -1, -1, gstate, 1, bonus);	
	if (gstate->outpostPlayed != outpostno)
	{
		printf("wrong number of outposts played\n");
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