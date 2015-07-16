#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	pid_t p;
	pid_t child;
	int status;
	switch((p = fork()))
	{
	case 0:
		// I'm a child, 
		// and this code will only happen in the child
		printf("My PID is %d, and my parent is %d.\n",getpid(), getppid());
		execlp("ls", "ls","-l","-a","-t",(char*)NULL);
		break;
	case -1:
		// An error.
		perror("Oops, could not create a child.");
		exit(EXIT_FAILURE);
	default:
		// I'm the parent.
		// and this will only happen in the parent
		printf("My PID is %d and I spawned %d\n",getpid(), p);
		child = wait(&status);
		printf("My PID is: %d, and I waited on %d who exited with status %d.\n", getpid(), child, status);
		break;
	}
	
	// Both processes will execute this section.
	
	return 0;
}