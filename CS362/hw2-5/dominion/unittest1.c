#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"


int main(){
	int i = 0;
	struct gameState game;


	for (i = 0; i < 4; i++){
		game.whoseTurn = i;
		if (whoseTurn(&game) != i)
		{
			printf("player %d is out of turn in the game.\n", i + 1);
		
		} else 
		{
			printf("player %d is in the correct turn order.\n", i + 1);
		}
	}
	return 0;
}

 