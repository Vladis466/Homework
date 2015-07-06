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



int main(int argc, char *argv[])
	int option;
	
	while ((option = getopt(argc, argv, "qxtvdAw:?")) != -1) 
	{
		switch(option)
		{
		case 'q':
			break;
		case 'x':
			break;
		case 't':
			break;
		case 'v':
			break;
		case 'd':
			break;
		case 'A':
			break;
		case 'w':
			break;
			
		default:
	}
	
	return 0;
	
}

















