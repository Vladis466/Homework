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
 
#define _BSD_SOURCE 

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
#include <ctype.h>
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
char *trigger;

char *PermissionFiles(mode_t perm);
void appendFiles(const char *archive, const char *files[], int num_files);
void buildHeader(struct ar_hdr *hdr, const struct stat *st, char *fName);
void fHeader(const char *file, const struct stat *st, struct ar_hdr *hdr);
void wrFileAr(int archive, int fd, struct stat *st);
void appALL(const char *archive);
void deleteFiles(const char *Ar, const char **delFiles ,int i);

void print_archive(const char *archive, int verbs);
void print_hdr(struct ar_hdr *hdr);
void evenLength( int fd, struct ar_hdr *file_header);

int main(int argc, char *argv[])
{	
	//int fd;
	int i = 0;
	int verbosity = 0;
    int option = 0;
	int setOpt = 0;
    const char *theArchive;
    const char *files[argc];

    while ((option = getopt(argc, argv, "Adqtvw:x")) != -1) {
        switch (option) {
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
			verbosity = 1;
            break;
        case 'd':
            // delete named files from archive
			setOpt = 4;
            break;
        case 'A':
            setOpt = 6;
            //Append all regular files in current directory
            break;
        case 'w':
            //Extra credit: for a given time-out, add all modified files to archive.
           
            break;

        default:
			printf("error, invalid input");
			exit(EXIT_FAILURE);
        }
    }



    theArchive = argv[optind++];		//next value after options is the archive
	while (optind < argc) { files[i++] = argv[optind++]; }	
	if (setOpt == 3)
	{
		//fd = open(theArchive, O_RDWR);
		print_archive(theArchive, verbosity);
	}
	if (setOpt == 4) { deleteFiles(theArchive, files, i); }
	if (setOpt == 6) { appALL(theArchive); }
	
	
	
 //   for (i = optind; i <argc; i++)


    if (setOpt == 1) {
            appendFiles(theArchive, files, i);
	}
   return 0;
}


void deleteFiles(const char *aR, const char **delFiles ,int i)
{
	struct ar_hdr file_header;
    int name_size = 0;
    int fd;
    int size;
    ssize_t buf;
	int d = 0;
	if(delFiles[0] == NULL) {
		printf("No files entered. GoodBye. \n");
		exit(EXIT_FAILURE);
	}
	printf("%s\n", delFiles[0]);
	printf("%s\n", delFiles[1]);
	char arHeadtext[8];
    fd = open(aR, O_RDONLY);
    read(fd, arHeadtext, 8);

}





/*
 * 
 * Builds the header for the file in the archive.   
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



void fHeader(const char *file, const struct stat *st, struct ar_hdr *hdr)
{
    char filename[16];
	char extra[200];
    int i = 0;
	int j = 15;

    while(i < strlen(file)) {			
		if(i == 15) {
			while (j < strlen(file)){
				extra[j] = file[j];
				j++;							//Beginning to deal with the extended names
			}
		trigger = filename;
		break;
		}
        filename[i] = file[i];
        i++;
//		printf("%s \n", filename);
    }
    filename[i++] = '/';
    while(i < 16) {
        filename[i++] = ' ';
    }
	printf("%s \n", filename);
	buildHeader(hdr, st, filename);
	

}


/*
 * 
 *	Writes contents of the file 
 *  into the archive at the file specified.
 *   
 */
void wrFileAr(int archive, int fd, struct stat *st)
{
    ssize_t readBlock;
    char* buf[st->st_blksize];

    while((readBlock = read(fd, buf, st->st_blksize)) != 0) {	//read chars from filename into a buffer
        write(archive, buf, readBlock);    
    }

    
    if((st->st_size % 2) == 1) { (write(archive, "\n", 1));  } //where st_size = filesize add new line if odd length
}

/*
 * 
 *
 *	Append files to the desired archive.
 *  If archive does not exist, create it and then append the files.
 */
void appendFiles(const char *archive, const char *files[], int num_files)
{
    int fd;				//for archive
	int fd1;			//for files
    struct stat st;					//To keep all the info for the header
    struct ar_hdr file_hdr;	
	
	//Create the archive and append files. If archive exists, just append.
    fd = open(archive, O_APPEND | O_RDWR| O_EXCL | O_CREAT, SATANPERMS);
		if(fd == -1) { open(archive, O_APPEND | O_RDWR, SATANPERMS); }
		//EXCL will make open fail if the archive exists. Added this second line
		//because I was having a bad reading, some issues...DAMNIT FOOOOo
	
	
	write(fd, "!<arch>\n", 8);	//Writes header of archive file for UNIX into the new archive.(Check how to make so not always?)	
	
	
	
    for (int i = 0; i < num_files; i++) {
		fd1 = open(files[i], O_RDONLY);			//link selected file using fd1
	    stat(files[i], &st);					//Get info into stat struct from fd1
	    fHeader(files[i], &st, &file_hdr);	//build header for file in archive
		write(fd, &file_hdr, 60);				//write file header into archive
		wrFileAr(fd, fd1, &st);					//write file into archive
    }		

    close(fd);
}


