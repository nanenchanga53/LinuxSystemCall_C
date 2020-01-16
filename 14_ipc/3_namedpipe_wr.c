#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAXLINE 100
/* 이름 있는 파이프를 통해 메시지를 출력 */
int main( ) 
{
	int fd, length, i;
	char message[MAXLINE];
	sprintf(message, "Hello from PID %d", getpid());
	length = strlen(message)+1;

// 작업 이름있는 파이프 연결 시작 -----
        do
        {
            fd = open("myPipe", O_WRONLY);
            if(fd == -1) sleep(1);
        }
        while(fd == -1);

// 작업 이름있는 파이프 연결 종료 -----

        for (i = 0; i <= 3; i++)
        {
		write(fd, message, length);
		printf("sended\n");
		sleep(3);
	}
	close(fd);
	return 0;
}

