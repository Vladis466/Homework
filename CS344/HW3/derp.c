Example program
Listing 26-5 provides an example of a more complex SIGCHLD handler. This handler
displays the process ID and wait status of each reaped child q. In order to see that
multiple SIGCHLD signals are not queued while the handler is already invoked, execution
of the handler is artificially lengthened by a call to sleep() w. The main program
creates one child process for each (integer) command-line argument r. Each of
these children sleeps for the number of seconds specified in the corresponding
command-line argument and then exits t. In the following example of the execution
of this program, we see that even though three children terminate, SIGCHLD is
only queued twice to the parent:
$ ./multi_SIGCHLD 1 2 4
16:45:18 Child 1 (PID=17767) exiting
16:45:18 handler: Caught SIGCHLD First invocation of handler
16:45:18 handler: Reaped child 17767 - child exited, status=0
Monitoring Child Processes 557
16:45:19 Child 2 (PID=17768) exiting These children terminate during…
16:45:21 Child 3 (PID=17769) exiting first invocation of handler
16:45:23 handler: returning End of first invocation of handler
16:45:23 handler: Caught SIGCHLD Second invocation of handler
16:45:23 handler: Reaped child 17768 - child exited, status=0
16:45:23 handler: Reaped child 17769 - child exited, status=0
16:45:28 handler: returning
16:45:28 All 3 children have terminated; SIGCHLD was caught 2 times
Note the use of sigprocmask() to block the SIGCHLD signal before any children are created
in Listing 26-5 e. This is done to ensure correct operation of the sigsuspend() loop
in the parent. If we failed to block SIGCHLD in this way, and a child terminated
between the test of the value of numLiveChildren and the execution of the
sigsuspend() call (or alternatively a pause() call), then the sigsuspend() call would block
forever waiting for a signal that has already been caught y. The requirement for
dealing with this type of race condition was detailed in Section 22.9.
Listing 26-5: Reaping dead children via a handler for SIGCHLD
–––––––––––––––––––––––––––––––––––––––––––––––––– procexec/multi_SIGCHLD.c
#include <signal.h>
#include <sys/wait.h>
#include "print_wait_status.h"
#include "curr_time.h"
#include "tlpi_hdr.h"
static volatile int numLiveChildren = 0;
/* Number of children started but not yet waited on */
static void
sigchldHandler(int sig)
{
int status, savedErrno;
pid_t childPid;
/* UNSAFE: This handler uses non-async-signal-safe functions
(printf(), printWaitStatus(), currTime(); see Section 21.1.2) */
savedErrno = errno; /* In case we modify 'errno' */
printf("%s handler: Caught SIGCHLD\n", currTime("%T"));
while ((childPid = waitpid(-1, &status, WNOHANG)) > 0) {
q printf("%s handler: Reaped child %ld - ", currTime("%T"),
(long) childPid);
printWaitStatus(NULL, status);
numLiveChildren--;
}
if (childPid == -1 && errno != ECHILD)
errMsg("waitpid");
558 Chapter 26
w sleep(5); /* Artificially lengthen execution of handler */
printf("%s handler: returning\n", currTime("%T"));
errno = savedErrno;
}
int
main(int argc, char *argv[])
{
int j, sigCnt;
sigset_t blockMask, emptyMask;
struct sigaction sa;
if (argc < 2 || strcmp(argv[1], "--help") == 0)
usageErr("%s child-sleep-time...\n", argv[0]);
setbuf(stdout, NULL); /* Disable buffering of stdout */
sigCnt = 0;
numLiveChildren = argc - 1;
sigemptyset(&sa.sa_mask);
sa.sa_flags = 0;
sa.sa_handler = sigchldHandler;
if (sigaction(SIGCHLD, &sa, NULL) == -1)
errExit("sigaction");
/* Block SIGCHLD to prevent its delivery if a child terminates
before the parent commences the sigsuspend() loop below */
sigemptyset(&blockMask);
sigaddset(&blockMask, SIGCHLD);
e if (sigprocmask(SIG_SETMASK, &blockMask, NULL) == -1)
errExit("sigprocmask");
r for (j = 1; j < argc; j++) {
switch (fork()) {
case -1:
errExit("fork");
case 0: /* Child - sleeps and then exits */
t sleep(getInt(argv[j], GN_NONNEG, "child-sleep-time"));
printf("%s Child %d (PID=%ld) exiting\n", currTime("%T"),
j, (long) getpid());
_exit(EXIT_SUCCESS);
default: /* Parent - loops to create next child */
break;
}
}
Monitoring Child Processes 559
/* Parent comes here: wait for SIGCHLD until all children are dead */
sigemptyset(&emptyMask);
while (numLiveChildren > 0) {
y if (sigsuspend(&emptyMask) == -1 && errno != EINTR)
errExit("sigsuspend");
sigCnt++;
}
printf("%s All %d children have terminated; SIGCHLD was caught "
"%d times\n", currTime("%T"), argc - 1, sigCnt);
exit(EXIT_SUCCESS);
}
–––––––––––––––––––––––––––––––––––––––––––––––––– procexec/multi_SIGCHLD.c


















































