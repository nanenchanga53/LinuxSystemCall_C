#include <stdio.h> 
#include <unistd.h> 
#include <pthread.h> 
int ncount;   // 쓰레드간 공유되는 자원
FILE *ft;

pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER; // 초기화

// 쓰레드 함수 1
void* do_loop(void *data)
{
	int i;   
	// 작업 뮤텍스 락 ----- 
        pthread_mutex_lock(&mutex); // 잠금을 생성한다.
        for (i = 0; i < 10; i++)
        {
                //pthread_mutex_lock(&mutex); // 잠금을 생성한다.
		printf("loop1 : %d\n", ncount);       
                fprintf(ft,"loop1 : %d\n",ncount);
		ncount ++;        
		sleep(1);    
                //pthread_mutex_unlock(&mutex); // 잠금을 해제한다.
	}    
	// 작업 뮤텍스 락 해제 -----
        pthread_mutex_unlock(&mutex); // 잠금을 해제한다.
}


void* do_loop2(void *data)
{
	int i;  
        // 잠금을 얻으려고 하지만 do_loop 에서 이미 잠금을
        // 얻었음으로 잠금이 해제 될 때까지 기다린다.

        pthread_mutex_lock(&mutex); // 잠금을 생성한다.
        for (i = 0; i < 10; i++)
        {
                //pthread_mutex_lock(&mutex); // 잠금을 생성한다.
                printf("loop2 : %d\n", ncount);
                fprintf(ft,"loop2 : %d\n",ncount);
                ncount --;
                sleep(1);
                //pthread_mutex_unlock(&mutex);// 잠금을 해제한다.
	}    
	// 작업 뮤텍스 락 해제 -----

        pthread_mutex_unlock(&mutex);// 잠금을 해제한다.
}   

 
int main()
{    
        ft = fopen("test.txt","a");
	int thr_id;    
	pthread_t p_thread[2];    
	int status;    
	int a = 1;    
	ncount = 0;    
	thr_id = pthread_create(&p_thread[0], NULL, do_loop, (void *)&a);    
        sleep(1);
	thr_id = pthread_create(&p_thread[1], NULL, do_loop2, (void *)&a);    
	
	pthread_join(p_thread[0], (void *) &status);    
	pthread_join(p_thread[1], (void *) &status);    

	// 작업 뮤텍스 해제 -----
        status = pthread_mutex_destroy(&mutex);

	printf("code  =  %d\n", status);    
	printf("finished\n");    
	return 0;

        //
}
