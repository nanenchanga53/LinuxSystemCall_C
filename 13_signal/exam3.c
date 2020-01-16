#include <sys/types.h>
#include <wait.h>
#include <stdio.h>
int main()
{
        pid_t pid;

        printf("Parent process : pid = %d, ppid = %d\n", getpid(), getppid());

        pid = fork();

        if (pid != 0)
        {
                printf("parent start");
        }
        else /* child process */
        {
            sleep(2);
            execl("exam2", NULL, NULL, NULL);
            exit(1);

        }

        printf("parent close\n");

        //ps -ef | grep [process id]
}

