#include <stdio.h>
#include <stdlib.h>

#include "student.h"
#include "dbproc.h"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "사용법 : %s file\n", argv[0]);
		exit(1);
	}

	// 프로그램 메인 루프 생성
	char op;
	int iExit = 0;
	while(1) {
		printf("\n\n어떤 작업을 수행하시겠습니까?(I:추가, Q:조회, U:갱신, C:DB초기화, E:종료) : ");
		scanf(" %c", &op);
		printf("[사용자 %c 선택]\n", op);

		switch(op) {
			case 'I':
				dbinsert(argv[1]);
				break;

			case 'Q':
				dbquery(argv[1]);
				break;

			case 'U':
				dbupdate(argv[1]);
				break;

			case 'C':
				remove(argv[1]);
				printf("\n\n초기화 후 종료합니다.\n");
				iExit = 1;
				break;

			case 'E':
				printf("\n\n종료합니다.\n");
				iExit = 1;
				break;
		}

		if(iExit == 1) {
			break;
		}
	}
}
