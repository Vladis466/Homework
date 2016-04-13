#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>


//  Semaphores come in two flavors: named and unnamed
//    named: exist in the file system
//    unnamed: logical construct

//sem_open is variadic: sem_t *sem_open(const char *name, int oflag, ...);

int main(int argc, char **argv)
{
	sem_t *sem = sem_open("/my_very_own_semaphore", O_CREAT, 0777, 2);
	
	printf("%d: Waiting on semaphore\n", getpid()); 
	fflush(stdout);
	
	sem_wait(sem); // Decrement the semaphor
	
	printf("%d: obtained semaphore, doing \"work\"\n", getpid()); 
	fflush(stdout);
	sleep(5);

	sem_post(sem);
	printf("%d: released semaphore\n", getpid()); 
	fflush(stdout);

	sem_close(sem);

	return 0;
}
