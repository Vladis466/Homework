/*
 * Vlad Predovic
 * CS 344
 * Summer 2015
 * myar.c intends to illustrate the of file I/O on Unix by teaching us to maintain a 
 * UNIX archive library. The program should run similar to the std UNIX command ar.
 * Options available are:
 
			> myar key arfile name ...
					where > indicates the command prompt at the shell, arfile is the name 
					of the archive file to be used, and key is one of the following options:
			-q quickly append named files to archive
			-x extract named files
			-t print a concise table of contents of the archive
			-v iff specified with -t, print a verbose table of contents of the archive
			-d delete named files from the archive
			-A quickly append all “regular” files in the current directory (except the archive itself)
			-w Extra credit: for a given timeout, add all modified files to the archive. (except the archive itself)

 */
 
 

#include <dirent.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <utime.h>

#include <myar.h>
#include "myar.h"


void ToC(char *archive, int verbosity);

int main(int argc, char *argv[]){
	int option = 0;
	int setOpt = 0;
	int printVerbose = 0;
    char *theArchive;

	
	while ((option = getopt(argc, argv, "q:x:tvd:Aw")) != -1) //colon after options -> requires input file
	{
		switch(option)
		{
		case 'q':
		// append named files to archive
			setOpt = 1;
			break;
		case 'x':
		//extract named files from archive
			setOpt = 2;
			break;
		case 't':
		//print a concise table of contents of archive
			setOpt = 3;
			break;
		case 'v':
		//if specified with t, print a verbose table of contents of archive
			printVerbose = 1;
			break;
		case 'd':
		// delete named files from archive
			setOpt = 4;
			break;
		case 'A':
		//Append all regular files in current directory
			setOpt = 5;
			break;
		case 'w':
		//Extra credit: for a given time-out, add all modified files to archive.
			setOpt = 6;
			break;
			
		default:
			printf("error, wrong input");
			exit(EXIT_FAILURE);
		}
	}
	
	
//	theArchive = argv[2];   

	theArchive = argv[optind++];  //in case there were multiple entries(like -v -t)
	
	printf("You chose option '%s' with value '%s'\n",argv[1], theArchive);
	
	
	//do table and append all first. They don't require file inputs.
	
	if(setOpt == 1)
	{
		ToC(theArchive, printVerbose);
	}
	

	return 0;
	
}

/* Description: 
*  Prints a ToC listing of the names of what is in the archive.
*  If verbosity is = 1, then it prints all the info of each file.
*/
void ToC(char *archive, int verbosity)
{
	FILE *openArc = fopen(archive, "r");
	
	
	fclose(openArc);
	
}














