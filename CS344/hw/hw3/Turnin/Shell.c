/*
*	Assignment 3 CS 344 Summer 2015
*	Create a program to mimic the functionality of linux system command.
*	Design a shell.
*
*/

#define _POSIX_C_SOURCE 200809L
#define _BSD_SOURCE
#define MAX_CMD_LEN 200
#define MAX_ENAME 133
#define block_size 1024

#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
#include <math.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "curr_time.h"




//static void outputError(Boolean useErr, int err, Boolean flushStdout, const char *format, va_list ap);
//static void terminate(Boolean useExit3);
//void errExit(const char *format, ...);

void printWaitStatus(const char *msg, int status);
int theSystem(const char *command);
char **parser(const char *input);
int changeDir(char **parsedArgs);
void listDir();
void helperMayo();
void launchProg(char** parsedArgs);


struct pipe {
	int pIn[2];
	int pOut[2];
};



int main(int argc, char *argv[])
{
	char str[MAX_CMD_LEN]; /* Command to be executed by theSystem() */
	int status; /* Status return from system() */
	for (;;) { /* Read and execute a shell command */
	
	
	   char cwd[block_size];
	   if (getcwd(cwd, sizeof(cwd)) != NULL)
		   fprintf(stdout, "%s ", cwd);

			
		printf("TELL ME WHAT TO DO: \n");
		fflush(stdout);
		if (fgets(str, MAX_CMD_LEN, stdin) == NULL)
			break; /* end-of-file */
			if(strcmp(str, "exit") == 0)
			{
				//exit out
				exit(EXIT_SUCCESS);
			}
			if(strcmp(str, " ") != 0)
			{
			status = theSystem(str);
			}
			printf("system() returned: status=0x%04x (%d,%d)\n",
			(unsigned int) status, status >> 8, status & 0xff);
		if (status == -1) {
			//errExit("system");
			printf("The errExit function was simplified.");
			exit(EXIT_FAILURE);
		} else {
			if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
			printf("(Probably) could not invoke shell\n");
			else /* Shell successfully executed command */
			printWaitStatus(NULL, status);
		}
	}
	exit(EXIT_SUCCESS);
}



