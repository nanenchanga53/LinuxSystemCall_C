쓰레드
	프로세스와 다르게 하나의 영역안에서 분리

컴파일시 gcc 코스코드 뒤에 -pthread를 더해줘야함
gcc -o exe exe.c -pthread



동기화
세마포어(Semaphore) : 공유된 자원의 데이터를 여러 프로세스가 접근하는 것을 막는 것

뮤텍스(Mutex) : 공유된 자원의 데이터를 여러 쓰레드가 접근하는 것을 막는 것
출처: https://jwprogramming.tistory.com/13 [개발자를 꿈꾸는 프로그래머]

데드락을 방지하기 위해 양보하는 로직이 필요하다 계속 양보하는 스레드가 생기는걸 방지하기 위해 많이 스레드를 양보한것을 먼저 선점할 수 있도록 하는 스케줄링이 필요함

pthread_mutex_lock()함수는 아래의 에러코드를 반환한다.

EINVAL    뮤텍스가 잘못 초기화 되었다. 
EDEADLK    이미 잠금을 얻은 쓰레드가 다시 잠금을 요청할 때 (error checking 뮤텍스일 경우 사용할 수 있다) 

pthread_mutex_trylock()함수는 아래의 에러코드를 반환한다.
EBUSY    뮤텍스가 잠겨 있어서 잠금을 얻을 수 없다. 
EINVAL   뮤텍스가 잘못 초기화 되었다. 

https://stackoverflow.com/questions/54004239/qnx-pthread-mutex-lock-causing-deadlock-error-45-edeadlk
