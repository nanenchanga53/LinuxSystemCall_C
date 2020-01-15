#include <stdio.h>
#include <fcntl.h>
/* 자식 프로세스의 표준 출력을 파일에 재지정한다. */
int main(int argc, char* argv[])
{
	int child, pid, fd, status;

        // 위치 1번
        // 부모 자식이 공유할 때
        fd = open(argv[1],O_CREAT| O_TRUNC| O_WRONLY, 0600);
        dup2(fd, 1);   // system Call 파일을 표준출력에 복제
        close(fd);

	pid = fork( );

        if (pid == 0)
        {
		// 작업 자식프로세스에서 특정 파일을 열어서 표준출력에 연결, 그리고 외부프로그램 실행 시작 ----
		
                // 위치 2번
                // 다른 프로세스로 대치되어도 fd테이블 정보는 남아있음
                //fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0600);
                //dup2(fd, 1);// 파일을 표준출력에 복제
                //close(fd);

                execvp(argv[2], &argv[2]);

		// 작업 자식프로세스에서 특정 파일을 열어서 표준출력에 연결, 그리고 외부프로그램 실행 종료 ----
		fprintf(stderr, "%s:실행 불가\n",argv[1]);

        }
        else
        {
		child = wait(&status);
		printf("[%d] 자식 프로세스 %d 종료 \n", getpid(), child);
		fprintf(stdout, "부모 프로세스 종료");
	}
        //./redirect r2file ls -l
        //./redirect r2file2 ls -l
}
