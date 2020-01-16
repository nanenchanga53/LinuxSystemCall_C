#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
void p1();
void intHandler();
jmp_buf env;
jmp_buf env2;
// 작업 비지역 점프 시작 -----

int main()
{
        signal(SIGINT, intHandler);
        if (setjmp(env) != 0)
        {
                printf("인터립트로 인해 evn1로 이 후 종료\n");
                exit(0);
        }
        else
        {
                printf("처음 통과\n");
        }

        if (setjmp(env2) != 0)
        {
                printf("인터립트로 인해 evn2로 이 후 종료\n");
                exit(0);
        }
        else
        {
                printf("처음 통과\n");
        }
        p1();
}


void p1()
{
        while (1)
        {
                printf("루프\n");
                sleep(1);
        }
}

// 작업 비지역 점프 종료 -----
void intHandler()
{
        printf("인터럽트\n");
        longjmp(env, 1);
        //longjmp(env2, 1);
        //둘중 하나만 쓰자
}
