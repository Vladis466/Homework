// randomly tests entire game of dominion.c


#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "testdominion.h"
#include "dominion.h"
#include "dominion_helpers.h"


#define GAME_RESULTS "gameResults.out"
#define PERMISSIONS S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH


int fd;
struct gameState gs;
int k[10];
int success;


int main(int argc, char** argv) {
	int numPlayers;
	char s[1000];
	char s2[10];
	int win[MAX_PLAYERS];
	int player;
	int seed;
	int result;
	int i;
	
	success = 1;
	srand(time(NULL));
	fd = creat(GAME_RESULTS, PERMISSIONS);
	getKingdomCards(k);
	numPlayers = rand() % 2 + 2;
	seed = rand();
	result = initializeGame(numPlayers, k, seed, &gs);
	if (result == -1) {
		printf("initialize game returned -1\n");
		exit(1);
	}
	
	sprintf(s, "%d\n%d\n", numPlayers, seed);
	for (i = 0; i < 9; i++) {
		sprintf(s2, "%d,", k[i]);
		strcat(s, s2);
	}
	sprintf(s2, "%d\n", k[9]);
	strcat(s, s2);
	write(fd, s, strlen(s));
	
	player = 0;
	while(1) {
		if (gs.whoseTurn != player) {
			success = 0;
			printf("wrong turn, expected %d, found %d\n",
				player, gs.whoseTurn);
			player = gs.whoseTurn;
		}
		sprintf(s, "> player %d:\n", player);
		write(fd, s, strlen(s));
		act();
		write(fd, "a\n", 2);
		buy();
		write(fd, "b\n", 2);
		if (isGameOver(&gs))
			break;
		if (gs.outpostPlayed) {
			if (gs.whoseTurn != player) {
				success = 0;
				printf("wrong turn after outpost, expected %d, found %d\n",
					player, gs.whoseTurn);
				player = gs.whoseTurn;
			}
			sprintf(s, "> outpost:\n");
			write(fd, s, strlen(s));
			act();
			write(fd, "a\n", 2);
			buy();
			write(fd, "b\n", 2);
			if (isGameOver(&gs))
				break;
		}
		
		endTurn(&gs);
		player = (player + 1) % numPlayers;
	}
	
	getWinners(win, &gs);
	sprintf(s, "* ");
	for (i = 0; i < gs.numPlayers; i++) {
		if (win[i]) {
			sprintf(s2, "%d,", i);
			strcat(s, s2);
		}
	}
	s[strlen(s)-1] = '\n';
	write(fd, s, strlen(s));
	close(fd);
	
	if (success)
		printf("success\n");
	
	return 0;
}


void getKingdomCards(int* k) {
	int tmp[10];
	int kStart;
	int kRange;
	int i;
	int j;
	
	kStart = adventurer;
	kRange = treasure_map - adventurer + 1;
	
	tmp[0] = rand() % kRange;
	k[0] = tmp[0] + kStart;
	
	for (i = 1; i < 10; i++) {
		tmp[i] = rand() % (kRange - i);
		for (j = 0; j < i; j++) {
			if (tmp[i] >= tmp[j]) {
				tmp[i]++;
			}
		}
		k[i] = tmp[i] + kStart;
		addToTmp(tmp, i);
	}
}


void addToTmp(int* tmp, int newIndex) {
	int i;
	int temp;
	
	i = newIndex - 1;
	temp = tmp[newIndex];
	while (i >= 0) {
		if (temp > tmp[i]) {
			tmp[i+1] = temp;
			return;
		}
		tmp[i+1] = tmp[i];
		--i;
	} // all current elements are above the new one
	tmp[0] = temp;
}

void act() {
	int i;
	int actCards;
	int which;
	int player;
	
	player = gs.whoseTurn;
	while (gs.numActions > 0) {
		actCards = 0;
		for (i = 0; i < gs.handCount[player]; i++) {
			if (gs.hand[player][i] >= adventurer &&
					gs.hand[player][i] <= treasure_map &&
					gs.hand[player][i] != gardens) {
				++actCards;
			}
		}
		
		if (actCards == 0)
			return;
		if ((rand() % (actCards*2)) == 0)
			return;
		
		which = rand() % actCards;
		for (i = 0; i < gs.handCount[player]; i++) {
			if (gs.hand[player][i] >= adventurer &&
					gs.hand[player][i] <= treasure_map &&
					gs.hand[player][i] != gardens) {
				if (which == 0) {
					testPlayCard(i);			
					break;
				} else {
					--which;
				}
			}
		}
	}
}


