#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

int main(int argc, char const *argv[]){
	//embargo
	struct gameState* gstate = malloc(sizeof(struct gameState));
	int j,k;
	int returnno;
	int currentPlayer = 1;
	int card = embargo;
	int choice1 = 0;
	int* bonus = 0;
	int testTokens[27];
	SelectStream(2);
	PutSeed(4);
	choice1 = 13;
	gstate->hand[0][0] = card;
	gstate->handCount[0] = 1;
	for(j = 0; j < 27; j++)
	{
		for(k = 0; k < 10; k++)
		gstate->supplyCount[j]++;
	}
	testTokens[choice1]++;
	returnno = cardEffect(card, choice1, -1, -1, gstate, 0, bonus);
	if (testTokens[choice1] != gstate->embargoTokens[choice1])
	{
		printf("wrong number of embargo tokens\n");
	}
	else
	{
		printf("test passed\n");
	}
	if(gstate->coins != 2)
	{
		printf("coins not added\n");	
	}
	else
	{
		printf("test passed\n");
	}
	free(gstate);
	return 0;
}