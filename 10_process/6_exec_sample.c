#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
/* 세 개의 자식 프로세스를 생성하여 각각 다른 명령어를 실행한다. */
int main( ) 
{
	printf("부모 프로세스 시작\n");

        if (fork( ) == 0)
        {
                execl("atexitExample",NULL, NULL, NULL);
                fprintf(stderr,"4 번째 실패");
                exit(3);
        }
        usleep(100);

        if (fork( ) == 0)
        {
                execl("b.out", NULL, NULL);
		fprintf(stderr,"첫 번째 실패");
		exit(1);
	}
	usleep(100);
        if (fork( ) == 0)
        {
                execl("/bin/date", "date", NULL);
		fprintf(stderr,"두 번째 실패"); 
		exit(2);
	}
        usleep(100);
        if (fork( ) == 0)
        {
		execl("/bin/ls","ls", "-l", NULL);
		fprintf(stderr,"세 번째 실패");  
		exit(3);
	}



	int child, status;
        child = wait(&status); // 어떤 프로세스든 끝나기를 기다린다.
        child = wait(&status); // 어떤 프로세스든 끝나기를 기다린다.
        child = wait(&status); // 어떤 프로세스든 끝나기를 기다린다.
        child = wait(&status); // 어떤 프로세스든 끝나기를 기다린다.

	printf("부모 프로세스 끝\n");
}