void testPlayCard(int handPos) {
	int card;
	int choice1, choice2, choice3;
	int i;
	int tmp;
	int which;
	int player;
	static char s[100];
	int result;
	
	card = gs.hand[gs.whoseTurn][handPos];
	player = gs.whoseTurn;
	choice1 = choice2 = choice3 = -1;
	switch(card) {
		case feast:
			while(1) {
				choice1 = rand() % 17;
				if (choice1 >= 7) {
					choice1 = k[choice1 - 7];
					if (gs.supplyCount[choice1] > 0 &&
							getCost(choice1) <= 5) {
						break;
					}
				} else if (gs.supplyCount[choice1] > 0 &&
						getCost(choice1) <= 5) {
					break;
				}
			}
			break;
		case mine:
			tmp = 0;
			for (i = 0; i < gs.handCount[player]; i++) {
				if (gs.hand[player][i] >= copper && gs.hand[player][i] <= gold) {
					++tmp;
				}
			}
			if (tmp == 0)
				return;
			which = rand() % tmp;
			for (i = 0; 1; i++) {
				if (gs.hand[player][i] >= copper && gs.hand[player][i] <= gold) {
					if (which == 0) {
						choice1 = i;
						break;
					} else {
						--which;
					}
				}
			}
			choice2 = copper + (rand() %
				(gs.hand[player][choice1] - copper + 1));
			break;
		case remodel:
			choice1 = (handPos+1+(rand()%(gs.handCount[player]-1))) %
				gs.handCount[player];
			while(1) {
				choice2 = rand() % 17;
				if (choice2 >= 7) {
					choice2 = k[choice2 - 7];
					if (gs.supplyCount[choice2] > 0 &&
							getCost(choice2) <=
							(2 + getCost(gs.hand[player][choice1]))) {
						break;
					}
				} else if (gs.supplyCount[choice2] > 0 &&
						getCost(choice2) <=
						(2 + getCost(gs.hand[player][choice1]))) {
					break;
				}
			}
			break;
		case baron:
			tmp = 0;
			for (i = 0; i < gs.handCount[player]; i++) {
				if (gs.hand[player][i] == estate) {
					tmp = 1;
					break;
				}
			}
			choice1 = tmp && (rand() % 2);
			break;
		case minion:
			choice1 = 1 + (rand() % 2);
			break;
		case steward:
			if (gs.handCount[player] >= 3) {
				choice1 = 1 + (rand() % 3);
				if (choice1 == 3) {
					choice2 = rand()%(gs.handCount[player]-1);
					if (choice2 >= handPos) {
						++choice2;
					}
					choice3 = rand() % (gs.handCount[player] - 2);
					if (choice3 >= handPos || choice3 >= choice2) {
						++choice3;
						if (choice3 >= handPos && choice3 >= choice2) {
							++choice3;
						}
					}
				}
			} else {
				choice1 = 1 + (rand() % 2);
			}
			break;
		case ambassador:
			choice1 = rand() % (gs.handCount[player]-1);
			if (choice1 >= handPos)
				++choice1;
			tmp = 0;
			for (i = 0; i < gs.handCount[player]; i++) {
				if (i != choice1 && gs.hand[player][i] ==
						gs.hand[player][choice1]) {
					tmp = 1;
					break;
				}
			}
			choice2 = rand() % (2 + tmp);
			break;
		case embargo:
			choice1 = rand() % 17;
			if (choice1 >= 7)
				choice1 = k[choice1 - 7];
			break;
		case salvager:
			choice1 = rand() % (gs.handCount[player] - 1);
			if (choice1 >= handPos)
				++choice1;
			break;
	}
	
	
	result = playCard(handPos, choice1, choice2, choice3, &gs);
	if (result == -1) {
			success = 0;
			printf("playCard returned -1:\nhandPos=%d\ncard=%d\nchoice1=%d\nchoice2=%d\nchoice3=%d\n",
				handPos, card, choice1, choice2, choice3);
	}	
	
	sprintf(s, "A %d,%d,%d,%d\n", handPos,
		choice1, choice2, choice3);
	write(fd, s, strlen(s));
}


void buy() {
	int choice;
	static char s[100];
	int result;
	
	//updateCoins(gs.whoseTurn, &gs, bonus);
	while (gs.numBuys > 0) {
		choice = rand() % 18;
		if (choice == 17)
			break;
		if (choice >= 7)
			choice = k[choice - 7];
		
		if (getCost(choice) <= gs.coins) {
			sprintf(s, "B %d\n", choice);
			write(fd, s, strlen(s));
			result = buyCard(choice, &gs);
			if (result == -1) {
				success = 0;
				printf("buyCard returned -1:\nchoice=%d\n", choice);
			}
		}
	}
}
