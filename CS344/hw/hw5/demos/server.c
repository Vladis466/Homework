/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define SERV_PORT 9878
#define SERV_PORT_STR "9878"
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
	 //sockaddr_in: structure containing an internet addres
     struct sockaddr_in serv_addr, cli_addr;
     int n;
	 
	 
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
	 
	 //AF_INET: addr domain of socket connects to IPv4
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
	 //initializing port buffer to 0
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
	 
	 //address family (IPv4)
     serv_addr.sin_family = AF_INET;
	 //IP address of host server
     serv_addr.sin_addr.s_addr = INADDR_ANY;
	 //convert port number from host to network byte order
     serv_addr.sin_port = htons(portno);
	 
	 //socket file descriptor, address, size of address. : binds socket to address
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
	 //listens for socket connections, max queue = 5
     listen(sockfd,5);
	 
	 //When connection made, return the new socket fd.
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
	 
	 //initialize buffer and read from socket
	 bzero(buffer,256); 
	 
//	 do{
     while(n = read(newsockfd,buffer,255) != 0)
	 {
//	 if(strcmp(buffer,"exitNow")== 0) break;
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);
     n = write(newsockfd,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");
//	 }while(strcmp(buffer,"exitNow")!= 0);
	 }
     close(newsockfd);
     close(sockfd);
     return 0; 
}

//http://www.linuxhowtos.org/C_C++/socket.htm