#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int flag = 0;

void *th1_func(void *arg)
{
	int i = 0;

	printf("in th1 \n");
	while(i <= 10)
	{
		pthread_mutex_lock(&mutex);

		printf("th1 proc #1 :: %d flag :%d \n",i, flag);
		i++;
		flag = 1;
		printf("th1 proc #2 :: %d flag :%d \n",i, flag);

		sleep(2);
		pthread_mutex_unlock(&mutex);

	}
	return NULL;
}


void *th2_func(void *arg)
{
	int i = 0;

        while(i <= 10)
        {
                sleep(1);
                printf("in th2 \n");
                // 작업 뮤텍스 trylock 시작 -----
                if(pthread_mutex_trylock(&mutex)==0)
                {
                    printf("=====th2 proc #1 :: %d flag :%d \n",i, flag);
                    flag = 0;
                    printf("=====th2 proc #2 :: %d flag :%d \n",i, flag);
                    i++;
                    pthread_mutex_unlock(&mutex);
                }
        }
// 작업 뮤텍스 trylock 종료 -----
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
