#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
//kingdomCards
int main()
{
	int i, j;
	int* k;
	int* A = malloc(sizeof(int)*10);
	SelectStream(2);
	PutSeed(3);
	for (j = 0; j < 10; j++)
		A[j] = (int)(Random()*100);
	k = kingdomCards(A[0],A[1],A[2],A[3],A[4],A[5],A[6],A[7],A[8],A[9]);
	assert (k != NULL);
	for ( i = 0; i < 10; i++)
	{
		if (k[i] != A[i])
			printf("test failed\n");
		else
			printf("test passed\n");
	}
	free(A);
	return 0;
}