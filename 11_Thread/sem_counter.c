#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdio.h>

#define MAX_THREAD  3

// 공유변수
int count = 0;
int go = 0;

void *myThreadFunc(void *data);

struct sembuf mysem_open = {0, -1, SEM_UNDO};
struct sembuf mysem_close = {0, 1, SEM_UNDO};

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

	semid = semget(2345, 1, IPC_CREAT|IPC_EXCL|0666);
        if(semid == -1)
        {
		perror("semget error (alloc)");		
		semid = semget(2345, 1, IPC_CREAT|0666);
	}

        s_union.val = 1; // 세마포어 카운터 : 2개일때는 동시에 실행해서 값이 똑같은게 찍히는 경우가 있다 1로하면 1개씩만 실행된다
        if(semctl(semid, 0, SETVAL, s_union) == -1)
        {
		return 1;
	}

        for(i = 0; i < MAX_THREAD; i++)
        {
		thr_id = pthread_create(&pt[i], NULL, myThreadFunc, (void *)&i);
                if(thr_id < 0)
                {
			perror("Thread Create Error"); 
			return 1;
		}
		sleep(1);
	}	
	usleep(10000);
	go = 1;

        for(i = 0; i < MAX_THREAD; i++)
        {
		pthread_join(pt[i], NULL);
	}	

    if (semctl(semid, 0, IPC_RMID, s_union) == -1)
    {
        printf( "semctl()-IPC_RMID Fail\n");
        return -1;
    }
}

void *myThreadFunc(void *data){
	int thread_num = *(int *)data;
	int lnum;
	printf("Thread Create %d\n", thread_num);

	while(go == 0)
	{
	}
	printf("GO [%d]\n", thread_num);
        while(1)
        {
		semop(semid, &mysem_open, 1);
		fprintf(stderr, "IN [%d] count : %d\n", thread_num, count);
		usleep(10);
		
		lnum = count; 	
		lnum = lnum+1; 	
		count = lnum;

		fprintf(stderr, "[%d] count : %d\n", thread_num, count);
		fprintf(stderr, "-----OUT [%d]\n", thread_num);
		semop(semid, &mysem_close, 1);
		usleep(10);
		if(lnum >=20)
		{
			break;
		}
	}
}