int theSystem(const char *command)
{
    sigset_t blockMask, origMask;
    struct sigaction saIgnore, saOrigQuit, saOrigInt, saDefault;
    pid_t childPid;
    int status, savedErrno;
	char ** parsedLine;						//the parsed command
    if (command == NULL)                /* Is a shell available? */
        return system(":") == 0;

    /* The parent process (the caller of system()) blocks SIGCHLD
       and ignore SIGINT and SIGQUIT while the child is executing.
       We must change the signal settings prior to forking, to avoid
       possible race conditions. This means that we must undo the
       effects of the following in the child after fork(). */

    sigemptyset(&blockMask);            /* Block SIGCHLD */
    sigaddset(&blockMask, SIGCHLD);
    sigprocmask(SIG_BLOCK, &blockMask, &origMask);

    saIgnore.sa_handler = SIG_IGN;      /* Ignore SIGINT and SIGQUIT */
    saIgnore.sa_flags = 0;
    sigemptyset(&saIgnore.sa_mask);
    sigaction(SIGINT, &saIgnore, &saOrigInt);
    sigaction(SIGQUIT, &saIgnore, &saOrigQuit);
	
	
	parsedLine = parser(command);
	
//		printf("[%s] \n", parsedLine[0]);
	
	
	if (strcmp(parsedLine[0],"|" == 0)
	{
	
		piped(parsedLine);
	
	
	
	}
	if(strcmp(parsedLine[0],"cd") == 0)
	{
		changeDir(parsedLine);
		
	} else if(strcmp(parsedLine[0],"help\n") == 0)
	{
		helperMayo();
		
	} else if(strcmp(parsedLine[0],"ls\n") == 0)
	{
//		printf("ls reads");
		listDir();
		
	} else if(strcmp(parsedLine[0],"exit\n") == 0)
	{	
		printf("killing children...\n");
		kill(childPid, SIGTERM);
		return 0;
	} else 

	{

	

    switch (childPid = fork()) {
    case -1: /* fork() failed */
        status = -1;
        break;          /* Carry on to reset signal attributes */

    case 0: /* Child: exec command */

        /* We ignore possible error returns because the only specified error
           is for a failed exec(), and because errors in these calls can't
           affect the caller of system() (which is a separate process) */
		
        saDefault.sa_handler = SIG_DFL;
        saDefault.sa_flags = 0;
        sigemptyset(&saDefault.sa_mask);

        if (saOrigInt.sa_handler != SIG_IGN)
            sigaction(SIGINT, &saDefault, NULL);
        if (saOrigQuit.sa_handler != SIG_IGN)
            sigaction(SIGQUIT, &saDefault, NULL);

        sigprocmask(SIG_SETMASK, &origMask, NULL);
		

		launchProg(parsedLine);
	
		// execl("/bin/sh", "sh", "-c", command, (char *) NULL);
        _exit(127);                     /* We could not exec the shell */

    default: /* Parent: wait for our child to terminate */

        /* We must use waitpid() for this task; using wait() could inadvertently
           collect the status of one of the caller's other children */

        while (waitpid(childPid, &status, 0) == -1) {
            if (errno != EINTR) {       /* Error other than EINTR */
                status = -1;
                break;                  /* So exit loop */
            }
        }
        break;
    }

    /* Unblock SIGCHLD, restore dispositions of SIGINT and SIGQUIT */

    savedErrno = errno;                 /* The following may change 'errno' */

    sigprocmask(SIG_SETMASK, &origMask, NULL);
    sigaction(SIGINT, &saOrigInt, NULL);
    sigaction(SIGQUIT, &saOrigQuit, NULL);

    errno = savedErrno;
	
	
	}
    return status;


}




char **parser(const char *input)		//Will only parse by spaces
{
	
	
	char ** cmnds = malloc(64 * sizeof(char *));
	char * dummy;
	int i = 0;
	dummy = strtok((char*)input, " ");	//parser
	
	
	while(dummy != NULL)
	{
	
		cmnds[i] = dummy;				//pointer at each parsed command line thinger majiger.
//		printf("%s\n",  cmnds[i]);		
		dummy = strtok (NULL, " ");		
		i++;
	}
	

//	printf("%s\n",  cmnds[1]);
	return cmnds;
}



int changeDir(char **parsedArgs)
{	
	parsedArgs[1][strlen(parsedArgs[1])-1] = '\0';
	
//	printf("%ld \n", strlen(parsedArgs[1]));
	printf("[%s] \n", parsedArgs[1]);
	if(parsedArgs[1] == NULL)
	{
		printf("no argument received");
	} else {
	if(chdir(parsedArgs[1]) == -1)
		perror("error with directory");
	}
	printf("cd succesful\n");
	
	return 1;
}

void listDir()
{
	DIR *curDir;
	struct dirent *dp;
	int i = 0;
	curDir = opendir(".");						//open current directory
	while ((dp = readdir(curDir)) != NULL)		//keeps pointing to the next thing in curDir
	{
		i++;
		printf("  %s   ", dp->d_name);
		if(i % 5 == 0)
			printf("\n\n");
	}
	printf("\n\n");	
	
	closedir(curDir);
	
	

}



void helperMayo()
{

	printf("               	VLADS HELPFUL LIST FOR HELPING PEOPLE \n\n");
	printf("to exit shell: 		 		exit \n\n");
	printf("to change directory: 			cd 'directory name' \n\n");
	printf("to list files in current directory: 	ls \n\n");
	printf("\n\n");

}

void launchProg(char** parsedArgs)
{

//	if (execve(parsedArgs[0], parsedArgs) == -1) 
//		perror("Not a command mate!");	
		
	if (execvp(parsedArgs[0], parsedArgs) == -1) 
		perror("Not a command mate!");		

}

void piped(char** parsedArgs)
{
        int     fd[2], nbytes;
        pid_t   childpid;
        char    string[] = "Hello, world!\n";
        char    readbuffer[80];

        pipe(fd);
        
        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
                /* Child process closes up input side of pipe */
                close(fd[0]);

                /* Send "string" through the output side of pipe */
                write(fd[1], string, (strlen(string)+1));
                exit(0);
        }
        else
        {
                /* Parent process closes up output side of pipe */
                close(fd[1]);

                /* Read in a string from the pipe */
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                printf("Received string: %s", readbuffer);
        }
        
        return(0);


}





























void                    /* Examine a wait() status using the W* macros */
printWaitStatus(const char *msg, int status)
{
    if (msg != NULL)
        printf("%s", msg);
//non-zero value if status was returned for a child process that terminated normally.
    if (WIFEXITED(status)) {	
        printf("child exited, status=%d\n", WEXITSTATUS(status));
//Evaluates to a non-zero value if status was returned for a child process that 
//terminated due to the receipt of a signal that was not caught 
    } else if (WIFSIGNALED(status)) {
        printf("child killed by signal %d (%s)",
                WTERMSIG(status), strsignal(WTERMSIG(status)));
#ifdef WCOREDUMP        /* Not in SUSv3, may be absent on some systems */
        if (WCOREDUMP(status))
            printf(" (core dumped)");
#endif
        printf("\n");
//If the value of WIFSTOPPED(stat_val) is non-zero, 
//this macro evaluates to the number of the signal that caused the child process to stop.
    } else if (WIFSTOPPED(status)) {
        printf("child stopped by signal %d (%s)\n",
                WSTOPSIG(status), strsignal(WSTOPSIG(status)));

#ifdef WIFCONTINUED     /* SUSv3 has this, but older Linux versions and
                           some other UNIX implementations don't */
    } else if (WIFCONTINUED(status)) {
        printf("child continued\n");
#endif

    } else {            /* Should never happen */
        printf("what happened to this child? (status=%x)\n",
                (unsigned int) status);
    }
}






//Websites linked below were used as learning guides for this assignment. 
//http://stephen-brennan.com/2015/01/16/write-a-shell-in-c/