#include <stdio.h>
#include <stdlib.h>

// 작업 핸들러 선언 -----
static void exit_handler1(void), exit_handler2(void);

int main(void)
{

// 작업 핸들러 등록 시작 -----

    if (atexit(exit_handler1) != 0)
    {
            perror("exit_handler1 등록할 수 없음");
    }
    if (atexit(exit_handler2) != 0)
    {
            perror("exit_handler2 등록할 수 없음");
    }

// 작업 핸들러 등록 종로 -----
    printf("main 끝 \n");
    exit(0);
}

static void exit_handler1(void)
{
	printf("첫 번째 exit 처리기\n");
}

static void exit_handler2(void)
{
	printf("두 번째 exit 처리기\n");
}
