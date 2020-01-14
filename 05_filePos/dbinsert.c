#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// 작성 include -----
#include "student.h"

int main(int argc, char *argv[])
{
// 작성 필요변수 시작 -----
    int fd;
    struct student record;
// 작성 필요변수 종료 -----


    if (argc < 2)
    {

        fprintf(stderr, "사용법 : %s file\n", argv[0]);
        exit(1);
    }

// 작성 파일열기 시작 -----





// 작성 파일열기 종료 -----

	printf("%-9s %-8s %-4s\n", "학번(1000)", "이름", "점수");

// 작성 입력받은 후 위치 지정 및 저장 시작 -----

        while (scanf("%d %s %d", &record.id, record.name, &record.score) == 3)
        {
                lseek(fd, (record.id - START_ID) * sizeof(record), SEEK_SET);
                write(fd, (char *) &record, sizeof(record) );
        }



// 작성 입력받은 후 위치 지정 및 저장 종료 -----

	close(fd);
	exit(0);
}

