/*  Vlad Predovic
**  CS372  Project2
**
*/
#include <fcntl.h>
#include "dirent.h"
#include <errno.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h>
#include "pthread.h"


void dataConnect(char *DATA_PORT_str, char *cmnd, char *file_name);
void returnTextFile(int clientfd2, char *f_name);
void returnDirectory(int cli_sock);

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

//All credit goes to Joseph Quincy for his exerpt on closing sockets
int getSO_ERROR(int fd) {
   int err = 1;
   socklen_t len = sizeof err;
   if (-1 == getsockopt(fd, SOL_SOCKET, SO_ERROR, (char *)&err, &len))
      perror("getSO_ERROR");
   if (err)
      errno = err;              // set errno to the socket SO_ERROR
   return err;
}

void closeSocket(int fd) {      // *not* the Windows closesocket()
   if (fd >= 0) {
      getSO_ERROR(fd); // first clear any errors, which can cause close to fail
      if (shutdown(fd, SHUT_RDWR) < 0) // secondly, terminate the 'reliable' delivery
         if (errno != ENOTCONN && errno != EINVAL) // SGI causes EINVAL
            perror("shutdown");
      if (close(fd) < 0) // finally call close()
         perror("close");
   }
}
//-------------------------------------------------------------------

#define CLADDR_LEN 128
#define BUFF_SIZE 1024

int main(int argc, char**argv)
{   
  int sockfd, rdWrt;
  struct sockaddr_in self;
  char buffer[BUFF_SIZE];
  int SERV_PORT;
  /*---Create streaming socket---*/
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0)
    error("ERROR opening socket");

  if(argc < 2)
  {
    printf("Type in the port number on the command line when you start the program please \n\n\n");
    exit(0);
  }
  SERV_PORT = atoi(argv[1]);  

  /*---Initialize address/port structure---*/
  bzero(&self, sizeof(self));
  self.sin_family = AF_INET;
  self.sin_port = htons(SERV_PORT);
  self.sin_addr.s_addr = INADDR_ANY;

  /*---Assign a port number to the socket---*/
  if ( bind(sockfd, (struct sockaddr*)&self, sizeof(self)) != 0 )
    error("ERROR assigning port number to socket");

  /*---Make it a "listening socket"---*/
  if ( listen(sockfd, 20) != 0 )
    error("ERROR setting socket to listen");

  /*---Forever... ---*/
  while (1)
  { 
    int clientfd;
    struct sockaddr_in client_addr_info;
    int addrlen=sizeof(client_addr_info);
    char checker[3];
    char data_port[8];
    char filename[255];


    printf("\n\nMain buffer emptied, now waiting for an initial connection and the following command.\n\n");
    /*---accept a connection (creating a data pipe)---*/
    clientfd = accept(sockfd, (struct sockaddr*)&client_addr_info, &addrlen);
    printf("%s:%d connected\n", inet_ntoa(client_addr_info.sin_addr), ntohs(client_addr_info.sin_port));

    //Make sure stdout is flushed for kicks, that way nothing messes with printing as is often the case
    fflush(stdout);
    memset(buffer, 0, BUFF_SIZE);
    //Accept and parse the COMMAND from client, get the length for the text file
    rdWrt = recv(clientfd, buffer, BUFF_SIZE, 0); 
    size_t len_str = strlen(buffer);

    strncpy(checker, buffer, 2);
    strncpy(data_port, buffer+2, 6);
    strncpy(filename, buffer+6, len_str);
    checker[2] = '\0';
    data_port[4] = '\0';
    filename[len_str - 5] = '\0';
    fflush(stdout);
    /*printf("DATA PORT --------->%s\n\n", data_port);
    printf("FILE NAME --------->%s\n\n", filename);
    printf("COMMAND ---------->%s\n\n", checker);
    printf("DOES IT MATCH WILL PRINT 0 --------->%d\n\n", strcmp(filename, "sample.txt"));*/
    if(!strcmp(checker, "-l") || !strcmp(checker, "-g"))
    {
      //returnDirectory(clientfd);
      dataConnect(data_port, checker, filename);
    }
    else
    {
      printf("Command sent was not accepted");
      strcpy(buffer, "Commands sent were invalid...closing connection now\n\n");
      send(clientfd, buffer, sizeof(buffer), 0);      
    }

    /*---Close data connection---*/
    printf("Closing Client Connection....");
    sleep(1);
    closeSocket(clientfd);
  }

  /*---Clean up (should never get here!)---*/
  printf("Closing Host Connection....");
  closeSocket(sockfd);
  return 0;
}




