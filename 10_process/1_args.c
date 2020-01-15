#include <stdio.h>
/* 모든 명령줄 인수를 출력한다. */
int main(int argc, char *argv[])
{
	int i;

	printf("---------------------------------------\n");
	printf("-----------------argv------------------\n");
	printf("---------------------------------------\n");

        for (i = 0; i < argc; i++)
        {     /* 모든 명령줄 인수 출력 */
		printf("argv[%d]: %s \n", i, argv[i]);
	}


	printf("---------------------------------------\n");
	printf("------------------env------------------\n");
	printf("---------------------------------------\n");

	char **ptr;
	extern char **environ;
	/* 모든 환경 변수 값 출력*/
        for (ptr = environ; *ptr != 0; ptr++)
        {
		printf("%s \n", *ptr);
	}

	exit(0);
}
