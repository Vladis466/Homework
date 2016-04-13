#define _POSIX_C_SOURCE 200809L

/* Standard libraries */
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

/* System call prototypes! */
#include <unistd.h>

/* File information */
#include <sys/stat.h>

/* File Control */
#include <fcntl.h>

/* errno, and error constants */
#include <errno.h>

// Default buffer size
#define BSIZE 128

void parrot(int fd_in, int fd_out)
{
	char buff [BSIZE];
	int nbytes = 0;
	while(1)
	{
		while((nbytes = read(fd_in, buff, BSIZE)) > 0)
		{
			if(write(fd_out, buff, nbytes) != nbytes)
				fprintf(stderr, "\nOops, couldn't write what was read.\n");
		}
	}
	return;
}


int print_in2out(int fd_in, int fd_out)
{
	char buff [BSIZE];
	int nbytes = 0;
	while((nbytes = read(fd_in, buff, BSIZE)) > 0)                          
	{                                                                       
		if(write(fd_out, buff, nbytes) != nbytes)                           
			fprintf(stderr, "\nOops, couldn't write as much as was read.\n");
	}                                                                       
	return 0;
}

int main(int argc, char** argv)
{

	// Modes and mode arguments.
	int parrot_mode      = 0;
	int file_mode        = 0;
	char* file_value     = NULL;
	int removal_mode     = 0;
	int informative_mode = 0;
	
	// Set default file descriptors.
	int fd_in  = STDIN_FILENO;
	int fd_out = STDOUT_FILENO;
	
	int read_options  = O_RDONLY | O_CREAT;
	int write_options = O_WRONLY | O_APPEND | O_SYNC;

	// Current argument parsed
	int current;

	// Set the getopt's opterr to a known (no error) value.
	opterr = 0;

	// Provide the user with consistent help
	char* help_str = "Usage: \n"
                     "parrot -[iprt] -f filename\n"
		             "\n"
		             "-i\tShow file information when specified with -f\n"
		             "-r\tRemove file when specified with -f.\n"
                     "\t\tIf specified with -p, the output will be written to stdout.\n"
                     "-p\tParrot input on stdin to either:\n"
		             "\t\tthe file specified with -f, or\n"
		             "\t\tstandard out.\n"
		             "-t\tWhen specified with -f, truncate the file after printing it.\n"
                     "-f\tPrint the contents of the specified file to stdin.\n";

	while( (current = getopt(argc, argv, "iprtf:")) != -1 )
	{
		//printf("Parsing argument: %c\n", current);
		switch(current)
		{
		case 'f': // File mode.
			file_mode = 1;
			file_value = optarg;
			break;
		case 'p': // Parrot mode.
			parrot_mode = 1;
			break;
		case 'i': // Informative mode. Stat the file -> print the results.
			informative_mode = 1;
			break;
		case 'r': // Remove the file.
			removal_mode = 1;
			break;
		case 't': // If specified with f, truncate the file after printing.
			break;
		case '?':
			if( optopt == 'f')
			{
				fprintf(stderr, "Option -f requires a filename arg.\n");
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
		fd_in = open(file_value, read_options, S_IRWXU);
		
		// Error Checking
		if(fd_in == -1)
		{
			// There has been a problem.
			fprintf(stderr, "Oops, something happened that we didn't handle. Exiting.\n");
			return -1;
		}
	}

	if(informative_mode && file_mode)
	{
		struct stat *st = (struct stat*)malloc(sizeof(struct stat));
		int ret = fstat(fd_in, st);
		fprintf(stdout,"%d, %d, %d", st->st_mode, st->st_nlinks, st->st_mtime);
	}

	if(parrot_mode && file_mode)
	{
		print_in2out(fd_in, fd_out);
		close(fd_in);
		fd_in = STDIN_FILENO;
		fd_out = open(file_value, write_options);
		parrot(fd_in, fd_out);
	}
	else if(file_mode)
    {
	    print_in2out(fd_in, fd_out);
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