The principal advantages of system() are simplicity and convenience:
.. We don’t need to handle the details of calling fork(), exec(), wait(), and exit().
.. Error and signal handling are performed by system() on our behalf.
.. Because system() uses the shell to execute command, all of the usual shell processing,
substitutions, and redirections are performed on command before it is
executed. This makes it easy to add an “execute a shell command” feature to an
application. (Many interactive applications provide such a feature in the form
of a ! command.)
The main cost of system() is inefficiency. Executing a command using system()
requires the creation of at least two processes—one for the shell and one or more
for the command(s) it executes—each of which performs an exec(). If efficiency or
speed is a requirement, it is preferable to use explicit fork() and exec() calls to execute
the desired program.
The return value of system() is as follows:
.. If command is a NULL pointer, then system() returns a nonzero value if a shell is
available, and 0 if no shell is available. This case arises out of the C programming
language standards, which are not tied to any operating system, so a shell
might not be available if system() is running on a non-UNIX system. Furthermore,
even though all UNIX implementations have a shell, this shell might not
#include <stdlib.h>
int system(const char *command);
See main text for a description of return value
580 Chapter 27
be available if the program called chroot() before calling system(). If command is
non-NULL, then the return value for system() is determined according to the
remaining rules in this list.
.. If a child process could not be created or its termination status could not be
retrieved, then system() returns –1.
.. If a shell could not be execed in the child process, then system() returns a value
as though the child shell had terminated with the call _exit(127).
.. If all system calls succeed, then system() returns the termination status of the
child shell used to execute command. (The termination status of a shell is the termination
status of the last command it executes.)
It is impossible (using the value returned by system()) to distinguish the case
where system() fails to exec a shell from the case where the shell exits with the
status 127 (the latter possibility can occur if the shell could not find a program
with the given name to exec).
In the last two cases, the value returned by system() is a wait status of the same
form returned by waitpid(). This means we should use the functions described in
Section 26.1.3 to dissect this value, and we can display the value using our
printWaitStatus() function (Listing 26-2, on page 546).
Example program
Listing 27-7 demonstrates the use of system(). This program executes a loop that
reads a command string, executes it using system(), and then analyzes and displays
the value returned by system(). Here is a sample run:
$ ./t_system
Command: whoami
mtk
system() returned: status=0x0000 (0,0)
child exited, status=0
Command: ls | grep XYZ Shell terminates with the status of…
system() returned: status=0x0100 (1,0) its last command (grep), which…
child exited, status=1 found no match, and so did an exit(1)
Command: exit 127
system() returned: status=0x7f00 (127,0)
(Probably) could not invoke shell Actually, not true in this case
Command: sleep 100
Type Control-Z to suspend foreground process group
[1]+ Stopped ./t_system
$ ps | grep sleep Find PID of sleep
29361 pts/6 00:00:00 sleep
$ kill 29361 And send a signal to terminate it
$ fg Bring t_system back into foreground
./t_system
system() returned: status=0x000f (0,15)
child killed by signal 15 (Terminated)
Command: ^D$ Type Control-D to terminate program
Program Execution 581
Listing 27-7: Executing shell commands with system()
–––––––––––––––––––––––––––––––––––––––––––––––––––––– procexec/t_system.c
#include <sys/wait.h>
#include "print_wait_status.h"
#include "tlpi_hdr.h"
#define MAX_CMD_LEN 200
int
main(int argc, char *argv[])
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