#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//Primes for eArreryone!!!





struct primeArr *crinit_primeArr(int x);

void p_primeArr(struct primeArr *Arr);
void IgnorePts(struct primeArr *Arr);


struct primeArr
	{
		int *num;				
		int num_of_primes;			
		int capacity;				
	};

int main()
{
	int n = 0;
	printf("Please enter the max number to search through for primes: ---->    ");
	scanf("%d", &n);
	
		struct primeArr *primeArray = crinit_primeArr(n);
		IgnorePts(primeArray);
		p_primeArr(primeArray);
	
	
	return 0;
}

struct primeArr *crinit_primeArr(int t)
{
	struct primeArr *a = malloc(sizeof(struct primeArr));
	a->num = malloc(sizeof(int) * t);
	a->capacity = t;
	a->num_of_primes = 0;
	return a;
}



void p_primeArr(struct primeArr *Arr)
{
	int i;
	
	for(i = 0; i < Arr->capacity; i++){
		if(Arr->num[i] == 0){
			printf(" %d \n",i+1);
			Arr->num_of_primes++;
		}
	}
	
/* 	if(Arr->num != 0){
		free(Arr->num); 	
		Arr->num = NULL;   	
	}
	free(Arr); */
}



void IgnorePts(struct primeArr *Arr){
	int j = 0;
	int k;	
	Arr->num[0] = 1;

	if(Arr->num[j]){
		for(j = 2; j <= sqrt(Arr->capacity); j++){
			for(k = 2 * j; k <= Arr->capacity; k += j){
				Arr->num[k-1] = 1;
			}
		}
	}
}




/* int main(int argc, char* argArr[]){
	
	int primes = 0; int count = 2;		//start at greater than 1
	int max = 0; int i = 0;	//dummy count
	int primeList[100];
	
	pf("Hello enter the max number please. \n");
	scanf ("%d", &max);
	
	while(max != 0){
		while(count < max){
			if(max % count == 0)
			break;
			
			if(count + 1 == max){		//If our max is divisible by no number greater than 1 and we haArre reached itself
				primeList[primes] = max;		//save the prime
				primes++;				//Increase our number of primes	
			}
			count++;
		}
		max--;
		count = 2;
	}
	pf("List of primes. \n\n");
	while (i < primes)
	{
		pf("%d\n\n", primeList[i]);
		i++;
	}
	return 0;
} */
