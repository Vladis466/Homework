/*	Vlad Predovic
**	CS372  Project1
**
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
#include "pthread.h"

#define LISTENQ 1024
#define MAXLINE 4096
#define MAXSOCKADDR 128
#define BUFFSIZE 1024

int cntoServer(); 
void * receiveMessage(void * socket);
char name[64];

void error(const char *msg)
{
    perror(msg);
    exit(0);
}


int main(int argc, char**argv)
{
	int socketfd, rdWrt;
	char buffer[1024];
  char finalbuff[1024];
  char prompt[128];
	char *hostname;
  char trigger[10] = "\\quit\n";
  char *SERV_STR;
	pthread_t rThread;
  unsigned int SERV_PORT;
	//codeTime();

    //sockaddr_in: structure containing an internet address
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    if(argc < 3)
    {
      printf("Type in as follows, ignoring quotations: 'cli' 'port number' 'host name'");
      exit(0);
    }

    SERV_STR = argv[1];
    SERV_PORT = atoi(argv[1]);
    hostname = argv[2];

     //printf("Enter the port number corresponding to the server please: ");
    //scanf("%d", &SERV_PORT);

    //printf("Type in the name of the host:");
    //scanf("%d", &hostname);


    printf("What would you like your handle to be? ");
    scanf("%s", name);
    strcpy(prompt, "< ");
    strcat(prompt, name);
    strcat(prompt, " >  ");
    prompt[strlen(prompt)-1] = 0;

    //AF_INET: addr domain of socket connects to IPv4
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) 
        error("ERROR opening socket");
        
    
    //server = pointer with info about that host
    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    //printf("SERVER NAME:::::::  %s", server);
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
    if (connect(socketfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");



    printf("Welcome, start chatting below: to disconnect type in \\quit \n\n\n");  

    rdWrt = sendto(socketfd, SERV_STR, 5, 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

     rdWrt = pthread_create(&rThread, NULL, receiveMessage, (void *) socketfd);
     if (rdWrt) {
      printf("ERROR: Return Code from pthread_create() is %d\n", rdWrt);
      exit(1);
     }

     while (fgets(buffer, BUFFSIZE, stdin) != NULL) {
      fprintf(stderr, "< %s >  ", name);


      //If \quit, end program and send signal to server
      if(!strcmp(buffer, trigger))
        {
          printf("Disconnecting now, goodbye \n\n\n"); 
          rdWrt = sendto(socketfd, buffer, strlen(buffer), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr));  
          exit(0);
          close(socketfd);
          pthread_exit(NULL);
          exit(0);    
          break;
        } else 
        {
            //Reset final message. Add prompt and buffer. Then send it to the server.
            finalbuff[0] = 0;
            strcat(finalbuff, prompt);
            strcat(finalbuff, buffer);
            rdWrt = sendto(socketfd, finalbuff, strlen(finalbuff), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr));  
            if (rdWrt < 0) {  
             printf("Error sending data!\n\t-%s", buffer);  
            }          
        }




     }




     printf("Closing socket now, goodbye");
     close(socketfd);
     pthread_exit(NULL);
 
     return 0;
}


void * receiveMessage(void * socket) {
 int sockfd, rdWrt;
 char buffr[BUFFSIZE]; 
 char trigger[10] = "\n\\quit\n";
 sockfd = (int) socket;
  
 for (;;) {
  memset(buffr, 0, BUFFSIZE); 
  rdWrt = recvfrom(sockfd, buffr, BUFFSIZE, 0, NULL, NULL);  
  if (rdWrt < 0) {  
   printf("Error receiving data!\n");    
  } else {
   //buffr[strlen(buffr)] = 0;
   fputs(buffr, stdout);
   //printf("%s", trigger);
   if(!strcmp(buffr, trigger))
   {
      usleep(100*1000);  /* sleep for 100 milliSeconds */
      printf("Closing socket...\n\n");
      exit(0); 
      close(sockfd);
      pthread_exit(NULL); 
      printf("Success. Goodbye\n\n");    
   }

   
  }  
 }
}
