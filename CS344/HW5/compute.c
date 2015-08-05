
/*	Vlad Predovic
**	CS344 HW 5
**
**	This file tests all #'s in a range provided
**	by a message from the central server
**	Depending on the message it will also shut down.
**	The message it receives should have it running 
**	for 15 seconds FLAT.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <time.h>

#define LISTENQ 1024
#define MAXLINE 4096
#define MAXSOCKADDR 128
#define BUFFSIZE 4096

#define SERV_PORT 9878
#define SERV_PORT_STR "9878"






int codeTime()
{
	time_t start, total;
	int iterate = 100000;
	int i;
	long dummy = 0;
	
	//Keep tweaking the iterate value until we hit 15
	//run the iterator, if way too small increase iterate by 100X
	//If way too big, decrease by 10x
	//If slightly, increase/dec by 500;
	while(total != 15)
	{
		start = time(0);				//Reset timer
		for(i = 0; i < iterate; i++)
		{
			dummy += iterate % i;
		}
		total = difftime((time_t) time(0), start);			//Get time diff
		printf("time taken: %d  \n", total);
		
		if(total - 15 < 1)
			iterate -= 500;								//slightly too big
			
		if(15 - total < 1)
			iterate += 500;
			
		if(total - 15 > 1)
			iterate /= 70;
		
		if(15 - total > 1)
			iterate *= 100;
	}

	return 0;
}


int brutePerfect(long *perfys, int stRange, int endRange)
{
	
	int i, target, Sums;
	int j = 0;
	long *perfArr = malloc(sizeof(long)*10);

	target = stRange;
	
	
	while(target < endRange)
	{	
		i = 1;
		Sums = 0;
		while(i < target)
		{
			if(target % i == 0)
				Sums += i;
			i++;
		}

	    if(Sums==target)
		    printf("%d is a perfect number\n",target);
			perfArr[j] = Sums;
			j++;
	    else
		    printf("%d is not a perfect number\n",target);
			
		target++;
	}
}


//Our socket and parser will have to be in this 
//function eventually.
int main()
{
	int endLim, strtLim;
	long *perfArr = malloc(sizeof(long)*10);
	
	printf("Insert number to start searching for perfectitude \n");
	scanf ("%d",&strtLim);
	printf("Insert number to to search up to for perfectitude \n");
	scanf ("%d",&endLim);
	
	brutePerfect(perfArr, strtLim, endLim);
	
	codeTime();

}