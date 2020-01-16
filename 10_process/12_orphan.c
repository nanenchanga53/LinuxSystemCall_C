#include <sys/types.h>
#include <wait.h>
#include <stdio.h>
int main()
{
	pid_t pid;

	printf("Parent process : pid = %d, ppid = %d\n", getpid(), getppid());

	pid = fork();

        if ( pid != 0 )/* parent process */
        {

                printf("Parent process : pid = %d, ppid = %d\n", getpid(), getppid());
		printf("fork-child process : pid = %d\n", pid);

        }
        else /* child process */
        {
		sleep(5);
		printf("child process : pid = %d, ppid = %d\n", getpid(), getppid());
        }
        /* parent & child process */
	printf("pid %d terminates.. \n", getpid()); 

        //ps -ef | grep [process id]
}

