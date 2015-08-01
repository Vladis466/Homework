#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "primes.h"
//Primes for eArreryone!!!









/* int main()
{
	int n = 0;
	printf("Please enter the max number to search through for primes: ---->    ");
	scanf("%d", &n);
	
		struct primeArr *primeArray = crinit_primeArr(n);
		IgnorePts(primeArray);
		p_primeArr(primeArray);
	
	
	return 0;
} */

struct primeArr *crinit_primeArr(long t)
{
	struct primeArr *a = malloc(sizeof(struct primeArr));
	a->num = malloc(sizeof(unsigned int) * t);
	//a->list = malloc(sizeof(int) * t);
	a->capacity = t;
	a->num_of_primes = 0;
	return a;
}



void p_primeArr(struct primeArr *Arr)
{
	int i;
	int n = 0;
	for(i = 0; i < Arr->capacity; i++){
		if(Arr->num[i] == 0){
			//Arr->list[n] = i+1;
			//printf(" %d \n",(int) Arr->list[n]);
			Arr->num_of_primes++;
			n++;
		}
	}
	
/* 	if(Arr->num != 0){
		free(Arr->num); 	
		Arr->num = NULL;   	
	}
	free(Arr); */
}



void IgnorePts(struct primeArr *Arr){
	long j = 0;
	long k;	
	Arr->num[0] = 1;
	if(Arr->num[j]){
//	printf(" ERROR? \n\n");
		for(j = 2; j <= sqrt(Arr->capacity); j++){
			for(k = 2 * j; k <= Arr->capacity; k += j){				
				Arr->num[k-1] = 1;
			}
		}
	}
}



