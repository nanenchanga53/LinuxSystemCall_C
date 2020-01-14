#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

//작성 include -----
#include "student.h"

int main(int argc, char *argv[])
{
	char c;
	int fd, id;
	struct student record;
        if (argc < 2)
        {
		fprintf(stderr, "사용법 : %s file\n", argv[0]);
		exit(1);
	}

//작성 파일 열기 시작 -----

        if ((fd = open(argv[1], O_RDONLY)) == -1)
        {
                perror(argv[1]);
                exit(2);
        }


//작성 파일 열기 종료 -----

	do {
		printf("\n검색할 학생의 학번 입력(1000):");
                if (scanf("%d", &id) == 1)
                {
//작성 파일 위치 포인터 이동 및 값 읽기 시작 -----

                    lseek(fd, (id-START_ID)*sizeof(record), SEEK_SET);
                    if ((read(fd, (char *) &record, sizeof(record)) > 0) && (record.id != 0))
                    {
                            printf("이름:%s\t 학번(1000):%d\t 점수:%d\n", record.name, record.id, record.score);
                    } else
                    {
                            printf("레코드 %d 없음\n", id);
                    }

//작성 파일 위치 포인터 이동 및 값 읽기 종료 -----
                }
                else
                {
			 printf("입력 오류");
		}

		printf("계속하겠습니까?(Y/N)");
		scanf(" %c", &c);

        }
        while (c=='Y');

	close(fd);
	exit(0);
}

