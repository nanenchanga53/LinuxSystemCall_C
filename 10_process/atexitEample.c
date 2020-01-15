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

// 작업 - "log"파일을 'a'모드로 열고 "종료합니다" 메시지 저장
static void exit_handler1(void)
{
    FILE *fp;
    fp = fopen("log.txt", "a");

    fprintf(fp,"log a mode open and exit\n");
    printf("첫 번째 exit 처리기\n");
}

static void exit_handler2(void)
{
        printf("두 번째 exit 처리기\n");
}
