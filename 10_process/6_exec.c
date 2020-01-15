#include <stdio.h> 

int main( ) 
{
	printf("부모 프로세스 시작\n");

	// 작업 자식프로세스 생성 후 exec 수행 시작 -----


        if (fork( ) == 0)
        {
                execl("/bin/echo", "echo", "hello", NULL);
                fprintf(stderr,"첫 번째 실패");
                exit(1);
        }
        if (fork( ) == 0)
        {
                execl("/bin/date", "date", NULL);
                fprintf(stderr,"두 번째 실패");
                exit(2);
        }
        if (fork( ) == 0)
        {
                execl("/bin/ls","ls", "-l", NULL);
                fprintf(stderr,"세 번째 실패");
                exit(3);
        }

        if (fork( ) == 0)
        {
                execl("atexitExample",NULL, NULL, NULL); //atexitExample
                fprintf(stderr,"4 번째 실패");
                exit(3);
        }


	// 작업 자식프로세스 생성 후 exec 수행 종료 -----

	printf("부모 프로세스 끝\n");
}
