/*
*	Assignment 4 CS 344 Summer 2015
*	Implement a threaded and multiple process/shared memory version
*	of a prime number finding algorithm. 
*	Then compare them
*/

#define _POSIX_C_SOURCE 200809L
#define _BSD_SOURCE
#define NUM_THR_PROC 2
#define CharSPACE 1073741824
#define VEC_LEN 1000000
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

#define BITMASK(b) (1 << ((b) % 8))
#define BITSLOT(b) ((b) / 8)
#define BITSET(a, b) ((a)[BITSLOT(b)] |= BITMASK(b))
#define BITCLEAR(a, b) ((a)[BITSLOT(b)] &= ~BITMASK(b))
#define BITTEST(a, b) ((a)[BITSLOT(b)] & BITMASK(b))
#define BITNSLOTS(nb) ((nb + 8 - 1) / 8)

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
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
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
unsigned int masks[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
int happyCount = 0;
struct data
{
	unsigned int Depth;
	int offset;
	unsigned int sliceSt;
	unsigned int sliceEnd;
	char *myList;
	
};

struct data d[NUM_THR_PROC];
pthread_t threads[NUM_THR_PROC];
pthread_mutex_t mutex_sum;

static char List[CharSPACE];

void mapPrimes(unsigned int *bitArr, long Count);
void runThreads(long numBytes, long Inpt, int rem);


/*Will extract and turn the current char-bit masked
** happy primes an unsigned int bit-mask.
*/
void mapTurnin(int byteAmt)
{
	FILE *fp;
	FILE *fd;
	unsigned int i;
	int j;
	int k = 0;
	char temp[1];
	temp[0] = List[0];
	//This is the actual number value as we iterate 2^32-1 times.
	unsigned int Index = 1;
	//unsigned int  *intMask = malloc(sizeof(unsigned int*) * byteAmt);
	unsigned int  intMask[happyCount];
	//We want to iterate through the char array 
	for(i = 0; i<byteAmt; i++)
	{
	
	//For each byte we want to extract the happy derps, so only look at 2nd bit.		
		for (j = 7; j > -1; j = j - 2)
		{
			if(CHECK_BIT(List[i], j))
				{
					printf("EXTRACT HAPPINESS  %d  %d  %d\n", Index, i, j);
					//Filter the value into our mask and increment index
					intMask[k] = 0xFFFFFFFF & Index;
					k++; 
				}else
				{
				//printf("No happy\n");
				}
			//We go down the index because our list is backwards.
			Index++;
			
		}
	}
	
	printf("intmask size:  %ld\n",sizeof(intMask));
	fp = fopen("Turnin", "w");
	
	fwrite(intMask, sizeof(intMask[0]), sizeof(intMask)/sizeof(intMask[0]), fp);
	fclose(fp);
	fd = fopen("TurninChar", "w");
	fwrite(temp, sizeof(List[0]), 1, fp);
	 
	fclose(fd);



}


int happyOrsad(unsigned int nerm);



unsigned char mapReader(unsigned char singleBit, unsigned int Num)
{
	//Max index point
	unsigned int Index = Num * 4 + 3+1;						//Keep track of what number were on.
	unsigned char temp;
	int j;
	//printf("number: %d\n", Num);
	//printf("number: %d\n", Index);
	
	
	
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
				//printf("Prime Found\n");
				//If returns true (happy), else sad;
				if(happyOrsad(Index))
				{	
					//printf("AND ITS HAPPY\n");
					temp |= masks[j + 1];  
					happyCount++;
				} 
			} else
			{
				//printf("prime not found\n");
			}
		//We go down the index because our list is backwards.
		Index--;
		
	}
	return temp;
	
	//FILE *fp;
	//fp = fopen("premDs", "w");
	//fwrite(&temp, sizeof(singleBit), sizeof(singleBit)/sizeof(singleBit), fp);		


}

void *dot(void *arg)
{
	FILE *fp;
	unsigned int i;
	
	
	
	struct data *d = (struct data*) arg;
	
	
	
	printf("I'm thread #%d, and I'm starting up.\n", d->offset + 1);	
		
	//pthread_mutex_lock(&mutex_sum);

	printf("%d start: \n", d->sliceSt);
	printf("%d end: \n", d->sliceEnd);
	for(i = d->sliceSt; i < d->sliceEnd; i++)
	{
	List[i] = mapReader(List[i], i);
	}
	
	fp = fopen("Checker", "w");

		
	fwrite(List, sizeof(List[0]), d->Depth, fp);

	if(d->offset == 0)
		printf(" AMT OF BITS:  --->> %d\n",d->Depth);		
	//pthread_mutex_unlock(&mutex_sum);
	fclose(fp);
	pthread_exit((void*) 0);
}




/*
int derp(int Max)
{
	char bitarray[BITNSLOTS(Max)];
	int i, j;

	memset(bitarray, 0, BITNSLOTS(Max));

	for(i = 2; i < Max; i++) {
		if(!BITTEST(bitarray, i)) {
//			printf("%d\n", i);
			for(j = i + i; j < Max; j += i)
				BITSET(bitarray, j);
		}
		
	}
	
//	for(i = 0; i < 20; i++)
//	{
//		printf("%d\n", bitarray[i]);
//	}
	return 0;
	
	
}
*/

void runSystem(unsigned int start,unsigned int end,unsigned int offset)
{

	FILE *fp;
	unsigned int i;
	
	
	
	//struct data *d = (struct data*) arg;
	
	
	
	printf("I'm Child #%d, and I'm starting up.\n", d->offset + 1);	
		
	//pthread_mutex_lock(&mutex_sum);
	
	printf("%d start: \n", d->sliceSt);
	printf("%d end: \n", d->sliceEnd);
	for(i = d->sliceSt; i < d->sliceEnd; i++)
	{
	List[i] = mapReader(List[i], i);
	}
	
	fp = fopen("Checker", "w");

		
	fwrite(List, sizeof(List[0]), d->Depth, fp);	
	
	

    //exit(EXIT_SUCCESS);

}


