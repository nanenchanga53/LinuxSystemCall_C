#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdio.h>

#define MAX_THREAD  3

int count = 0;

void *myThreadFunc(void *data);

// 작업 세마포어 p 연산 -----
// 작업 세마포어 v 연산 -----

union snum
{
	int val;
};

static int semid;

int main(int argc, char **argv)
{
	int thr_id;
	int status;
	int i;
	union snum s_union;
	pthread_t pt[MAX_THREAD];

// 작업 세마포어 생성 시작 -----


















// 작업 세마포어 생성 종료 -----

	for(i = 0; i < MAX_THREAD; i++){
		pthread_join(pt[i], NULL);
	}	

// 작업 세마포어 해제 시작 -----
    



// 작업 세마포어 해제 종료 -----
}

void *myThreadFunc(void *data){
	int thread_num = *(int *)data;
	int lnum;
	printf("Thread Create %d\n", thread_num);

// 작업 세마포어 사용 시작 -----
















// 작업 세마포어 사용 종료 -----
}
