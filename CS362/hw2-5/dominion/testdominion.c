#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"
int Kings [20] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, 
				 minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};

const char *named[20] = {"adventurer", "council_room", 
			"feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward",
			"tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};
			
void randomizeKings(int kingCards[], FILE *Writer);
void printFiles(struct gameState *gameState, FILE *Writer);
char* cardSelect(int *currCard);


int main (int argc, char** argv) {
	struct gameState G;
	int kCards[10];					//The () initializes to NULL i believe
	FILE *Writer;
	int x;
	
  
	srand (time(NULL));											
	int players = rand() % 5;	
	int seeds = rand() % 9;
	if (seeds ==  0) { seeds = 1;   }					//No interactive seeding. 
	if (players < 2) { players = 2; }
  
	
	Writer = fopen("gameResults.out", "w");				//Open file with write permissions.

//	sscanf (argv[1],"%d",&num);

	printf ("Starting game with %d players. \n", players);
	fprintf (Writer,"Starting game with %d players. \n", players);
	fprintf (Writer,"With the following kingdom cards: \n");
	randomizeKings(kCards, Writer);	
for( x = 0; x < 10000; x++)
{	
	
	initializeGame(players, kCards, seeds, &G);
	

	int money = 0;
	int smithyPos = -1;
	int adventurerPos = -1;
	int i=0;
	int j=0;	
	
/* 	for(i = 0; i < players; i++)
	{
		shuffle(i, &G);			
	} */


	int numSmithies = 1;
	int numAdventurers = 0;

	while (!isGameOver(&G)) {
	
	int choice1 = rand() %25;
	int choice2 = rand() %25;
	int choice3 = rand() %25;
	
	
	money = 0;
	smithyPos = -1;
	adventurerPos = -1;
	for (i = 0; i < numHandCards(&G); i++) {
	  if (handCard(i, &G) == copper)
	money++;
	  else if (handCard(i, &G) == silver)
	money += 2;
	  else if (handCard(i, &G) == gold)
	money += 3;
	  else if (handCard(i, &G) == smithy)
	smithyPos = i;
	  else if (handCard(i, &G) == adventurer)
	adventurerPos = i;
	}

	if (whoseTurn(&G) == 0) {
	  if (smithyPos != -1) {
		printf("0: smithy played from position %d\n", smithyPos); 
	playCard(smithyPos, -1, -1, -1, &G); 
	printf("smithy played.\n");
	money = 0;
	i=0;
	while(i<numHandCards(&G)){
	  if (handCard(i, &G) == copper){
		playCard(i, -1, -1, -1, &G);
		money++;
	  }
	  else if (handCard(i, &G) == silver){
		playCard(i, -1, -1, -1, &G);
		money += 2;
	  }
	  else if (handCard(i, &G) == gold){
		playCard(i, -1, -1, -1, &G);
		money += 3;
	  }
	  

	  
	  
	  i++;
	}
	  }
	  
	cardEffect(feast, choice1, choice2, choice3, &G, 8, 0);
	 //playCard(feast, choice1, choice2, choice3, &G);

	  for(j=0; j < 27; j++)								//Kingdom cards!
	  {
		
			printf("playing card: %s \n", named[j - 7]); //to account for differences in array names
			playCard(Kings[j], choice1, choice2, choice3, &G);
			cardEffect(Kings[j], choice1, choice2, choice3, &G, 8, 0);
	  }	

	 	
	  money +=10; 			//make sure we have the money to play card for testing purposes
	  j = rand() % 10;				//get a random kingdom card!!
	  printf("%s ---<>>< \n", named[kCards[j] - 7]);
	  fprintf(Writer, "\n\n\t %s Kingdom card in play \n\n", named[kCards[j] - 7]);
	  buyCard(kCards[j], &G);

	  j = rand() % 10;				//get a random kingdom card!!
	  buyCard(kCards[j], &G);	  
	  if (money >= 8) {
//		printf("0: bought province\n"); 
		buyCard(province, &G);
	  }
	  else if (money >= 6) {
//		printf("0: bought gold\n"); 
		//buyCard(gold, &G);
	  }
	  else if ((money >= 4) && (numSmithies < 2)) {
//		printf("0: bought smithy\n"); 
		buyCard(smithy, &G);
		numSmithies++;
	  }
	  else if (money >= 3) {
//		printf("0: bought silver\n"); 
		//buyCard(silver, &G);
	  }

//	  printf("0: end turn\n");
	  endTurn(&G);
	}
	else {
	  if (adventurerPos != -1) {
		fprintf(Writer, " ADVENTURER PLAYED! %d\n", adventurerPos);

	
	playCard(adventurerPos, -1, -1, -1, &G); 
	money = 0;
	i=0;
	while(i<numHandCards(&G)){
	  if (handCard(i, &G) == copper){
		//playCard(i, -1, -1, -1, &G);
		//money++;         
	  }
	  else if (handCard(i, &G) == silver){
		//playCard(i, -1, -1, -1, &G);
		//money += 2;
	  }
	  else if (handCard(i, &G) == gold){
		//playCard(i, -1, -1, -1, &G);
		//money += 3;
	  }
	  i++;
	}
	  }

	  if (money >= 8) {
//		printf("1: bought province\n");
		buyCard(province, &G);
	  }
	  else if ((money >= 6) && (numAdventurers < 2)) {
//		printf("1: bought adventurer\n");
	buyCard(adventurer, &G);
	numAdventurers++;
	  }
//	  else if (money >= 6){
//		printf("1: bought gold\n");
//		buyCard(gold, &G);
//		}
	  else if (money >= 3){
//		printf("1: bought silver\n");
	//	buyCard(silver, &G);
	  }
//	  printf("1: endTurn\n");
//	  printf("segfault?");
	  
	  endTurn(&G);    
	  printFiles(&G , Writer);
	}
	} // end of While
	


	printf ("Finished game. If value = 0, that player probably was not playing. \nBelow are the scores: \n\n");

	printf ("Finished game. If value = 0, that player probably was not playing. \nBelow are the scores: \n\n");
	printf("THIS GAME WAS DESIGNED TO MAXIMIZE THE CHAOTIC INPUT OF KINGDOM CARDS \n");
	printf("IF IT SEGFAULTS JUST RUN IT AGAIN... it's chaotic yaknow? It was kept this way\n");
	printf("To examine possible outputs with many kingdom cards. Don't hate.\n");
	printf("Error checking for every possible conflict between cards would require an extensive period of time\n");
	
	for(i = 0; i < players; i++)
	{
	printf ("Player %d: %d\n", i, scoreFor(i, &G));
	fprintf (Writer,"Player %d: %d\n", i, scoreFor(i, &G));
	}
}
	return 0;


}

void randomizeKings(int kingCards[], FILE *Writer)
{
	int i, r;
	int cardsPossible [20] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, 
				 minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
								
	const char *names[20] = {"adventurer", "council_room", 
			"feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward",
			"tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};	
	
	int checker [20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			
 /* initialize random seed: */
			
	
								//number between 0 - 19 inclusive.
	//players = (int) rand() % 5;							
	for(i = 0; i < 10; i++)
	{
		r = rand() % 20;
		
		if(checker[r] == 0)
		{													//check first, if not already taken then proceed.
			kingCards[i] = cardsPossible[r];
			fprintf(Writer,"%s,  ",names[r]);
//			printf("kingdom card: %d \n", kingCards[i]);
			checker[r] = 1;
			
		} else   
		{ 
			i--; 					// repeat until new card
		}
	
		
	}
//	printf("%s  \n",names[r]);
}




void printFiles(struct gameState *gameState, FILE *Writer){
  int plyr, crd;
  int currHand;
  int currDeck;
  int discardPile;
  fprintf(Writer,"\n\n----------game state--------\n\n");
  
  
  for (plyr = 0; plyr < gameState->numPlayers; plyr++){
		fprintf(Writer, "\tplayer %d handcount: %d \n", plyr + 1, numHandCards(gameState));
		fprintf(Writer, "\tPlayer %d Hand: ", plyr + 1);			//print out players hand
		for (crd = 0; crd < gameState->handCount[plyr]; crd++){
			currHand = gameState->hand[plyr][crd];
			fprintf(Writer, " %s", cardSelect(&currHand));			//issues printing currhand....
		}
	
		fprintf(Writer, "\n\t\tDeck: ");	
		for (crd = 0; crd < gameState->deckCount[plyr]; crd++){				//print out deck count
			currDeck = gameState->deck[plyr][crd];
		  fprintf(Writer, " %s", cardSelect(&currDeck));
		}
		
		
		
		fprintf(Writer, "\n\t\tDiscard: ");
		for (crd = 0; crd < gameState->discardCount[plyr]; crd++){			//print out discard pile count
			discardPile = gameState->discard[plyr][crd];					
			fprintf(Writer, " %s", cardSelect(&discardPile));
		}
		fprintf(Writer, "\n\n");
  }
  fprintf(Writer, "-----------NEXT!------------\n\n");
}


char* cardSelect(int *currCard)
{
	int q;
	char * errorMsg = "CARD NOT FOUND.";
	int cardsPossible [27] = {curse, estate, duchy, province, copper, gold, silver, adventurer, council_room, 
			feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward,
			tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
								
	char *names[27] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room", 
			"feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward",
			"tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};
	
	//printf("My card %d \n", *currCard);
	//printf("card %d,\t", cardsPossible[7]);
	for(q = 0; q < 27; q++)
	{
		
	//	printf("card %d,\t", cardsPossible[q]);
		if(*currCard == cardsPossible[q])
		{
			return names[q];
		}
	}

	return errorMsg;
}