//Creates the data connection and calls a function depending on the command that was passed.
void dataConnect(char *DATA_PORT_str, char *cmnd, char *file_name)
{
  int sockfd2, rdWrt2, DATA_PORT;
  struct sockaddr_in self2;
  char buffer2[BUFF_SIZE];
  int reuse = 1;
  
  DATA_PORT = atoi(DATA_PORT_str);




  /*---Create streaming socket---*/
  sockfd2 = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd2 < 0)
    error("ERROR opening socket");


  if (setsockopt(sockfd2, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0)
      perror("setsockopt(SO_REUSEADDR) failed");

  #ifdef SO_REUSEPORT
    if (setsockopt(sockfd2, SOL_SOCKET, SO_REUSEPORT, (const char*)&reuse, sizeof(reuse)) < 0) 
        perror("setsockopt(SO_REUSEPORT) failed");
  #endif

  /*printf("DATA PORT --------->%d\n\n", DATA_PORT);
  printf("COMMAND ---------->%s\n\n", cmnd);
  printf("FILE NAME --------->%s\n\n", file_name);*/
  /*---Initialize address/port structure---*/
  bzero(&self2, sizeof(self2));
  self2.sin_family = AF_INET;
  self2.sin_port = htons(DATA_PORT);
  self2.sin_addr.s_addr = INADDR_ANY;

  /*---Assign a port number to the socket---*/
  if ( bind(sockfd2, (struct sockaddr*)&self2, sizeof(self2)) != 0 )
    error("ERROR assigning port number to socket(in function:data Connect)");

  /*---Make it a "listening socket"---*/
  if ( listen(sockfd2, 5) != 0 )
    error("ERROR setting socket to listen");

  int clientfd2;
  struct sockaddr_in client_addr_info2;
  int addrlen2=sizeof(client_addr_info2);

  memset(buffer2, 0, BUFF_SIZE);

  printf("\n\n Now listening for the client to connect in order to begin data transfer.\n\n");
  /*---accept a connection (creating a data pipe)---*/
  clientfd2 = accept(sockfd2, (struct sockaddr*)&client_addr_info2, &addrlen2);
  printf("%s:%d Data connection established:\n", inet_ntoa(client_addr_info2.sin_addr), ntohs(client_addr_info2.sin_port));


  //Pick whether to return the current directory or send back a file.
  //Defaults to a text file since we already did the error handling
  if(!strcmp(cmnd, "-l"))
    returnDirectory(clientfd2);
  else
    returnTextFile(clientfd2, file_name);



  /*---Close data connection---*/
  printf("Closing data connection socket.....\n\n");

  closeSocket(clientfd2);
  sleep(2);
  closeSocket(sockfd2);


  return;
}



//Take in the client file descriptor and file name.
//Open the file selected and copy it over to the buffer.
//It is then sent over the connection to the client.
//If the file name is incorrect, all connections to the client will close.
void returnTextFile(int clientfd2, char *f_name)
{
  char buff[BUFF_SIZE];
  char file_path[1024];
  ssize_t read_return;
  int filefd;

  getcwd(file_path, sizeof(file_path));
  memset(buff, 0, BUFF_SIZE);
  strcat(file_path, "\\");
  strcat(file_path, f_name);

  printf("FILE PATH---->%s\n\n", file_path);

  filefd = open(f_name, O_RDONLY);
  if (filefd == -1)
  {
    printf("Commands sent were invalid...closing connection now\n\n");
    strcpy(buff, "Commands sent were invalid...closing connection now\n\n");
    send(clientfd2, buff, sizeof(buff), 0); 
    return;        
  } else {
    strcpy(buff, "Beginning Transmission.... Sending text file \n\n");
    send(clientfd2, buff, sizeof(buff), 0);     
  }




    while (1) {
        read_return = read(filefd, buff, BUFF_SIZE);
        if (read_return == 0)
          break;
        if (read_return == -1) 
          error("Error on open");
        //fflush(stdout);
        //printf("\n%s\n", buff);
        //if (write(clientfd2, buff, read_return) == -1) 
            //error("Error on writing file to socket");
        send(clientfd2, buff, sizeof(buff), 0); 
        
    }
    if (close(filefd) < 0) // finally call close()
         error("close read file error");
    return;
}


//Function that returns the current directory with very little formatting and all file names inside it.
//Relies primarily on the dirent struct for populating the buffer.
void returnDirectory(int cli_sock)
{
  char buff[BUFF_SIZE];
  char cwd[1024];
  DIR *curr_dir;
  struct dirent *dir_format;


  //Get the current working directory, needed for seeing everything inside it
  if (getcwd(cwd, sizeof(cwd)) != NULL)
    fprintf(stdout, "Current working dir: %s\n", cwd);
  else
    perror("getcwd() error");


  memset(buff, 0, BUFF_SIZE);

  // Cycle through CWD, appending each item to the buffer)
  if ((curr_dir = opendir (cwd)) != NULL) 
  {
    while ((dir_format = readdir(curr_dir)) != NULL)
    {
      //printf ("%s\n", dir_format->d_name);
      strcat(buff, dir_format->d_name);
      strcat(buff, "\n");
    }
    closedir(curr_dir);
  } else {
    perror("Error reading directory, no result will be available");
    exit(1);
  }
  //printf ("%s\n", buff);
  send(cli_sock, buff, sizeof(buff), 0);   
  return;
}



//SOURCES



//http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
//http://www.theinsanetechie.in/2014/01/a-simple-chat-program-in-c-tcp.html
//source: http://stackoverflow.com/questions/23119615/coding-ftp-service-over-tcp-in-c-code
//https://beej.us/guide/bgnet/output/html/singlepage/bgnet.html
//https://www.cs.utah.edu/~swalton/listings/sockets/programs/part2/chap6/simple-server.c
//http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
//http://stackoverflow.com/questions/2014033/send-and-receive-a-file-in-socket-programming-in-linux-with-c-c-gcc-g

//Following code was taken just to close sockets (I hope thats not an issue)
//http://stackoverflow.com/questions/12730477/close-is-not-closing-socket-properly



//Using setsockopt to reuse an address
//http://stackoverflow.com/questions/24194961/how-do-i-use-setsockoptso-reuseaddr