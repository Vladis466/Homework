#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//isGameOver
int main()
{
	struct gameState* gstate = malloc(sizeof(struct gameState));
	int i,j,k;
	int supplyPos;
	int maxPlayers = 4;
	SelectStream(2);
	PutSeed(3);
	for (j = 1; j <= maxPlayers; j++)
	{	
		gstate->numPlayers = j;
		printf("Testing isGameOver with %d player(s)\n\n",gstate->numPlayers);
		for(supplyPos = 0; supplyPos < 27; supplyPos++ )
		{
			for(i = 0; i< 27; i++)
			{
				gstate->supplyCount[i] = 10;
			}
			k = isGameOver(gstate);
			if (k == 1)
				printf("test failed\n");
			else
				printf("test passed\n");
		}
	}
	return 0;
}