#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXLINE 256

int main() {
	int fd1, fd2, n;
	char inmsg[MAXLINE];

// 작업 이름있는 파이프 연결 시작 -----







// 작업 이름있는 파이프 연결 종료 -----

	printf("* 클라이언트 시작 \n");

	while(1) {
		n = read(fd1, inmsg, MAXLINE); 
		printf("[서버] -> %s\n", inmsg);
		printf("[클라이언트] : ");
		fgets(inmsg, MAXLINE, stdin);
		write(fd2, inmsg, strlen(inmsg)+1); 
	}
}

