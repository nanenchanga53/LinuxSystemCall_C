#include <stdio.h>
#define MAXLINE 80

/* 텍스트 파일에 줄 번호 붙여 프린트한다. */
int main(int argc, char *argv[])
{
	FILE *fp;
	int line = 0;
	char buffer[MAXLINE];

        if (argc != 2)
        {
		fprintf(stderr,  "사용법:line 파일이름\n");
		exit(1);
	}

	if ( (fp = fopen(argv[1],"r")) == NULL)
	{
		fprintf(stderr, "파일 열기 실패");
		exit(2);
	}

	// 작성 fgets를 이용한 파일 내용 읽고 화면에 print 시작 -----

        while (fgets(buffer, MAXLINE, fp) != NULL)
        { // 한 줄 읽기
                line++;
                printf("%3d %s", line, buffer);
        }



	// 작성 fgets를 이용한 파일 내용 읽고 화면에 print 종료 -----
	exit(0);
}
