#include <unistd.h>
#define MAXLINE 100

/* 파이프를 통해 자식에서 부모로 데이터를 보내는 프로그램 */
 int main( )
{
	int n, length, fd[2];
	int pid;
	char message[MAXLINE], line[MAXLINE];

	// 작업 파이프 생성 -----
        pipe(fd);

        if ((pid = fork()) == 0)/* 자식 프로세스 */
        {
		close(fd[0]);
		sprintf(message, "Hello from PID  %d\n", getpid());
		length = strlen(message)+1;
		// 작업 생성한 파이프에 데이터 쓰기 -----
                write(fd[1], message,length);
        }
        else /* 부모 프로세스 */
        {
		close(fd[1]);
		// 작업 생성한 파이프에서 데이터 읽기 -----
                n = read(fd[0], line, MAXLINE);
                printf("[%d] %s", getpid(), line);

	}

	exit(0);
 }
