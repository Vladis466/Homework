#define _POSIX_C_SOURCE 200908L

#include <sys/types.h>  // basic system data types
#include <sys/socket.h> // basic socket definitions
#include <sys/time.h>   // timeval{} for select()
#include <time.h>       // timespec{} for pselect()
#include <netinet/in.h> // sockaddr_in{} and other Internet defns
#include <arpa/inet.h>  // inet(3) functions
#include <errno.h>
#include <fcntl.h>      // for nonblocking
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>   // for S_xxx file mode constants
#include <sys/uio.h>    // for iovec{} and readv/writev
#include <unistd.h>
#include <sys/wait.h>
#include <sys/select.h>

#define LISTENQ 1024
#define MAXLINE 4096
#define MAXSOCKADDR 128
#define BUFFSIZE 4096

int main(int argc, char **argv)
{
	int i;
	int listenfd;
	int sockfd;
	int port;
	int n;
	int num_bytes;
	char buf[MAXLINE];
	char clistr[MAXLINE];
	socklen_t clilen;
	struct sockaddr_in cliaddr;
	struct sockaddr_in servaddr;

	if(argc < 2)
	{
		printf("usage: %s port\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	port = atoi(argv[1]);

	listenfd = socket(AF_INET, SOCK_DGRAM, 0);

	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);

	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	listen(listenfd, LISTENQ);

	clilen = sizeof(cliaddr);

	
	for(;;){
		int len = sizeof(struct sockaddr_in);
		num_bytes = recvfrom(listenfd, buf, MAXLINE, 0,
		                    (struct sockaddr *) &cliaddr, &len);
	  
		if (num_bytes == -1)
		{
			perror("recvfrom");
			exit(EXIT_FAILURE);
		}
		
		if (inet_ntop(AF_INET, &cliaddr.sin_addr, clistr, clilen) == NULL)
		{
			printf("couldn't get address.\n");
		}
		else
		{
			printf("Server received %ld bytes from (%s, %u)\n",
			       (long) num_bytes, clistr, ntohs(cliaddr.sin_port));
		}

		for (int j = 0; j < num_bytes; j++)
			buf[j] = toupper((unsigned char) buf[j]);

		if (sendto(listenfd, buf, num_bytes, 0, (struct sockaddr *) &cliaddr, len) != num_bytes)
		{		
			printf("Oops.");
			exit(EXIT_FAILURE);
		}
		
	}

	return 0;
}