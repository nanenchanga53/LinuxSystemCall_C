#include <stdio.h>
#include <signal.h>

/* 알람 시그널을 처리 */
// 작업 알람 핸들러 선언 -----
void alarmHandler();

int main( )
{
	// 작업 알람 시그널 핸들러 등록 -----
        signal(SIGALRM,alarmHandler);
	alarm(5);

	printf("무한 루프 \n");

        while (1)
        {
		sleep(1);
		printf("1초 경과 \n");
	}

	printf("실행되지 않음 \n");
}


// 작업 알람 핸들러 내용 작성 시작 -----
void alarmHandler()
{
        printf("알람 발생\n");
        exit(0);
}
// 작업 알람 핸들러 내용 작성 종료 -----
