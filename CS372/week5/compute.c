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
#define SERV_PORT 6969
#define SERV_PORT_STR "6969"
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
	char buff[1024];
	
	//codeTime();
	
	
	socketfd = cntoServer();
	// //Message stuff
	// do{
	//     printf("Please enter the message: ");
	//     bzero(buffer,256);
	//     fgets(buffer,255,stdin) != NULL;
		
	// 	if(strcmp(buffer,"exitNow")== 0) break;
	//     rdWrt = write(socketfd,buffer,strlen(buffer));
	//     if (rdWrt < 0) 
	//          error("ERROR writing to socket");
	//     bzero(buffer,256);
	//     rdWrt = read(socketfd,buffer,255);
	//     if (rdWrt < 0) 
	//          error("ERROR reading from socket");
	//     printf("%s\n",buffer);
		
	// }while(strcmp(buffer,"exitNow")!= 0);
    

    while(1) {
        printf("Client: Enter Data for Server:\n");
        fgets(buffer,256-1,stdin);
        if ((send(socketfd,buffer, strlen(buffer),0))== -1) {
                fprintf(stderr, "Failure Sending Message\n");
                close(socketfd);
                exit(1);
        }
        else {
                printf("Client:Message being sent: %s\n",buffer);
                rdWrt = recv(socketfd, buffer, sizeof(buffer),0);
                if ( rdWrt <= 0 )
                {
                        printf("Either Connection Closed or Error\n");
                        //Break from the While
                        break;
                }

                buff[rdWrt] = '\0';
                printf("Client:Message Received From Server -  %s\n",buffer);
           }
    }
    close(socketfd);
    
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