#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define DEFAULT_PROTOCOL 0
#define MAXLINE 100

int listenfd, connfd, port, clientlen;

/* 한 줄 읽기 */
void readLine(int fd, char* str)
{
	int n;
	do {
		n = read(fd, str, 1);
	} while(n > 0 && *str++ != NULL);
	return(n > 0);
}

void intHandler(int signo)
{
	printf("인터럽트 시그널 처리\n"); 
	printf("시그널 번호: %d\n", signo);
	close(listenfd);
	shutdown(listenfd, SHUT_RDWR);
	shutdown(connfd, SHUT_RDWR);
	exit(0);
}

/* 파일 서버 프로그램 */
int main (int argc, char* argv[])
{
	signal(SIGINT,intHandler);

	FILE *fp;
	char inmsg[MAXLINE], outmsg[MAXLINE];
	struct sockaddr_in serveraddr, clientaddr;
	struct hostent *hp;
	char *haddrp;
	signal(SIGCHLD, SIG_IGN);

	if (argc != 2) {
		fprintf(stderr, "사용법: %s <port>\n", argv[0]);
		exit(0);
	}
	port = atoi(argv[1]);

	listenfd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);

	bzero((char *) &serveraddr, sizeof(serveraddr));

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons((unsigned short)port);
	
	int option = 1;
    setsockopt( listenfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option) );

	bind(listenfd, &serveraddr, sizeof(serveraddr));
	listen(listenfd, 5);


	while (1) {
		clientlen = sizeof(clientaddr);
		printf("접속대기\n");
		connfd = accept(listenfd, &clientaddr, &clientlen); 

		/* 클라이언트의 도메인 이름과 IP 주소 결정 */
		hp = gethostbyaddr((char *)&clientaddr.sin_addr.s_addr,
		sizeof(clientaddr.sin_addr.s_addr), AF_INET);
		haddrp = inet_ntoa(clientaddr.sin_addr);

		printf("서버: %s (%s) %d에 연결됨\n", hp->h_name, haddrp, clientaddr.sin_port);

		if (fork ( ) == 0) {
			readLine(connfd, inmsg); /* 소켓에서 파일 이름을 읽는다 */
			fp = fopen(inmsg, "r");

			if (fp == NULL) {
				write(connfd, "해당 파일 없음", 10);

			} else { /* 파일에서 한 줄씩 읽어 소켓을 통해 보낸다 */
				while(fgets(outmsg, MAXLINE, fp) != NULL) {
					write(connfd, outmsg, strlen(outmsg)+1);
				}
			}
			close(connfd);
			exit (0);
		} else {
			close(connfd);
		}
	}  // while
}  // main


