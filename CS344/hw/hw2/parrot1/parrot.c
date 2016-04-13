/* Specifcally for getopt */
#include <ctype.h>
#include <getopt.h>

/* Standard libraries */
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

/* System call prototypes! */
#include <unistd.h>

/* File information */
#include <sys/stat.h>

/* errno, and error constants */
#include <errno.h>



#define BSIZE 128

void parrot(FILE* fd_in, FILE* fd_out)
{
	char buff [BSIZE];
	while(1){
		fgets(buff, BSIZE, fd_in);
		fputs(buff, fd_out);
	}
	return;
}


int print_file(FILE* fd_in, FILE* fd_out)
{
	// We'll be working on this today.
	return 0;
}

int main(int argc, char** argv)
{
	//printf("Parroting away\n");
	int parrot_mode = 0;

	int file_mode = 0;
	char* file_value = NULL;
	FILE* fd_in  = stdin;
	FILE* fd_out = stdout;
	int current;

	opterr = 0;

	char* help_str = "Usage: \n parrot -p, or parrot -f file.\n";

	while( (current = getopt(argc, argv, "pf:")) != -1 )
	{
		//printf("Parsing argument: %c\n", current);
		switch(current)
		{
		case 'f':
			file_mode = 1;
			file_value = optarg;
			break;
		case 'p':
			parrot_mode = 1;
			break;
		case '?':
			if( optopt == 'f')
			{
				fprintf(stderr, "Option -f requires an argument, specifically a filename.\n");
			}
			fprintf(stderr, help_str);
			return 1;

		default:
			fprintf(stderr, help_str);
			return 1;
        }
	}


	if(file_mode)
	{
		fd_in = fopen(file_value,"r");
	}

	if(parrot_mode && file_mode)
	{
		print_file(fd_in, fd_out);
		fclose(fd_in);
		fd_in = stdin;
		fd_out = fopen(file_value, "w+");
		parrot(fd_in, fd_out);
	}
	else if(file_mode)
    {
	    print_file(fd_in, fd_out);
    }
	else if(parrot_mode)
	{
		parrot(fd_in, fd_out);
	}
	else
	{
		fprintf(stderr, help_str);
	}

	return 0;
}
