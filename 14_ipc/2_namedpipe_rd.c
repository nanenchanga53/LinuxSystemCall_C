#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAXLINE 100
/* 이름 있는 파이프를 통해 읽은 내용을 프린트*/
int main( ) 
{
        int fd;
        char str[MAXLINE];

// 작업 이름있는 파이프 생성 시작 -----
        unlink("myPipe");
        mkfifo("myPipe", 0660);
        fd = open("myPipe", O_RDONLY);
// 작업 이름있는 파이프 생성 종료 -----

        while (readLine(fd, str))
        {
		printf("%s \n", str);
	}

	close(fd);
	return 0;
}

int readLine(int fd, char *str)
{ 
	int n;
        do
        {
		n = read(fd, str, 1);
        }
        while (n > 0 && *str++ != NULL);
	return (n > 0);
}

