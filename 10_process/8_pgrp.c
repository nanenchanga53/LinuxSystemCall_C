#include <sys/types.h> 
#include <unistd.h> 

int main()
{
	int pid, gid;
	printf("PARENT: PID = %d  GID = %d \n", getpid(), getpgrp());
	pid = fork();
        if (pid == 0)
        {
		// 작업 그룹id 변경 -----
                setpgid(0,0);
		printf("CHILD: PID = %d  GID = %d  PPID = %d \n", getpid(), getpgrp(), getppid());
		exit(255);
	}


	int child, status;
        child = wait(&status);  // 어떤 프로세스든 끝나기를 기다린다.
	printf("\t종료 코드 %d\n", status>>8);
	printf("PARENT: PID = %d  GID = %d  CPID = %d \n", getpid(), getpgrp(), pid);
}
