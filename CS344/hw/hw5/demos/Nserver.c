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

	char buf[MAXLINE];
	socklen_t clilen;
	struct sockaddr_in cliaddr;
	struct sockaddr_in servaddr;

	if(argc < 2)
	{
		printf("usage: %s port\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	port = atoi(argv[1]);

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);

	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	listen(listenfd, LISTENQ);

	clilen = sizeof(cliaddr);

	
	//for(;;){
	sockfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

	for(;;){
		
		//memset(buf, 0,MAXLINE);

		if( (n = read(sockfd, buf, MAXLINE)) == 0){
			//nothing was read, end of "file"
			close(sockfd);
			break;
		}else{
			printf("Received from client: %s\n", buf);
			write(sockfd, buf, n);
		}
	}
	//}

	return 0;
}