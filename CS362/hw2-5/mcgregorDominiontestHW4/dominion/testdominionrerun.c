// reruns a game from gameResults.out, produced from testdominion.c
// allows testing with different implementations of dominion.c


#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "testdominionrerun.h"
#include "dominion.h"
#include "dominion_helpers.h"


#define GAME_RESULTS "gameResults.out"
#define ALT_GAME_RESULTS "gameResultsRerun.out"
#define PERMISSIONS S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
#define BUFFSIZE 1000


struct gameState gs;
FILE* rfs;
int wfd;
int k[10];
int success;


int main(int argc, char** argv) {
	int numPlayers;
	char s[BUFFSIZE];
	char s2[10];
	int win[MAX_PLAYERS];
	int player;
	int seed;
	int result;
	int i;
	
	success = 1;
	if ((rfs = fopen(GAME_RESULTS, "r")) == NULL) {
		printf("could not open %s\n", GAME_RESULTS);
		exit(1);
	}
	if ((wfd = creat(ALT_GAME_RESULTS, PERMISSIONS)) == -1) {
		printf("could not open %s\n", ALT_GAME_RESULTS);
		exit(1);
	}
	
	// setup
	fgets(s, BUFFSIZE, rfs);
	write(wfd, s, strlen(s));
	numPlayers = (int) strtol(s, (char**) NULL, 10);
	fgets(s, BUFFSIZE, rfs);
	write(wfd, s, strlen(s));
	seed = (int) strtol(s, (char**) NULL, 10);
	fgets(s, BUFFSIZE, rfs);
	write(wfd, s, strlen(s));
	k[0] = (int) strtol(strtok(s, ","), (char**) NULL, 10);
	for (i = 1; i < 10; i++) {
		k[i] = (int) strtol(strtok(NULL, ","), (char**) NULL, 10);
	}
	result = initializeGame(numPlayers, k, seed, &gs);
	if (result == -1) {
		printf("initializeGame returned -1\n");
		exit(1);
	}

	// play game
	player = 0;
	while(1) {
		if (gs.whoseTurn != player) {
			success = 0;
			printf("wrong turn, expected %d, found %d\n",
				player, gs.whoseTurn);
			player = gs.whoseTurn;
		}
		fgets(s, BUFFSIZE, rfs);
		if (s[0] == '*')
			break;
		sprintf(s, "> player %d:\n", player);
		write(wfd, s, strlen(s));
		act(s);
		write(wfd, "a\n", 2);
		buy(s);
		write(wfd, "b\n", 2);
		if (isGameOver(&gs))
			break;
		if (gs.outpostPlayed) {
			if (gs.whoseTurn != player) {
				success = 0;
				printf("wrong turn after outpost, expected %d, found %d\n",
					player, gs.whoseTurn);
				player = gs.whoseTurn;
			}
			fgets(s, BUFFSIZE, rfs);
			if (s[0] == '*')
				break;
			sprintf(s, "> outpost:\n");
			write(wfd, s, strlen(s));
			act(s);
			write(wfd, "a\n", 2);
			buy(s);
			write(wfd, "b\n", 2);
			if (isGameOver(&gs))
				break;
		}
		
		endTurn(&gs);
		player = (player + 1) % numPlayers;
	}

	// end game
	if (isGameOver(&gs)) {
		getWinners(win, &gs);
		sprintf(s, "* ");
	} else {
		getWinners(win, &gs);
		sprintf(s, "game is not over ");
	}
	for (i = 0; i < gs.numPlayers; i++) {
		if (win[i]) {
			sprintf(s2, "%d,", i);
			strcat(s, s2);
		}
	}
	s[strlen(s)-1] = '\n';
	write(wfd, s, strlen(s));
	fclose(rfs);
	close(wfd);
	
	if (success)
		printf("success\n");
	
	return 0;
}


void act(char *s) {
	int handPos;
	int choice1, choice2, choice3;
	int result;
	
	fgets(s, BUFFSIZE, rfs);
	while(strcmp(s, "a\n")) { // line is not "a\n"
		strtok(s, " ");
		handPos = (int) strtol(strtok(NULL, ","), (char**) NULL, 10);
		choice1 = (int) strtol(strtok(NULL, ","), (char**) NULL, 10);
		choice2 = (int) strtol(strtok(NULL, ","), (char**) NULL, 10);
		choice3 = (int) strtol(strtok(NULL, ","), (char**) NULL, 10);
		
		result = playCard(handPos, choice1, choice2, choice3, &gs);
		if (result == -1) {
			success = 0;
			printf("playCard returned -1:\nhandPos=%d\ncard=%d\nchoice1=%d\nchoice2=%d\nchoice3=%d\n",
				handPos, gs.hand[gs.whoseTurn][handPos], choice1, choice2, choice3);
		}
		sprintf(s, "A %d,%d,%d,%d\n", handPos, choice1,
			choice2, choice3);
		write(wfd, s, strlen(s));
		fgets(s, BUFFSIZE, rfs);
	} // line is "a\n"
}


void buy(char *s) {
	int i;
	int choice;
	int result;
	
	//updateCoins(&gs, bonus);
	fgets(s, BUFFSIZE, rfs);
	while (strcmp(s, "b\n")) { // line is not "b\n"
		for (i = 2; i < strlen(s); i++) {
			s[i-2] = s[i];
		}
		s[i-2] = '\0';
		choice = (int) strtol(s, (char**) NULL, 10);
		sprintf(s, "B %d\n", choice);
		write(wfd, s, strlen(s));
		result = buyCard(choice, &gs);
		if (result == -1) {
			success = 0;
			printf("buyCard returned -1:\nchoice=%d\n", choice);
		}
		fgets(s, BUFFSIZE, rfs);
	} // line is "b\n"
}
