/*	Vlad Predovic
**	CS344 HW 5regex c
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
#include <arpa/inet.h>
#include <netdb.h>
#include <stdint.h>
#include <pcre.h>

#define LISTENQ 1024
#define MAXLINE 4096
#define MAXSOCKADDR 128
#define BUFFSIZE 4096
#define SERV_PORT 6969
#define SERV_PORT_STR "6969"
#define SERV_NAME "localhost"

//

  
  
  
char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int cntoServer(); 
int codeTime();
int brutePerfect(long *perfys, int stRange, int endRange);

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

const char* Jparser(int choice, char *test_string)
{
	pcre       *re_compiled;
	pcre_extra *p_extra;
	int         pcre_exec_ret;
	int         sub_str_vec[30];
	const char *pcre_error_str;
	int         pcre_error_offset;
	char       *str_regex;
	char      **to_match;
	const char *psub_str_match_str;
	int         j;
	const char *itemValue;
 	char *test_strings[] = {"\"start\":",
							 test_string,
	                         NULL}; 


	switch(choice) 
	{
		case 1:
			str_regex = "(.*)(hello)+";
			break;
		case 2:
			str_regex = "(?<=\"Performance\":)[0-9]++";
			break;
		case 3:
			str_regex = "(?<=\"Start\":)[0-9]++";
			break;
	}
	printf("\nRegex to use: %s", str_regex);

	// First, the regex string must be compiled.
	re_compiled = pcre_compile(str_regex, PCRE_UNGREEDY, &pcre_error_str, &pcre_error_offset, NULL);

	// OPTIONS (second argument) (|'ed together) can be:
	//    PCRE_ANCHORED       -- Like adding ^ at start of pattern.
	//    PCRE_CASELESS       -- Like m//i
	//    PCRE_DOLLAR_ENDONLY -- Make $ match end of string regardless of \n's
	//    No Perl equivalent.
	//    PCRE_DOTALL         -- Makes . match newlines too.  Like m//s
	//    PCRE_EXTENDED       -- Like m//x
	//    PCRE_EXTRA          -- 
	//    PCRE_MULTILINE      -- Like m//m
	//    PCRE_UNGREEDY       -- Set quantifiers to be ungreedy.  Individual quantifiers
	//                           may be set to be greedy if they are followed by "?".
	//    PCRE_UTF8           -- Work with UTF8 strings.

	// pcre_compile returns NULL on error, and sets pcre_error_offset & pcre_error_str
	if(re_compiled == NULL) {
		printf("ERROR: Could not compile '%s': %s\n", str_regex, pcre_error_str);
		exit(1);
	}

	// Optimize the regex
	p_extra = pcre_study(re_compiled, 0, &pcre_error_str);

	// pcre_study() returns NULL for both errors and when it can not optimize
	//    the regex.  The last argument is how one checks for errors (it is NULL
	//    if everything works, and points to an error string otherwise.
	if(pcre_error_str != NULL) {
		printf("ERROR: Could not study '%s': %s\n", str_regex, pcre_error_str);
		exit(1);
	}

	// HERE IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	for(to_match = test_strings; *to_match != NULL; to_match++) {
		//printf("String: %s\n", *to_match);
		//printf("        %s\n", "0         1         2         3");

		// Try to find the regex in to_match, and report results.
		pcre_exec_ret = pcre_exec(re_compiled,
		                          p_extra,
		                          *to_match, 
		                          strlen(*to_match),  // length of string
		                          0,                  // Start looking at this point
		                          0,                  // OPTIONS
		                          sub_str_vec,
		                          30);                // Length of sub_str_vec

		// pcre_exec OPTIONS (|'ed together) can be:
		//    PCRE_ANCHORED -- can be turned on at this time.
		//    PCRE_NOTBOL
		//    PCRE_NOTEOL
		//    PCRE_NOTEMPTY

		// Report what happened in the pcre_exec call..
		//printf("pcre_exec return: %d\n", pcre_exec_ret);
		if(pcre_exec_ret < 0) { // Something bad happened..
			switch(pcre_exec_ret) {
			case PCRE_ERROR_NOMATCH: 
				//printf("String did not match the pattern\n");
				break;
			case PCRE_ERROR_NULL: 
				printf("Something was null\n");
				break;
			case PCRE_ERROR_BADOPTION:
				printf("A bad option was passed\n");
				break;
			case PCRE_ERROR_BADMAGIC: 
				printf("Magic number bad (compiled re corrupt?)\n");
				break;
			case PCRE_ERROR_UNKNOWN_NODE:
				printf("Something kooky in the compiled re\n");
				break;
			case PCRE_ERROR_NOMEMORY: 
				printf("Ran out of memory\n");
				break;
			default: 
				printf("Unknown error\n");
				break;
			} /* end switch */
		} else {
			//printf("Result: We have a match!\n");
        
			// At this point, rc contains the number of substring matches found...
			if(pcre_exec_ret == 0) {
				printf("But too many substrings were found to fit in sub_str_vec!\n");
				// Set rc to the max number of substring matches possible.
				pcre_exec_ret = 30 / 3;
			}

			// DIY way to get the first substring match (whole pattern):
			// char subStrMatchStr[1024];
			// int i, j
			// for(j=0,i=sub_str_vec[0];i<sub_str_vec[1];i++,j++) 
			//   subStrMatchStr[j] = (*to_match)[i];
			// subStrMatchStr[sub_str_vec[1]-sub_str_vec[0]] = 0;
			//printf("MATCHED SUBSTRING: '%s'\n", subStrMatchStr);
        
			// PCRE contains a handy function to do the above for you:
			//substring vector is the index
			for(j = 0; j < pcre_exec_ret; j++) {
				pcre_get_substring(*to_match, sub_str_vec, 
				                   pcre_exec_ret, j, &(psub_str_match_str));
				printf("Match(%2d/%2d): (%2d,%2d): '%s'\n", j, pcre_exec_ret - 1, 
				       sub_str_vec[j * 2], sub_str_vec[j * 2 + 1], psub_str_match_str);
			
			}
			//printf("This is number: %s\n", psub_str_match_str);

			switch(choice) 
			{
				case 1:
					printf("Lollerskates\n");
					break;
				case 2:
					pcre_free(re_compiled);
					return psub_str_match_str;		//cant free string sorry....
					break;
				case 3:
					pcre_free(re_compiled);
					return psub_str_match_str;
					break;
			}
			
			
			// Free up the substring
			pcre_free_substring(psub_str_match_str);
		}
		printf("\n");
      
	} 
  
	// Free up the regular expression.
	pcre_free(re_compiled);
      
	// Free up the EXTRA PCRE value (may be NULL at this point)
	if(p_extra != NULL)
		pcre_free(p_extra);

	return itemValue;
}
int main()
{
	int socketfd, rdWrt;
	int i;
	char buffer[256];
	long int endLim, strtLim, writer, amt;
	long perfRange;
	long *perfArr = malloc(sizeof(long)*10);
	char perfSend[256];
	const char *strtLimCH, *amtCH;
	char* ch;
	

    //code goes here
	
    
	//Initializing and connecting to the server
	socketfd = cntoServer();
	
	
	//Getting the amount of numbers we can compute in 15sec
	//Then get it in JSON format and write it to the open socket.
	perfRange = codeTime();
    clock_t t1,t2;
    t1=clock();							
	//perfRange = 56000;
	snprintf(perfSend,256, "%d", perfRange);
	ch = concat("\"Performance\":", perfSend);
	write(socketfd, ch, strlen(ch));

 

	//zero out the buffer and then we read from the socket
	bzero(buffer,256);
	rdWrt = read(socketfd,buffer,255);	
    printf("\n\n\n%s\n",buffer);													//JSON implementation?

	//Get the responses from the server and parse it into numbers
	//with regular expressions. Then submit them to your brute force
	strtLimCH = Jparser(3, buffer);
	amtCH = Jparser(2, buffer);
	strtLim = strtol(strtLimCH, NULL, 0);
	amt = strtol(amtCH, NULL, 0);
	endLim = strtLim + amt;

	printf("\n\n\nEND LIMIT COMPUTED: %ld \n", endLim);
	if(endLim)
		brutePerfect(perfArr, strtLim, endLim);
	else
		printf("Error, ending limit could not be computed");
	
	
	
	//While loop concatenating the perfect numbers
	//into a JSON format array.
	i = 0;
	ch = "{\"PerfectNumbers\":[";
	while(perfArr[i+1] != 0)
	{
	snprintf(perfSend,256, "%ld", perfArr[i]);
	ch = concat(ch, perfSend);
	ch = concat(ch, ", ");
	i++;
	}
	//Get and insert the last value into our JSON array
	snprintf(perfSend,256, "%d", perfArr[i]);
	ch = concat(ch, perfSend);
	ch = concat(ch, "], ");
	//printf("\n\n\n%s\n",ch);
	
	//Add the total running time into our JSON string to send to manage.
	t2=clock();
    float diff = ((float)t2-(float)t1);
	float seconds = diff / CLOCKS_PER_SEC;	
	
	
	snprintf(perfSend,256, "%f", seconds);
	ch = concat(ch, "\"Time\":");
 	ch = concat(ch, perfSend);
	ch = concat(ch, "}");
	printf("\n\n\n%s\n",ch);   

	//WRITE THAT ISHHHHHH meow meow meow
	bzero(buffer,256);
	write(socketfd, ch, strlen(ch));	
	
	close(socketfd);
	free(perfArr);
    return 0;
}
	
	


