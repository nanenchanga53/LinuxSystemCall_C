#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#define DEFAULT_PROTOCOL 0
#define MAXLINE 100

int readLine(int fd, char* str);

/* 소문자-대문자 변환: 클라이언트 프로그램 */
int main()
{
	int clientfd, result;
	char inmsg[MAXLINE], outmsg[MAXLINE];
	struct sockaddr_un serverUNIXaddr;

	clientfd = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);

	serverUNIXaddr.sun_family = AF_UNIX;
	strcpy(serverUNIXaddr.sun_path, "convert");

        do /* 연결 요청 */
        {
		result = connect(clientfd, &serverUNIXaddr, sizeof(serverUNIXaddr));
                if (result == -1)
                {
			sleep(1);
		}
	} while (result == -1);

	printf("변환할 문자열 입력:\n");
	fgets(inmsg, MAXLINE, stdin);
	write(clientfd,inmsg,strlen(inmsg)+1); // 변환할 문자열 보내기
	/* 소켓으로부터 변환된 문자열을 한 줄 읽어서 프린트 */
	readLine(clientfd,outmsg);
	printf("%s --> \n%s", inmsg, outmsg);
	close(clientfd);
	
	return 0;
}

/* 한 줄 읽기 */
int readLine(int fd, char* str)
{
	int n;
        do
        {
		n = read(fd, str, 1);
        }
        while(n > 0 && *str++ != NULL);
	return(n > 0);
}
