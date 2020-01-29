#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXLINE 256

int main()
{

	int fd1, fd2, n;
	char msg[MAXLINE];

// 작업 이름있는 파이프 연결 시작 ----- (하나의 파이프로 양방향 통신가능)
        if(mkfifo("./chatfifo1",0666) == -1)
        {
            perror("mkfifo");
            exit(1);
        }

        if(mkfifo("./chatfifo2", 0666) == -1)
        {
            perror("mkfifo");
            exit(2);
        }
        fd1 = open("./chatfifo1", O_WRONLY);
        fd2 = open("./chatfifo2", O_RDONLY);
        if(fd1 == -1 || fd2 == -1)
        {
            perror("open");
            exit(3);
        }
// 작업 이름있는 파이프 연결 종료 -----

	printf("* 서버 시작 \n");
        while(1)
        {
		printf("[서버] : ");
		fgets(msg, MAXLINE, stdin);
		n = write(fd1, msg, strlen(msg)+1);  
                if (n == -1)
                {
                        perror("write");
                        exit(1);
		}
		n = read(fd2, msg, MAXLINE);  
		printf("[클라이언트] -> %s\n", msg);
	}
}


