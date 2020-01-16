#include <stdio.h>
#include <unistd.h>

void intHandler();

/* 부모 프로세스가 자식 프로세스를 생성하고 끝나기를 기다린다. */
int main() 
{
	int pid1, pid2, child, status;
	printf("[%d] 부모 프로세스 시작 \n", getpid( ));

	pid1 = fork();
        if (pid1 == 0)
        {
		printf("[%d] 자식1 프로세스 시작 \n", getpid( ));
		exit(1);
	}

	pid2 = fork();
        if (pid2 == 0)
        {
		printf("[%d] 자식2 프로세스 시작 \n", getpid( ));
		exit(1);
	}

	// 작업 --- 어떤프로세스든 끝나기를 기다린다 작업 시작 -----
        child = wait(&status); // 어떤 프로세스든 끝나기를 기다린다.
        printf("[%d] 자식 프로세스 %d 종료 \n", getpid(), child);



	// 작업 --- 어떤프로세스든 끝나기를 기다린다 작업 종료 -----
        child = wait(&status); // 어떤 프로세스든 끝나기를 기다린다.
        printf("[%d] 자식 프로세스 %d 종료 \n", getpid(), child);

        //커널에는 새로운 프로세스가 스택으로 쌓이기 때문에 역순으로 실행된다.
        //정순으로 만들고 싶으면 대기시간을 줘서 실행이 먼저되게 하자
	printf("\t종료 코드 %d\n", status>>8);
}

void intHandler(int signo)
{
        printf("인터럽트 시그널 처리\n");
        printf("시그널 번호: %d\n", signo);
        exit(0);
}

