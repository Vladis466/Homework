/*
*	Assignment 4 CS 344 Summer 2015
*	Implement a threaded and multiple process/shared memory version
*	of a prime number finding algorithm. 
*	Then compare them
*/

#define _POSIX_C_SOURCE 200809L
#define _BSD_SOURCE
#define NUM_THREADS 1
#define CharSPACE 1073741824
#define VEC_LEN 1000000
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

#define BITMASK(b) (1 << ((b) % CHAR_BIT))
#define BITSLOT(b) ((b) / CHAR_BIT)
#define BITSET(a, b) ((a)[BITSLOT(b)] |= BITMASK(b))
#define BITCLEAR(a, b) ((a)[BITSLOT(b)] &= ~BITMASK(b))
#define BITTEST(a, b) ((a)[BITSLOT(b)] & BITMASK(b))
#define BITNSLOTS(nb) ((nb + CHAR_BIT - 1) / CHAR_BIT)


#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <math.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>


#include <pthread.h>
#include "primes.h"
/*
*	Divide number into 'threads' parts using modulus 
*	Add them up to create start and end of each section.
*	throw that number into each thread
*	if its the last thread, add the remainder before throwage
*
*
*
*
*
*
*/


struct data
{

	int offset;
	int sliceSt;
	int sliceEnd;
	char *myList;
	
};

struct data d[NUM_THREADS];
pthread_t threads[NUM_THREADS];
pthread_mutex_t mutex_sum;
char List[CharSPACE];

void mapPrimes(long *bitArr, long Count);

int happyOrsad(unsigned int Number)
{

	return 1;
}

void mapReader(char singleBit, int Num)
{
	//Max index point
	unsigned int Index = Num * 4 + 3;						//Keep track of what number were on.
	char temp;
	int j;
	
	//for the specified bit (4 nums), copy it over
	//Iterate through it.
	//If a number is prime, increment the counter
	//Check if that number is happy or sad
	//set specification and feed back into the char array.

	//First	
		
	temp = singleBit;
	//Check if it is prime
	//If it is prime, check the index for happy and sad.
	for (j = 0; j < 8; j = j + 2){
		if(!CHECK_BIT(temp, j))
			{
				printf("Prime Found\n");
				//If returns 1(happy), else sad;
				if(happyOrsad(Index))
				{
					
					
				} else
				{
			} else
			{
				printf("prime not found\n");
			}
		//We go down the index because our list is backwards.
		Index--;
		
	}
	
	FILE *fp;
	fp = fopen("premDs", "w");
	
	fwrite(&temp, sizeof(singleBit), sizeof(singleBit)/sizeof(singleBit), fp);		


}
void *dot(void *arg)
{
	FILE *fp;
	int i;
	
	
	
	struct data *d = (struct data*) arg;
	
	
	
	printf("I'm thread #%d, and I'm starting up.\n", d->offset);	
		
	pthread_mutex_lock(&mutex_sum);

	printf("%d start: \n", d->sliceSt);
	printf("%d end: \n", d->sliceEnd);
	//for(i = d->sliceSt; i < d->sliceEnd; i++);
	//{
	mapReader(List[0], i); 
	//}
	
	fp = fopen("Checker", "w");
	fwrite(List, 1, 1, fp);	
	
	pthread_mutex_unlock(&mutex_sum);
	
	pthread_exit((void*) 0);
}








int main(int argc, char **argv)
{
	FILE *fp; 
	int i;
	int numBytes;
	long Inpt= 0;
	int rem = 0;
	struct primeArr *primeArray;
	pthread_attr_t attr;

	printf("Please enter the max integer to search through for primes: ---->    ");
	scanf("%ld",&Inpt);

	//Used this function to initially get my numbers into a BITMAP
	//primeArray = crinit_primeArr(Inpt);
	//IgnorePts(primeArray);
	//p_primeArr(primeArray);
	//mapPrimes(primeArray->num, Inpt);
	
	pthread_mutex_init(&mutex_sum, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	//The number of bytes we want to pull in 
	numBytes = Inpt / 4; 							//4 numbers are kept per char.
	if (numBytes % 4 > 0) { numBytes++;}

	char myPrimes[numBytes];						//So we get an array of that many chars(x4 numbers)
	
	fp = fopen("bitMap", "r");
	printf("ERROR\n");
	fread(List, sizeof(myPrimes[0]), sizeof(myPrimes)/sizeof(myPrimes[0]), fp );
	printf("ERROR\n");	
	Inpt = numBytes / NUM_THREADS;
	rem = numBytes % NUM_THREADS;

	
	
	
	
	for(i=0; i<NUM_THREADS; ++i)
	{
		int j = 0;
		int k = 0;
		d[i].offset = i;
		d[i].sliceSt = (Inpt * i);										
		d[i].sliceEnd = Inpt * (i + 1);
		
		if(i == NUM_THREADS - 1)
		{
			d[i].sliceEnd = d[i].sliceEnd + rem;
		}
		pthread_create(&threads[i], &attr, dot, (void*)&d[i]);
		
	}	
	

	pthread_attr_destroy(&attr);

	for(i=0; i<NUM_THREADS; ++i)
	{
		pthread_join(threads[i], NULL);
	}





	pthread_mutex_destroy(&mutex_sum);
	

	
	return EXIT_SUCCESS;
}






//Used to map my primes initially to create file I would later use.
void mapPrimes(long *bitArr, long Count)
{
	
	FILE *fp;
	int i = 0;
	int j = 0;
	
	//Create size of array for map to file. Add 1 more if uneven.
	Count = Count / 4;
	if (Count % 4 > 0) { Count++;}
	char myPrimes[Count];
	
	//
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
	
	fwrite(myPrimes, sizeof(myPrimes[0]), sizeof(myPrimes)/sizeof(myPrimes[0]), fp);
	
	 
	fclose(fp);

}