#include <sys/types.h>
#include <wait.h>
#include <stdio.h>
int main(void)
{
	// 작업 좀비 프로세스 코드 시작 -----
        pid_t pid;
        pid = fork();
        if ( pid != 0 ) /* parent process */
        {

                while(1)
                {
                        sleep(1);
                }
        }
        else /* child process */
        {
                sleep(10);
                exit(42);
        }

	// 작업 좀비 프로세스 코드 종료 -----
        // &를 붙여 후면처리로 실행
        // ps
        // kill [number]
	return 0;
}

