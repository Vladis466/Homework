/*
*	Assignment 4 CS 344 Summer 2015
*	Implement a threaded and multiple process/shared memory version
*	of a prime number finding algorithm. 
*	Then compare them
*/

#define _POSIX_C_SOURCE 200809L
#define _BSD_SOURCE
#define NUM_THREADS 1
#define VEC_LEN 1000000
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
	int *a;
	int *b;
	int len;
	
	int offset;
	int sliceSt;
	int sliceEnd;
	long *myList;
};

pthread_t threads[NUM_THREADS];

pthread_mutex_t mutex_sum;
double sum;

void *dot(void *arg)
{
	int i;
	int start;
	int end;

	
	

	struct data *d = (struct data*) arg;

	
	printf("I'm thread #%d, and I'm starting up.\n", d->offset);
	
	pthread_mutex_lock(&mutex_sum);
	for(i = 0; i < 8; i++){  						//Check to see primes saved
//	printf("\n%ld <-----NUMBER \n\n", primeArray->list[i]);
//	printf("%d <-----NUMBER\n", (int)d->myList[i]);
	}

	printf("%d start: \n", d->sliceSt);
	printf("%d end: \n", d->sliceEnd);
	for(i = d->sliceSt; i < d->sliceEnd; i++);
	{
		printf("%d prime: \n\n", (int) d->myList[i]);
	}
	

	pthread_mutex_unlock(&mutex_sum);
	
	pthread_exit((void*) 0);
}





int main(int argc, char **argv)
{
	int *a = (int*)malloc(NUM_THREADS * VEC_LEN * sizeof(int));
	int *b = (int*)malloc(NUM_THREADS * VEC_LEN * sizeof(int));
	int i;
	int Inpt= 0;
	int rem = 0;
	struct data d[NUM_THREADS];
	struct primeArr *primeArray;
	pthread_attr_t attr;

	printf("Please enter the max integer to search through for primes: ---->    ");
	scanf("%d",&Inpt);
	
	primeArray = crinit_primeArr(Inpt);					//Find the primes
	IgnorePts(primeArray);
	p_primeArr(primeArray);

	for(i=0; i<NUM_THREADS; ++i)
	{	
		d[i].myList = primeArray->list;			//copy over the list of primes into our struct
		
	}
	
	//shmemmount??
	//bitwise operators

	for(i = 0; i < primeArray->num_of_primes; i++){  						//Check to see primes saved
//	printf("\n%d <-----NUMBER \t", (int)primeArray->list[i]);
//	printf("\n%d <-----NUMBER \n", (int) d->myList[i]);
	}
	
	printf("\n\n\n\n%d <-----NUMBER OF PRIMES \n\n", primeArray->num_of_primes);
	rem = primeArray->num_of_primes % NUM_THREADS;		//get the remainder to add to the last thread

	Inpt = primeArray->num_of_primes / NUM_THREADS;							//iteration bounds
	
	for(i=0; i<VEC_LEN * NUM_THREADS; ++i)
	{
		a[i] = 1.0;
		b[i] = 1.0;
	}

	sum = 0.0;

	pthread_mutex_init(&mutex_sum, NULL);

	pthread_attr_init(&attr);

	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	printf(" ERROR? \n\n");
	
	for(i=0; i<NUM_THREADS; ++i)
	{
		d[i].a = a;
		d[i].b = b;
		d[i].len = VEC_LEN;
		d[i].offset = i;
		d[i].sliceSt = (Inpt * i);										
		d[i].sliceEnd = Inpt * (i + 1); 
		if(i == NUM_THREADS - 1)
		{
			d[i].sliceEnd = d[i].sliceEnd + rem;
		}
		pthread_create(&threads[i], &attr, dot, (void*)&d[i]);
		
	}

		for(i=0; i<10; i++)
	{
		//printf("%d prime!!: \n\n",(int) d->myList[i]);
	}
	
	pthread_attr_destroy(&attr);

	for(i=0; i<NUM_THREADS; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	printf("Sum is %f\n", sum);

	free(a);
	free(b);

	pthread_mutex_destroy(&mutex_sum);
	

	
	return EXIT_SUCCESS;
}








/*
//void Sections(startNum,ntrvl);
void *busy(void *threadid);

int main(int argc, char *argv[])
{
	int Inpt;
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;
	struct arg_struct *terms;
	terms = malloc(sizeof(struct arg_struct));
	(*terms).numSize = 0;
	printf("Please enter the max number to search through for primes: ---->    ");
	scanf("%d",Inpt);
	
	
	(*terms).numSize = Inpt;
printf("I'm thread and I'm starting up.\n");
	for(t=0; t<NUM_THREADS; t++){
		printf("Creating thread %ld\n", t);
		(*terms).ti = t;
		rc = pthread_create(&threads[t], NULL, busy, (void *)&terms);
		if (rc){
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(EXIT_FAILURE);
		}
	}
	
	for(t=0; t<NUM_THREADS; t++){
		pthread_join(threads[t], (void**)NULL);
	}


	// The last thing; clean-up
	pthread_exit(NULL);
	
	
	
}


void *busy(void *termStruct)
{
	long tid;
	struct arg_struct *myTerms = (struct arg_struct*)termStruct;
	
	tid = (long)(*myTerms).ti;
	
	
	printf("I'm thread #%ld, and I'm starting up.\n", tid);

	struct primeArr *primeArray; 
	primeArray = crinit_primeArr((*myTerms).numSize);
	IgnorePts(primeArray);
	p_primeArr(primeArray);
//	pthread_exit(0); 
	pthread_exit(NULL);
}

void Sections(startNum,ntrvl )
{


}

*/

