#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"
#include <time.h> 
    //gain card with cost up to 5
    //Backup hand

int main()
{
	int j = 0;
	int trigger = 0;
//	int testVal = 0;
	struct gameState state;
    int card = salvager; 
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int players = 0;
	int handPos = 0;
	int* Bonus = 0;
	int oldCount = 0;
	int currPlay = 0;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};	
		   
	srand(time(NULL));
//	int r = rand() % 20;
	players = (int) rand() % 5;
	if(players < 2){ players = 2; }   //Setting our rand amount of players.
	
	int Coins = 4;
	
	
	
	for (j = 1; j < 100; j++){ 
		for(currPlay = 0; currPlay < players; currPlay++){
			initializeGame(players, k, j, &state); 
	int i = 0;
	
	int temphand[5] = {5, 4, 3, 4, 5};
	int choiceCost = 5;
	
    for (i = 0; i <= 5; i++){
	temphand[i] = rand() % 6;//Backup card
	
	
	//state->hand[currentPlayer][i] = -1;//Set to nothing
      }
      //Backup hand

      //Update Coins for Buy
      //updateCoins(currentPlayer, state, 5);
	  Coins = 4;
      int x = 1;//Condition to loop on
      while( x == 1) {//Buy one card
	if (Coins <= 0){
	  if (DEBUG)
	    printf("None of that card left, sorry!\n");

	  if (DEBUG){
	    printf("Cards Left: %d\n",  temphand[i]);
	  }
	}
	else if (Coins < choiceCost){
	  printf("That card is too expensive!\n");

/*	  if (DEBUG){
	    printf("Coins: %d < %d\n", state->coins, getCost(choice1));
	  }
	}
	else{

	  if (DEBUG){
	    printf("Deck Count: %d\n", state->handCount[currentPlayer] + state->deckCount[currentPlayer] + state->discardCount[currentPlayer]);
	  }

	  gainCard(choice1, state, 0, currentPlayer);//Gain the card
	  x = 0;//No more buying cards

	  if (DEBUG){
	    printf("Deck Count: %d\n", state->handCount[currentPlayer] + state->deckCount[currentPlayer] + state->discardCount[currentPlayer]);
*/	  }

	}
          

      //Reset Hand

      //Reset Hand
     }
		}
		
      return 0;
	  
}