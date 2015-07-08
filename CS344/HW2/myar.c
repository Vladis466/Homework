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

#include <ar.h>
#include "myar.h"

// struct ar_hdr		/* archive file member header - printable ascii */
//{
//	char	ar_size[12];	/* file member size - decimal */
//	char	ar_nxtmem[12];	/* pointer to next member -  decimal */
//	char	ar_prvmem[12];	/* pointer to previous member -  decimal */			*Keeping to know what
//	char	ar_date[12];	/* file member date - decimal */					*arheader does.
//	char	ar_uid[12];	/* file member user id - decimal */
//	char	ar_gid[12];	/* file member group id - decimal */
//	char	ar_mode[12];	/* file member mode - octal */
//	char	ar_namlen[4];	/* file member name length - decimal */
//	union
//	{
//		char	ar_name[2];	/* variable length member name */
//		char	ar_fmag[2];	/* AIAFMAG - string to end header */
//	}	_ar_name;		/*      and variable length name */
//};

//returns a file 

char * /* Return ls(1)-style string for file permissions mask */
filePermStr(mode_t perm, int flags)
{
static char str[STR_SIZE];
snprintf(str, STR_SIZE, "%c%c%c%c%c%c%c%c%c",
(perm & S_IRUSR) ? 'r' : '-', (perm & S_IWUSR) ? 'w' : '-', (perm & S_IXUSR) ?
(((perm & S_ISUID) && (flags & FP_SPECIAL)) ? 's' : 'x') :
(((perm & S_ISUID) && (flags & FP_SPECIAL)) ? 'S' : '-'),
(perm & S_IRGRP) ? 'r' : '-', (perm & S_IWGRP) ? 'w' : '-', (perm & S_IXGRP) ?
(((perm & S_ISGID) && (flags & FP_SPECIAL)) ? 's' : 'x') :
(((perm & S_ISGID) && (flags & FP_SPECIAL)) ? 'S' : '-'),
(perm & S_IROTH) ? 'r' : '-', (perm & S_IWOTH) ? 'w' : '-',(perm & S_IXOTH) ?
(((perm & S_ISVTX) && (flags & FP_SPECIAL)) ? 't' : 'x') :
(((perm & S_ISVTX) && (flags & FP_SPECIAL)) ? 'T' : '-'));
return str;
}


void appendFiles(const char *archive, const char *files[], int num_files);
void buildHeader(struct ar_hdr *hdr, const struct stat *st, char *fName);
void fHeader(const char *file, const struct stat *st, struct ar_hdr *hdr);

void ToC(char *archive, int verbosity);

int main(int argc, char *argv[])
{	
	int printVerbose = 0;
    int option = 0;
	int setOpt = 0;
    const char *theArchive;
    const char *files[argc];

    while ((option = getopt(argc, argv, "Adqtvw:x")) != -1) {
        switch (option) {
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
	
	
 

	theArchive = argv[optind++];  //in case there were multiple entries(like -v -t)
	
	printf("You chose option '%s' with value '%s'\n",argv[1], theArchive);
	
	if (setOpt == 1) {
           appendFiles(theArchive, files, i);
	}
	
	if(setOpt == 3)
	{
		ToC(theArchive, printVerbose);
	}
	

	return 0;
	
}
/*
 * 
 *
 *
 *   
 */
void buildHeader(struct ar_hdr *hdr, const struct stat *st, char *fName)
{
	sprintf(hdr->ar_name, "%-16s", fName);
    sprintf(hdr->ar_date, "%-12ld", (long) st->st_mtime);
    sprintf(hdr->ar_uid, "%-6ld", (long) st->st_uid);
    sprintf(hdr->ar_gid, "%-6ld", (long) st->st_gid);
    sprintf(hdr->ar_mode, "%-8lo", (unsigned long) st->st_mode);
    sprintf(hdr->ar_size, "%-10lld", (long long) st->st_size);
    memcpy(hdr->ar_fmag, ARFMAG, 2);
}


/*
 * 
 *
 *
 *   
 */
void fHeader(const char *file, const struct stat *st, struct ar_hdr *hdr)
{
    char filename[16];
    int i = 0;
    while(i < strlen(file)) {			//Use strcpy instead..
        filename[i] = file[i];
        i++;
    }
    filename[i++] = '/';
    while(i < 16) {
        filename[i++] = ' ';
    }
	
	buildHeader(hdr, st, filename);
	

}


/*
 * 
 *
 *
 *   
 */
void appendFiles(const char *archive, const char *files[], int num_files)
{
    int fd;				//for archive
	int fd1;			//for files
    struct stat st;					//To keep all the info for the header
    struct ar_hdr file_hdr;	
	
	//Create the archive and append files. If archive exists, just append.
    fd = open(archive, O_APPEND | O_WRONLY| O_CREAT, SATANPERMS); 
	
	
	write(fd, "!<arch>\n", 8);	//Writes header of archive file for UNIX into the new archive.(Check how to make so not always?)	
	
	
	
    for (int i = 0; i < num_files; i++) {
		fd1 = open(files[i], O_RDONLY);			//link selected file using fd1
	    stat(files[i], &st);					//Get info into stat struct from fd1
	    fHeader(files[i], &st, &file_hdr);	//build header for file in archive
		write(fd, &file_hdr, 60);				//write file header into archive
		//NOT DONE~~~~~~~~				//write file into archive
    }		

    close(fd);
}



void ToC(char *archive, int verbosity)
{
	FILE *openArc = fopen(archive, "r");
	
	
	fclose(openArc);
	
}

















//Record of resources for personal use.

//http://www.gnu.org/software/libc/manual/html_node/Streams-and-File-Descriptors.html
//https://en.wikipedia.org/wiki/Ar_(Unix)
//http://linux.die.net/man/3/


/* Description: 
*  Prints a ToC listing of the names of what is in the archive.
*  If verbosity is = 1, then it prints all the info of each file.
*/