void *mount_shmem(char *path, int object_size){
	int shmem_fd;
	void *addr;

	/* create and resize it */
	shmem_fd = shm_open(path, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (shmem_fd == -1){
		fprintf(stdout, "failed to open shared memory object\n");
		exit(EXIT_FAILURE);
	}
	/* resize it to something reasonable */
	if (ftruncate(shmem_fd, object_size) == -1){
		fprintf(stdout, "failed to resize shared memory object\n");
		exit(EXIT_FAILURE);
	}

	addr = mmap(NULL, object_size, PROT_READ | PROT_WRITE, MAP_SHARED, shmem_fd, 0);
	if (addr == MAP_FAILED){
		fprintf(stdout, "failed to map shared memory object\n");
		exit(EXIT_FAILURE);
	}

	return addr;
}














int main(int argc, char **argv)
{
	FILE *fp; 
	int i, choice, err;
	long numBytes;
	long Inpt= 0;
	int rem = 0;
	pid_t pid[NUM_THR_PROC];
	struct primeArr *primeArray;
	int object_size = 1024 * 1024 * 600;
	
	printf("Please enter the max integer to search through for primes: ---->    ");
	scanf("%ld",&Inpt);
//	derp(Inpt);



//	Used this function to initially get my numbers into a BITMAP
//	primeArray = crinit_primeArr(Inpt);
//	IgnorePts(primeArray);
//	p_primeArr(primeArray);						<<<-------------------------
//	mapPrimes(primeArray->num, Inpt);
//	freeArr(primeArray);
	
	//The number of bytes we want to pull in 
	
	numBytes = Inpt / 4; 							//4 numbers are kept per char.
//	printf("ERROR\n");
	if (Inpt % 4 > 0) { numBytes++;}
//	printf("ERROR\n");
	unsigned char *myPrimes = malloc(sizeof(unsigned char*) * numBytes);
	//char myPrimes[numBytes];						//So we get an array of that many chars(x4 numbers)
//	printf("ERRORhelp\n");
	
	//We open our bitmap(hashed in chars) and set it in the global list array
	fp = fopen("bitMap", "r");
	fread(List, sizeof(myPrimes[0]), numBytes, fp );
	//printf("ERROR\n");	
	Inpt = numBytes / NUM_THR_PROC;
	rem = numBytes % NUM_THR_PROC;

	printf("Would you like to run threads or system? 1 for threads, 2 for system, anything else to quit");
	scanf("%d",&choice); 
	
	if(choice == 1)
		runThreads(numBytes, Inpt, rem);
		
	if(choice == 2)
	{
		void *myAddr = mount_shmem("/shProc", object_size);
		
		for(i = 0; i < NUM_THR_PROC; i++)
		{
			for(i=0; i<NUM_THR_PROC; ++i)
			{
				d[i].Depth = numBytes;
				int j = 0;
				int k = 0;
				d[i].offset = i;
				d[i].sliceSt = (Inpt * i);										
				d[i].sliceEnd = Inpt * (i + 1);
				
				//If it is our last fork or thread...
				if(i == NUM_THR_PROC - 1)
				{
					d[i].sliceEnd = d[i].sliceEnd + rem;
				}
			}		
			switch(pid[i] = fork())
			{
				case -1:
					fprintf(stderr, "Fork failed");
				case 0: //child process
					printf("%d start: \n", d[i].sliceSt);
					printf("%d end: \n", d->sliceEnd);
					runSystem(d[i].sliceSt, d[i].sliceEnd, d[i].offset);
				default:
					break;
			}
		}
	}

	//Parse the char array and extract all happy primes with this FUNCtion.
	mapTurnin(numBytes);
	
	while(wait(NULL) != -1);
    shm_unlink("/shProc");
	
	return EXIT_SUCCESS;
}






void runThreads(long numBytes, long Inpt, int rem)
{
	pthread_attr_t attr;
	int i;
	
	pthread_mutex_init(&mutex_sum, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	for(i=0; i<NUM_THR_PROC; ++i)
	{
		d[i].Depth = numBytes;
		int j = 0;
		int k = 0;
		d[i].offset = i;
		d[i].sliceSt = (Inpt * i);										
		d[i].sliceEnd = Inpt * (i + 1);
		
		if(i == NUM_THR_PROC - 1)
		{
			d[i].sliceEnd = d[i].sliceEnd + rem;
		}
		pthread_create(&threads[i], &attr, dot, (void*)&d[i]);
		
	}	
	

	pthread_attr_destroy(&attr);

	for(i=0; i<NUM_THR_PROC; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&mutex_sum);
	
	
	


}



//Used to map my primes initially to create file I would later use.
void mapPrimes(unsigned int *bitArr, long Count)
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

int happyOrsad(unsigned int nerm)
{
	unsigned int total;
	unsigned int first;
	
	while(1){
		total = 0;
		first = 0;
		
		while(nerm > 0)
		{ 
		first = nerm % 10;	//get first digit
		nerm /= 10;			//remove digit from num;
		total += pow(first, 2); //Add sum of squares to total
	//	printf("number: %d\n", nerm);
		}
		if(total==1)
			return 1;
		if(total==4||total==16||total==37||total==58||total==89||total==145||total==42||total==20)
			return 0;
			
		nerm = total;		//Loop back and do it all again with the new 'number'
		
	}
	
}




// http://c-faq.com/misc/bitsets.html was used
