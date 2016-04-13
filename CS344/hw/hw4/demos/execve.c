#define _POSIX_C_SOURCE 200910L

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char** argv)
{
	execve("/bin/ls", argv, environ);
}
