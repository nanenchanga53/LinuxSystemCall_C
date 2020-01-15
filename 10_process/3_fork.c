#include <stdio.h>
#include <unistd.h>
/* 자식 프로세스를 생성한다. */
int main()
{ 
	int pid;
	printf("[%d] 프로세스 시작 \n", getpid());
        // 작업 자식 프로세스 생성 ----
        pid = fork();
        printf("[%d] 프로세스 : 리턴값 %d\n", getpid(), pid);

	// 작업 자식 프로세스 구분 조건문 시작 ----
        if(pid == 0) // 0 : 자식 프로세스
        {
		printf("[Child] : Hello, world pid=%d\n", getpid());
	}
        else // 부모 프로세스
        {
		printf("[Parent] : Hello, world pid=%d\n", getpid());
	}

        //부모프로세스가 죽고 난 후 자식 프로세스가 또
        //실행되게 되는데 이때 부모프로세스는 자신이
        //죽고 쉘에 죽은것을 알리지만 자식이
        //실행되고 있는것은 모르기때문에 명령창이 뜬 후 자식이 실행
        //이걸 방지하도록 짜야한다
}
