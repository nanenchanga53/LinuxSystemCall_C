#include <stdio.h> 
#include <unistd.h> 
#include <pthread.h> 


/// 데드락 발생조건
/// 1. 공유자원에 대한 동시접근 불가
/// 2. 점유하고 기다리기
/// 3. 자원의 권한을 뺏어오지 못함
/// 4. 순환 형태로 대기함


int ncount1 = 1;    // 쓰레드간 공유되는 자원
int ncount2 = 1;    // 쓰레드간 공유되는 자원
pthread_mutex_t  mutex1 = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t  mutex2 = PTHREAD_MUTEX_INITIALIZER;

void* do_loop(void *data){
	int i; 
	while(1)
	{  
// 작업 데드락 발생 조건 시작 -----
		
















// 작업 데드락 발생 조건 종료 -----
	}
}

void* do_loop2(void *data){    
	int i;   
	while(1)
	{  
// 작업 데드락 발생 조건 시작 -----
		
















// 작업 데드락 발생 조건 종료 -----
	}
}   

 
int main()
{    
	int thr_id;    
	pthread_t p_thread[2];    
	int status;    
	int a = 1;      
	thr_id = pthread_create(&p_thread[0], NULL, do_loop, (void *)&a);    
	sleep(1);    
	thr_id = pthread_create(&p_thread[1], NULL, do_loop2, (void *)&a);    
	
	pthread_join(p_thread[0], (void *) &status);    
	pthread_join(p_thread[1], (void *) &status);    

	status = pthread_mutex_destroy(&mutex1);    
	printf("code  =  %d\n", status);    
	status = pthread_mutex_destroy(&mutex2);    
	printf("finished\n");    
	return 0;
}
