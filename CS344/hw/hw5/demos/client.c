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
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


#define LISTENQ 1024
#define MAXLINE 4096
#define MAXSOCKADDR 128
#define BUFFSIZE 4096
#define SERV_PORT 6868
#define SERV_PORT_STR "6868"
#define SERV_NAME "localhost"

int cntoServer(); 
int codeTime();
int brutePerfect(long *perfys, int stRange, int endRange);
void error(const char *msg)
{
    perror(msg);
    exit(0);
}


int main()
{
	int socketfd, rdWrt;
	char buffer[256];
	int endLim, strtLim;
	long *perfArr = malloc(sizeof(long)*10);
	
	printf("Start search number\n");
	scanf ("%d",&strtLim);
	printf("end search number \n");
	scanf ("%d",&endLim);
	
	brutePerfect(perfArr, strtLim, endLim);
	
	//codeTime();
	
	
	socketfd = cntoServer();
	//Message stuff
//	do{
    printf("Please enter the message: ");
    bzero(buffer,256);
    while(fgets(buffer,255,stdin) != NULL)
	{
//	if(strcmp(buffer,"exitNow")== 0) break;
    rdWrt = write(socketfd,buffer,strlen(buffer));
    if (rdWrt < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
    rdWrt = read(socketfd,buffer,255);
    if (rdWrt < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);
	}
//	}while(strcmp(buffer,"exitNow")!= 0);
    close(socketfd);
    return 0;
}






int brutePerfect(long *perfys, int stRange, int endRange)
{
	
	int i, Sums;
	long target;
	int j = 0;
	int count = 0;

	if(stRange > endRange)
	{
	printf("ERROR IN RANGES");
	exit(EXIT_FAILURE);
	}
	
	
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
	    if(Sums == target)
		{
		    printf("%ld is a perfect number\n",target);
			perfys[j] = Sums;
			j++;
			count++;
		}
		target++;
	}
	return count;
}

int codeTime()
{
	time_t start, total;
	struct timespec tms;
	long iterate = 12000000;
	int i;
	long dummy = 0;
	
	//Keep tweaking the iterate value until we hit 15
	//run the iterator, if way too small increase iterate by 100X
	//If way too big, decrease by 10x
	//If slightly, increase/dec by 500;
	while(total != 15)
	{
		start = time(0);				//Reset timer
		for(i = 1; i < iterate; i++)
		{
			dummy += iterate % i;
		}
		total = difftime((time_t) time(0), start);			//Get time diff
		printf("time taken: %d  \n",(int) total);
		printf("iterator value: %ld  \n", iterate);
		if((total - 15) > 5)
			{
			iterate /= 5;
			printf("iterator value1: %ld  \n", iterate);
			}
		else if((15 - total) > 5)
			{
			iterate *= (11 - total);
			printf("iterator value2: %ld  \n", iterate);
			}
		else if((total - 15) < 5 && (total - 15) > 0 ) 
			{
			iterate -= 5000;								//slightly too big
			printf("iterator value3: %ld  \n", iterate);	
			}
		else if((15 - total) < 5 && (15 - total) > 0)
		{
			iterate += 80000000;
			printf("iterator value4: %ld  \n", iterate);	
		}
	}

	return 0;
}


int cntoServer()
{
	int sockfd;
	//sockaddr_in: structure containing an internet addres
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
	
	//AF_INET: addr domain of socket connects to IPv4
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
		
	
	//server = pointer with info about that host
    server = gethostbyname(SERV_NAME);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
	////initializing port buffer to 0
    bzero((char *) &serv_addr, sizeof(serv_addr));
	//address family (IPv4)
    serv_addr.sin_family = AF_INET;
	//IP address of host server, need to copy cause its a charArr
	//Since we initially get with 'gethostbyname'
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
	//convert port number from host to network byte order
    serv_addr.sin_port = htons(SERV_PORT);
	
	//socket fd, server address, size of addr. Connects server/client
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

	return sockfd;
}