#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t addcond = PTHREAD_COND_INITIALIZER;
pthread_cond_t subcond = PTHREAD_COND_INITIALIZER;

int flag = 0;

void *th1_func(void *arg)
{
// 작업 뮤텍스 signal, wait 시작 -----

    int i = 0;

    printf("in th1 \n");
    while(i <= 10)
    {
            pthread_mutex_lock(&mutex);

            printf("th1 proc #1 :: %d flag :%d \n",i, flag);
            i++;
            flag = 1;
            printf("th1 proc #2 :: %d flag :%d \n",i, flag);

            pthread_cond_signal(&addcond);
            pthread_cond_wait(&subcond,&mutex);
            pthread_mutex_unlock(&mutex);

    }
    // 작업 뮤텍스 signal, wait 종료 -----
    return NULL;

}


void *th2_func(void *arg)
{
// 작업 뮤텍스 signal, wait 시작 -----

    int i = 0;

    printf("in th2 \n");
    while(i <= 10)
    {
            pthread_mutex_lock(&mutex);

            if(flag == 0)
            {
                    pthread_cond_wait(&addcond, &mutex);
            }

            printf("=====th2 proc #1 :: %d flag :%d \n",i, flag);
            flag = 0;
            printf("=====th2 proc #2 :: %d flag :%d \n",i, flag);
            i++;

            pthread_cond_signal(&subcond);
            pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


int main()
{
	pthread_t threadID1, threadID2;

	pthread_create(&threadID1, NULL, th1_func, NULL);
	usleep(100);
	pthread_create(&threadID2, NULL, th2_func, NULL);

	pthread_join(threadID1, NULL);
	pthread_join(threadID2, NULL);

	printf("pthread wait finish !! \n"); 
	return 0;
}
