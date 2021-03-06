#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

#include <wait.h>
#define MAX_THREAD  1

void *myThreadFunc(void *data);


// 작업 세마포어 p 연산 ----- 세마포어를 사용하며 차감
struct sembuf mysem_open = {0,-1,SEM_UNDO};

// 작업 세마포어 v 연산 ----- 세마포어를 사용완료하며 더한
struct sembuf mysem_close = {0, 1, SEM_UNDO};

union snum
{
        int val;
};

static int semid;

int main(int argc, char *argv[])
{

    union snum s_union;
    int i;
    int thr_id;
    pthread_t pt[MAX_THREAD];


    semid = semget(2345, 1, IPC_CREAT|IPC_EXCL|0666);//없으면 세마포어를 만들겠다는 설정으로 연결

    if(semid == -1)
    {
        perror("semget error (alloc)");
        semid = semget(2345, 1, IPC_CREAT|0666);
    }
    s_union.val = 1;// 세마포어 카운터

    if(semctl(semid, 0, SETVAL, s_union) == -1)
    {
        //
        return 1;
    }


    for(i = 0; i< MAX_THREAD; i++)
    {
        thr_id = pthread_create(&pt[i], NULL, myThreadFunc, (void *)&i);
        if(thr_id < 0)
        {
                perror("Thread Create Error");
                return 1;
        }
        usleep(100);
    }

    // 작업 세마포어 생성 종료 -----

    for(i = 0; i < MAX_THREAD; i++)
    {
        pthread_join(pt[i], NULL);
    }

    // 작업 세마포어 해제 시작 -----
    if(semctl(semid, 0, IPC_RMID, s_union) == -1)
    {
        printf("semctl()-IPC_RMID Fail\n");
        return -1;
    }

}

void *myThreadFunc(void *data)
{
        FILE *ft;
        char *filename = "event.txt";
        int thread_num = *(int *)data;
        int lnum;
        char messages[100];

        // 작업 세마포어 사용 시작 -----
        semop(semid, &mysem_open, 1);

        ft = fopen(filename,"w");
        printf("input message : ");
        scanf("%s", &messages);

        fprintf(ft,"%s",messages);
        printf("program end\n");
        sleep(1);


        // 작업 세마포어 사용 종료 -----
        semop(semid, &mysem_close, 1);

}

