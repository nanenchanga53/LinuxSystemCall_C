#include <sys/types.h>
#include <wait.h>
#include <stdio.h>
int main(void)
{
	pid_t pid;
	pid = fork();
        if ( pid != 0 ) /* parent process */
        {
                int icnt = 0;

		// 작업 좀비프로세스 해결 소스 작성 시작 -----
                while(1)
                {
                    sleep(1);
                    icnt++;

                    if(icnt == 15)
                    {
                        int child, status;
                        child = wait(&status); // 어떤 프로세스든 끝나기를 기다린다.
                        printf("\t종료 코드 %d\n", status>>8);
                    }

                }


		// 작업 좀비프로세스 해결 소스 작성 종료 -----
	}
        else /* child process */
        {
		sleep(10);
		exit(42);
	}	
	return 0;
}

