#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#define DEFAULT_PROTOCOL 0
#define MAXLINE 100

void toUpper(char* in, char* out);
int readLine(int fd, char* str);

/* 소문자를 대문자로 변환하는 서버 프로그램 */
int main ()
{
	int listenfd, connfd, clientlen;
	char inmsg[MAXLINE], outmsg[MAXLINE];
	struct sockaddr_un serverUNIXaddr, clientUNIXaddr;

	signal(SIGCHLD, SIG_IGN);
	clientlen = sizeof(clientUNIXaddr);

	listenfd = socket(AF_UNIX, SOCK_STREAM, DEFAULT_PROTOCOL);
	serverUNIXaddr.sun_family = AF_UNIX;
	strcpy(serverUNIXaddr.sun_path, "convert");
	unlink("convert");

	bind(listenfd, &serverUNIXaddr, sizeof(serverUNIXaddr));

	listen(listenfd, 5);

        while (1)
        { /* 소켓 연결 요청 수락 */
		connfd = accept(listenfd, &clientUNIXaddr, &clientlen);
                if (fork ( ) == 0)
                {
			/* 소켓으로부터 한 줄을 읽어 대문자로 변환하여 보냄 */
			readLine(connfd, inmsg);
			toUpper(inmsg, outmsg);
			printf("%s --> \n%s", inmsg, outmsg);
			write(connfd, outmsg, strlen(outmsg)+1);
			close(connfd);
			exit (0);

                }
                else
                {
			close(connfd);
		}
	}

	return 0;
}


/* 소문자를 대문자로 변환 */
void toUpper(char* in, char* out)
{
	int i;
        for (i = 0; i < strlen(in); i++)
        {
                if (islower(in[i]))
                {
			out[i] = toupper(in[i]);
                }
                else
                {
			out[i] = in[i];
		}
	}
	out[i] = NULL;
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
