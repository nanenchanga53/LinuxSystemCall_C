#include <stdio.h>
#define MAXLINE 100

// 함수원형 작성 시작-----
void copy(char from[], char to[]);
char line[MAXLINE]; //입력 줄
char longest[MAXLINE];//가장 긴 줄

// 함수원형 작성 종료

int main()
{
   	int len;
   	int max;
   	max = 0;
   	while (gets(line) != NULL) {
            len = strlen(line);
            if(len > max)
            {
                max = len;
                copy(line, longest);
            }
	}

        if (max > 0)// 입력 줄이 있었다면
        {
            printf("%s", longest);
        }

// 버퍼 flush 후 코드 작성 시작-----


// 버퍼 flush 후 코드 작성 종료

   return 0;
}


void copy(char from[], char to[])
{
// copy 함수 구현 시작-----
    int i;
    i = 0;
    while((to[i] = from[i]) != '\0')
    {
        ++i;
    }
// copy 함수 구현 종료-----
}


