#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
/* 부모 프로세스가 자식 프로세스를 생성하고 끝나기를 기다린다. */
int main() 
{
	int pid1, pid2, child, status;
	printf("[%d] 부모 프로세스 시작 \n", getpid( ));

	pid1 = fork();
        if (pid1 == 0)
        {
		printf("[%d] 자식1 프로세스 시작 \n", getpid( ));
                exit(1); //kid1 exit
	}

	// 작업 시차 주기 -----
        //커널에는 새로운 프로세스가 스택으로 쌓이기 때문에 역순으로 실행된다.
        //정순으로 만들고 싶으면 대기시간을 줘서 실행이 먼저되게 하자
        usleep(100);

	pid2 = fork();
        if (pid2 == 0)
        {
		printf("[%d] 자식2 프로세스 시작 \n", getpid( ));
                exit(1); // kid2 exit
	}

	// 작업 waitpid -----
        child = waitpid(pid2, &status, 0); //자식2가 죽는것만을 확인
	printf("[%d] 자식2 프로세스 %d 종료 \n", getpid( ), child);
	printf("\t종료 코드 %d\n", status>>8);
        //parent exit
}
