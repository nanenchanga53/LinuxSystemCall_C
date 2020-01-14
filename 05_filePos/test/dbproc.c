#include "student.h"
#include "dbproc.h"

void dbinsert(char* filename)
{
	char c;
	int fd;
	struct student record;

	if ((fd = open(filename, O_WRONLY|O_CREAT|O_EXCL, 0640)) == -1) {
		if ((fd = open(filename, O_RDWR)) == -1) {
			perror(filename);
			exit(2);
		}
	}

	printf("%-9s %-8s %-4s\n", "학번(1000)", "이름", "점수");

	while (scanf("%d %s %d", &record.id, record.name, &record.score) == 3) {
		lseek(fd, (record.id - START_ID) * sizeof(record), SEEK_SET);
		write(fd, (char *) &record, sizeof(record) );

		printf("계속하겠습니까?(Y/N)");
		scanf(" %c", &c);

		if(c != 'Y') {
			break;
		}
	}
	close(fd);
}


void dbquery(char* filename)
{
	char c;
	int fd, id;
	struct student record;

	if ((fd = open(filename, O_RDONLY)) == -1) {
		perror(filename);
		exit(2);
	}

	do {
		printf("\n검색할 학생의 학번 입력(1000):");
		if (scanf("%d", &id) == 1) {
			lseek(fd, (id-START_ID)*sizeof(record), SEEK_SET);
			if ((read(fd, (char *) &record, sizeof(record)) > 0) && (record.id != 0)) {
				printf("이름:%s\t 학번(1000):%d\t 점수:%d\n", record.name, record.id, record.score);
			} else {
			 	printf("레코드 %d 없음\n", id);
			}
		} else {
			 printf("입력 오류");
		}

		printf("계속하겠습니까?(Y/N)");
		scanf(" %c", &c);

	} while (c=='Y');

	close(fd);
}


void dbupdate(char* filename)
{
	int fd, id;
	char c;
	struct student record;

	if ((fd = open(filename, O_RDWR)) == -1) {
		perror(filename);
		exit(2);
	}

	do {
		printf("수정할 학생의 학번 입력(1000): ");
		if (scanf("%d", &id) == 1) {
			lseek(fd, (long) (id-START_ID)*sizeof(record), SEEK_SET);
			if ((read(fd, (char *) &record, sizeof(record)) > 0) && (record.id != 0)) {
				printf("학번(1000):%8d\t 이름:%4s\t 점수:%4d\n", record.id, record.name, record.score);
				printf("새로운 점수: ");
				scanf("%d", &record.score);
				lseek(fd, (long) -sizeof(record), SEEK_CUR);
				write(fd, (char *) &record, sizeof(record));
			} else {
				printf("레코드 %d 없음\n", id);
			}
		} else {
			printf("입력오류\n");
		}

		printf("계속하겠습니까?(Y/N)");
		scanf(" %c",&c);

	} while (c == 'Y');
	close(fd);
}
