/*
*	Assignment 3 CS 344 Summer 2015
*	Create a program to mimic the functionality of linux system command.
*	Design a shell.
*
*/

#define _POSIX_C_SOURCE 200809L
#define _BSD_SOURCE

#include <unistd.h>
#include <sys/types.h>

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "print_wait_status.h"
#include "curr_time.h"
#include "tlpi_hdr.h"
#define MAX_CMD_LEN 200

int theSystem(char *command);

int main(int argc, char *argv[])
{
char str[MAX_CMD_LEN]; /* Command to be executed by system() */
	int status; /* Status return from system() */
	for (;;) { /* Read and execute a shell command */
		printf("Command: ");
		fflush(stdout);
		if (fgets(str, MAX_CMD_LEN, stdin) == NULL)
			break; /* end-of-file */
			status = system(str);
			printf("system() returned: status=0x%04x (%d,%d)\n",
			(unsigned int) status, status >> 8, status & 0xff);
		if (status == -1) {
			errExit("system");
		} else {
			if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
			printf("(Probably) could not invoke shell\n");
			else /* Shell successfully executed command */
			printWaitStatus(NULL, status);
		}
	}
	exit(EXIT_SUCCESS);
}



int theSystem(char *command)
{
	int status;
	pid_t childPid;
	switch (childPid = fork()) 
	{
		case -1: /* Error */
			return -1;
			Program Execution 583
		case 0: /* Child */
			execl("/bin/sh", "sh", "-c", command, (char *) NULL);
			_exit(127); /* Failed exec */
		default: /* Parent */
			if (waitpid(childPid, &status, 0) == -1)
			return -1;
		else
		return status;
	}
}