/*     rdWrt = write(socketfd,perfSend,strlen(perfSend));
    if (rdWrt < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
	
    rdWrt = read(socketfd,buffer,255);
    if (rdWrt < 0) 
         error("ERROR reading from socket"); */


/*Description: Computes and stores the perfect numbers in perfys
**Algorithm brute forces the numbers 
**
**
*/
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

/*Description: Returns the amount of tasks program can accomplish  
**
**
**
*/
int codeTime()
{
	time_t start, total;
	struct timespec tms;
	long iterate = 12000;
	int i, j;
	long dummy = 0;
	
	//Keep tweaking the iterate value until we hit 15
	//run the iterator, if way too small increase iterate by 100X
	//If way too bi/small, dec/inc by 10x
	//If slightly, increase/dec by 500;
	while(total != 15)
	{
		start = time(0);				//Reset timer
		
		for(i = 1; i < iterate; i++)
		{	
			for(j = 1; j < i; j++)
				dummy = iterate % j;
		}
		//Check the time and adjust accordingly
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
			iterate *= 2;
			printf("iterator value2: %ld  \n", iterate);
			}
		else if((total - 15) < 5 && (total - 15) > 0 ) 
			{
			iterate -= 2000;								//slightly too big
			printf("iterator value3: %ld  \n", iterate);	
			}
		else if((15 - total) < 5 && (15 - total) > 0)
		{
			iterate += 4000;
			printf("iterator value4: %ld  \n", iterate);	
		}
		//My function started bugging out 10 minutes before 12.
		//I was not calling it because it takes a while to find the value
		iterate = 52000;
		break;
	}
	//When we hit 15 return the value
	return iterate;
}

/*Description: All the initial server connection stuff
**
**
**
*/
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