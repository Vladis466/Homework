#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

int testdominion(struct gameState *gstate);					//plays through a game of dominion
int get_actioncard(int player, struct gameState *gstate); 	//gets position of a random action card in player hand
int get_supplycard(struct gameState *gstate); 				//gets enum of a random supply card available for purchase
char *getcardname(int n); 									//returns a *char containing the name of a given card enum
int print_gamestate(struct gameState *gstate);				//prints the state of the gameand player hands

int main()
{
	printf("\n");
	//srand(time(NULL));
	struct gameState newgame;
	int player_count = (rand() % (MAX_PLAYERS - 1)) + 2;
	//int i, j, t;
	//int k[10];
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
	//int l[20] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
	//				village, baron, great_hall, minion, steward, tribute, ambassador,
	//				cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
	/*for(i = 0; i < 20; i++)
	{
		t = rand() % 20;
		j = l[t];
		l[t] = l[i];
		l[i] = j;
	}*/
	//for(i = 0; i < 10; i++){k[i] = l[i];}
	if(initializeGame(player_count, k, rand(), &newgame) == -1)
	{
		printf("\nERROR: Initialize game failed.");
		return -1;
	}
	if(testdominion(&newgame) == -1)
	{
		printf("\nERROR: Test game failed.");
		return -1;
	}
	return 0;
}

int testdominion(struct gameState *gstate)
{
	int player, test, i;
	int playercount = gstate->numPlayers;
	int roundcount = 0;
	int playerturn[playercount];
	int round_finished = 0;
	int turn_finished = 0;
	int round_flag = 0;
	for(i = 0; i < playercount; i++){playerturn[i] = 0;}
	while(isGameOver(gstate) == 0)
	{
		roundcount++;
		printf("\nStarting Round %d\n", roundcount);
		round_flag = 0;
		round_finished = 0;
		while(round_finished == 0)
		{
			print_gamestate(gstate);
			player = gstate->whoseTurn;
			playerturn[player]++;
			printf("\nStarting Player %d's turn #%d\n", player + 1, playerturn[player]);
			turn_finished = 0;
			while(turn_finished == 0)
			{
				while(gstate->numBuys > 0 && gstate->coins > 0)
				{
					if(buyCard(get_supplycard(gstate), gstate) == -1)
					{
						printf("\nERROR: buyCard() failed.\n");
					}
					gstate->phase = 0;
					if(gstate->numActions > 0)
					{
						test = get_actioncard(player, gstate);
						if(test == -1)
						{
							printf("No action cards in hand.\n");
						}
						else if(playCard(test, rand() % 2, rand() % 2, rand() % 2, gstate) == -1)
						{
							printf("ERROR: playCard() failed.\n");
						}
					}
				}
				if(endTurn(gstate) == -1)
				{
					printf("\nERROR: endTurn() failed.\n");
				}
				else
				{
					turn_finished = 1;
				}
			}
			print_gamestate(gstate);
			printf("Ending Player %d's turn #%d\n", player + 1, playerturn[player]);
			if(whoseTurn(gstate) == 0 && round_flag == 1)
			{
				round_finished = 1;
			}
			if(round_flag == 0){round_flag = 1;}
		}
		printf("\nFinished Round %d\n", roundcount);
	}
	printf("\nGame Finished\n");
	return 0;
}

int get_actioncard(int player, struct gameState *gstate)
{
	printf("Selecting card for action...\n");
	int i;
	int hand_count = gstate->handCount[player];
	int action_card_count = 0;
	int action_card_pos[hand_count];
	int action_card_rand;
	int temp;
	//printf("hand count = %d\n", hand_count);
	for(i = 0; i < hand_count; i++)
	{
		//printf("get_actioncard_loop i = %d\n", i);
		temp = gstate->hand[player][i];
		if(temp >= adventurer && temp <= treasure_map)
		{
			action_card_pos[action_card_count] = i;
			action_card_count++;
		}
	}
	//printf("action_card_count = %d\n", action_card_count);
	if(action_card_count == 0){return -1;}
	action_card_rand = action_card_pos[rand() % action_card_count];
	printf("Card selected for action: %s\n", getcardname(gstate->hand[player][action_card_rand]));
	return action_card_rand;
}

int get_supplycard(struct gameState *gstate)
{
	printf("Selecting card for purchase...\n");
	int i;
	int supply_card_count = 0; //number of acceptable supply card options
	int supply_card_pos[27]; //array of acceptable supply cards in total supply
	int supply_card_rand; //randomly selected card from set of acceptable supply cards
	for(i = 0; i < 27; i++)
	{
		if(getCost(i) <= gstate->coins && supplyCount(i, gstate) > 0)
		{
			supply_card_pos[supply_card_count] = i;
			supply_card_count++;
		}
	}
	supply_card_rand = supply_card_pos[rand() % supply_card_count];
	printf("Card selected for purchase: %s\n", getcardname(supply_card_rand));
	return supply_card_rand;
}

char *getcardname(int n)
{
	switch(n)
	{
		case curse:
			return "curse";
		case estate:
			return "estate";
		case duchy:
			return "duchy";
		case province:
			return "province"; 
		case copper:
			return "copper";
		case silver:
			return "silver";
		case gold:
			return "gold";
		case adventurer:
			return "adventurer";
		case council_room:
			return "council_room";
		case feast:
			return "feast";
		case gardens:
			return "gardens";
		case mine:
			return "mine";
		case remodel:
			return "remodel";
		case smithy:
			return "smithy";
		case village:
			return "village";
		case baron:
			return "baron"; 
		case great_hall:
			return "great_hall";
		case minion:
			return "minion";
		case steward:
			return "steward";
		case tribute:
			return "tribute";
		case ambassador:
			return "ambassador";
		case cutpurse:
			return "cutpurse";
		case embargo:
			return "embargo";
		case outpost:
			return "outpost";
		case salvager:
			return "salvager";
		case sea_hag:
			return "sea_hag";
		case treasure_map:
			return "treasure_map";
		default:
			return "CARD NOT FOUND";
	}
}

int print_gamestate(struct gameState *gstate)
{
	int i, j;
	printf("\nGame State:\n");
	printf("Number of Players: %d\n", gstate->numPlayers);
	//printf("Buys: %d\n", gstate->numBuys);
	//printf("Actions: %d\n", gstate->numActions);
	//printf("Outpost Played: %d\n", gstate->outpostPlayed);
	//printf("Outpost Turn: %d\n", gstate->outpostTurn);
	printf("Whose Turn: %d\n", gstate->whoseTurn + 1);
	//printf("Phase: %d\n", gstate->phase);
	printf("Coins: %d\n", gstate->coins);
	//printf("Played Card Count: %d\n", gstate->playedCardCount);
	printf("\n");
	for(i = 0; i < gstate->numPlayers; i++)
	{	
		printf("Player %d has the following in his hand:\n", i + 1);
		for(j = 0; j < gstate->handCount[i]; j++)
		{
			printf("%s ", getcardname(gstate->hand[i][j]));
		}
		printf("\n");
		printf("Player %d has the following in his deck:\n", i + 1);
		for(j = 0; j < gstate->deckCount[i]; j++)
		{
			printf("%s ", getcardname(gstate->deck[i][j]));
		}
		printf("\n");
		printf("Player %d has the following in his discard pile:\n", i + 1);
		for(j = 0; j < gstate->discardCount[i]; j++)
		{
			printf("%s ", getcardname(gstate->discard[i][j]));
		}
		printf("\n");
	}
	
	
	return 0;
}


