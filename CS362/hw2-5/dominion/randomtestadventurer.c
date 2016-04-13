#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"
#include <time.h>
//testing card adventurer using RANDOM testing.
//Reveal cards from your deck until you get two treasure cards. put all revealed cards
// in the discard pile and those two treasure cards in your hand.

int main(int argc, char** argv){
	int j = 0;
//	int testVal = 0;
	struct gameState myGame;
    int card = adventurer; 
	int currPlay = 0;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int players = 0;
	int handPos = 0;
	int* Bonus = 0;
	int carded, index, coinage = 0;
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};	
		   
	srand(time(NULL));
//	int r = rand() % 20;
	//players = (int) rand() % 5;
	if(players < 2){ players = 2; }   //Setting our rand amount of players.
	
	
	for (j = 1; j < 10000; j++){ 
		for(currPlay = 0; currPlay < players; currPlay++){
			initializeGame(players, k, j, &myGame); 
			coinage = 0;									//reset coin counter

//Randomize the player's stats.		
			myGame.deckCount[currPlay] = (int) rand() % 501;
		    myGame.discardCount[currPlay] = (int) rand() % 401;
			myGame.handCount[currPlay] = (int) rand() % 111;
			myGame.playedCardCount = (int) rand() % 301;
			
			for(index = 0; index < myGame.handCount[currPlay]; index++)
			{
				carded = myGame.hand[currPlay][index];
				switch(carded) {
				case copper: coinage += 1;
				  break;
				case silver: coinage += 2;
				  break;
				case gold: coinage += 3;
				  break;
			
				}
			}
			int oldCoins = coinage;				//weird error

			if (oldCoins == 0) { break; }
			cardEffect(card, choice1, choice2, choice3, &myGame, handPos, Bonus);
			
			coinage = 0;									//reset coin counter
			for(index = 0; index < myGame.handCount[currPlay]; index++)
			{
				carded = myGame.hand[currPlay][index];
				switch(carded) {
				case copper: coinage += 1;
				  break;
				case silver: coinage += 2;
				  break;
				case gold: coinage += 3;
				  break;
			
				}
			}
	//		printf("%d ---",  oldCoins);			
	//		printf("%d   ----", index);
	//		printf("%d \n",  coinage);
			
			
			
			if(coinage < oldCoins + 1 || coinage > oldCoins + 7)		//Make sure the amout of coins added is within the bounds
			printf("error, adventurer not working\n");
			
			
			
			
			
			
			
			
			
			
		}
			
	}	
	printf("If no error messages were seen then the adventurer card is being played correctly.  \n");
	
	return 0;
}