/* Append all regular files 
 * 
 * get list of regular files in current directory (except archive
 *   itself)
 *  - uses stat and checks file type
 * pass list to 'quick append' function
 *
 */
void appALL(const char *archive)
{
    char **files;
    DIR *openDIR;
    struct dirent *ed;
    int fileCount = 0;

  

	openDIR = opendir(".");		// "." specifies current directory

    files = (char **) malloc( sizeof(char *) * 50);

    while ((ed = readdir(openDIR)) != NULL) {
        if(ed->d_type == DT_REG && strcmp(ed->d_name, archive) != 0) {  //to not copy ARCHIVE file
            files[fileCount++] = ed->d_name;
        }
    }

    closedir(openDIR);
    
    appendFiles(archive, (const char **)files, fileCount);
    free(files);
}


    


void print_archive(const char *archive, int verbs)
{
    int name_size = 0;
    int fd;
    int size;
    ssize_t buf;
    struct ar_hdr file_header;

	char arHeadtext[8];
    fd = open(archive, O_RDONLY);
    read(fd, arHeadtext, 8);

    while((buf = read(fd, &file_header, 60)) == 60) {
        size = 0;
		name_size = 0;
        if (buf == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (memcmp(file_header.ar_fmag, ARFMAG, 2) != 0) {
            fprintf(stderr, "Bad read.\n");
            exit(EXIT_FAILURE);
        }

        if(verbs == 1) {
            print_hdr(&file_header);
        } else {
            while(file_header.ar_name[name_size] != '/') { ++name_size; }
            printf("%.*s\n", name_size, file_header.ar_name);
        }
		
		evenLength(fd, &file_header);
		

    }

    close(fd);
}

void evenLength( int fd, struct ar_hdr *hdrFile)
{	
	int size = 0;
	
	if ((size = strtol(hdrFile->ar_size, (char **)NULL, 10)) == LONG_MIN
			|| size == LONG_MAX)
	{
		perror("strtol");
		exit(EXIT_FAILURE);
	}

	/* Compensate for '\n' when the file length is even */
	if ((size % 2) == 1) {
		size++;
	}

	if (lseek(fd, size, SEEK_CUR) == -1) {
		perror("lseek");
		exit(EXIT_FAILURE);
	}

}


//Fix time to print the header to correctly and prints all the values getting the info from stat.
void print_hdr(struct ar_hdr *hdr)
{
	int Nsize = 0;
    mode_t perms;
    mode_t *ps = &perms;
    time_t date;
    long fileUid;
    long fileGid;
    long fileSize;

    char date_str[20];


	
    sscanf(hdr->ar_mode, "%lo", (long *) ps);
    sscanf(hdr->ar_uid, "%ld", &fileUid);
    sscanf(hdr->ar_gid, "%ld", &fileGid);
    sscanf(hdr->ar_date, "%ld", &date);
    sscanf(hdr->ar_size, "%ld", &fileSize);

    strftime(date_str, 20, "%b %d %H:%M %Y", localtime(&date));

    printf("%8s %ld/%ld %6ld %10s",
            PermissionFiles(perms), fileUid, fileGid, fileSize, date_str);
			
		while(hdr->ar_name[Nsize] != '/') { ++Nsize; }
	printf("  %.*s  \n ", Nsize, hdr->ar_name);		//Dat Name size broken...

}

char *PermissionFiles(mode_t perm)
{
	static char ret[sizeof("rwxrwxrwx")];

	snprintf(ret, sizeof("rwxrwxrwx"), "%c%c%c%c%c%c%c%c%c",
		 ((perm & S_IRUSR) ? 'r' : '-'),
		 ((perm & S_IWUSR) ? 'w' : '-'),
		 ((perm & S_IXUSR) ? ((perm & S_ISUID) ? 's' : 'x') :
		  ((perm & S_ISUID) ? 'S' : '-')),
		 ((perm & S_IRGRP) ? 'r' : '-'),
		 ((perm & S_IWGRP) ? 'w' : '-'),
		 ((perm & S_IXGRP) ? ((perm & S_ISGID) ? 's' : 'x') :
		  ((perm & S_ISGID) ? 'S' : '-')),
		 ((perm & S_IROTH) ? 'r' : '-'),
		 ((perm & S_IWOTH) ? 'w' : '-'),
		 ((perm & S_IXOTH) ? ((perm & S_ISVTX) ? 't' : 'x') :
		  ((perm & S_ISVTX) ? 'S' : '-')));

	return (ret);
}

//Record of resources for personal use.

//http://www.gnu.org/software/libc/manual/html_node/Streams-and-File-Descriptors.html
//https://en.wikipedia.org/wiki/Ar_(Unix)
//http://linux.die.net/man/3/


