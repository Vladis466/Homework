#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "primes.h"
//Primes for eArreryone!!!
#define MAXBYTES 1000000






/*

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
*/
struct primeArr *crinit_primeArr(long t)
{
	struct primeArr *a = malloc(sizeof(struct primeArr));
	a->num = malloc(sizeof(char) * t);
	a->mask = malloc(sizeof(char) * t/4);
	if(a->num == NULL)
	{
	printf("malloc failed\n");
	}
	
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
	
// 	if(Arr->num != 0){
//		free(Arr->num); 	
//		Arr->num = NULL;   	
//	}
//	free(Arr); 
}

//I need a bit arr
//int bmask(long index, char *bitMask)

void IgnorePts(struct primeArr *Arr)
{
	long j = 0;
	long k;	
	Arr->num[0] = 1;
	if(Arr->num[j]){
	printf(" ERROR? \n\n");
		for(j = 2; j <= sqrt(Arr->capacity); j++){
			for(k = 2 * j; k <= Arr->capacity; k += j){				
				Arr->num[k-1] = 1;
			}
		}
	}
}


//Used to map my primes initially to create file I would later use.
void mapPrimes(char *bitArr, long Count)
{
	
	FILE *fp;
	int i = 0;
	int j = 0;
	
	//Create size of array for map to file. Add 1 more if uneven.
	Count = Count / 4;
	if (Count % 4 > 0) { Count++;}
	char *myPrimes = malloc(sizeof(char) * Count);
	printf("%ld\n", Count);
	
	while(j < Count)
	{
		//cancel out everything except binary ones
		myPrimes[j] = 0xFF & bitArr[i];
		//Shift over and repeat process with next number.
		myPrimes[j] = myPrimes[j] << 2;
		myPrimes[j] = myPrimes[j] ^ bitArr[i+1];
		myPrimes[j] = myPrimes[j] << 2;
		myPrimes[j] = myPrimes[j] ^ bitArr[i+2];
		myPrimes[j] = myPrimes[j] << 2;
		myPrimes[j] = myPrimes[j] ^ bitArr[i+3]; 
			
		i = i + 4;
		j++;
	}
	
	fp = fopen("bitMap", "w");
	
	fwrite(myPrimes, sizeof(myPrimes[0]), Count, fp);
	
	 
	fclose(fp);

}

