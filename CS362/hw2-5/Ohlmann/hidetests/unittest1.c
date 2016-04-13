#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//fulldeckcount
int main()
{
	struct gameState* gstate = malloc(sizeof(struct gameState));
	int cardno,cards;
	int i,j,k;
	cardno = 0;
	gstate->numPlayers = 4;
	SelectStream(2);
	PutSeed(3);
	cards = 0;
	for (i = 1; i <= 4; i++)
	{
		for(j = 0; j < 10; j++ )
		{
				gstate->discardCount[i-1]++;
				gstate->discard[i-1][j] = ((int)(Random()*100))%27;
				cardno++;
		}
		for(k = 0; k < 27; k++)
		{
			cards += fullDeckCount(i-1,k,gstate);
		}
		if (cardno != cards)
		{
			printf("test failed\n");
		}
		else
		{
			printf("test passed\n");
		}
		cardno = 0;
		cards = 0;
	}
	return 0;
}