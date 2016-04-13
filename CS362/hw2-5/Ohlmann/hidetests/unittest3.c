#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//buyCard
int main()
{
	struct gameState* gstate = malloc(sizeof(struct gameState));
	int i,j,k;
	int supplyPos;
	int testNumBuys;
	int* supply = malloc(sizeof(int)*27);
	int maxPlayers = 4;
	SelectStream(2);
	PutSeed(3);
	for (j = 1; j <= maxPlayers; j++)
	{	
		gstate->numPlayers = j;
		for(supplyPos = 0; supplyPos < 27; supplyPos++ )
		{
			for(i = 0; i< 27; i++)
			{
				gstate->supplyCount[i] = 10;
				supply[i] = gstate->supplyCount[i];
			}
			gstate->coins = 8;
			gstate->numBuys = 1;
			k = buyCard(supplyPos,gstate);
			if (k != 0  || gstate->numBuys != 0 || supply[supplyPos] - 1 != gstate->supplyCount[supplyPos])
				printf("test failed\n");
			else
				printf("test passed\n");
		}
	}
	return 0;
}