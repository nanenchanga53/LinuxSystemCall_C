#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
        int shmid;
        void *shared_memory = (void *)0;

        char buff[1024];
        int skey = 5678;
        int *process_num;
        int local_num;    // 공유메모리 공간을 만든다.

        shmid = shmget((key_t)skey, sizeof(int), 0666|IPC_CREAT);

        if(shmid == -1)
        {
                perror("shmget failed : ");
                exit(0);
        }

        printf("Key %d\n", skey); // 공유메모리를 맵핑한다.
        shared_memory = shmat(shmid, (void *)0, 0);
        if(!shared_memory)
        {
                perror("shmat failed : ");
                exit(0);
        }

        process_num = (int *)shared_memory;

        local_num = 0;
        while(local_num < 10)
        {
                local_num++;
                *process_num = local_num;
                printf("changed mem\n");
                sleep(1);
        }

        printf("process_num is %d\n", (int)*process_num);
        sleep(5);
}

