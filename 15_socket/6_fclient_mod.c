#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define DEFAULT_PROTOCOL 0
#define MAXLINE 100

int clientFd;

/* 한 줄 읽기 */
int readLine(int fd, char* str)
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
	close(clientFd);
	shutdown(clientFd, SHUT_RDWR);
	exit(0);
}

/* 파일 클라이언트 프로그램 */
int main (int argc, char* argv[])
{
	signal(SIGINT,intHandler);

	int port, result;
	char *host, inmsg[MAXLINE], outmsg[MAXLINE];
	struct sockaddr_in serverAddr;
	struct hostent *hp;
	if (argc != 3) {
		fprintf(stderr, "사용법 : %s <host> <port>\n", argv[0]);
		exit(0);
	}

	host = argv[1];
	port = atoi(argv[2]);
	clientFd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);

	/* 서버의 IP 주소와 포트 번호를 채운다. */
	if ((hp = gethostbyname(host)) == NULL) {
		perror("gethostbyname error"); // 호스트 찾기 오류
	}

	bzero((char *) &serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	bcopy((char *)hp->h_addr_list[0],
	(char *)&serverAddr.sin_addr.s_addr, hp->h_length);
	serverAddr.sin_port = htons(port);

	do { /* 연결 요청 */
		printf("연결요청\n");
		result = connect(clientFd, &serverAddr,  sizeof(serverAddr));
		if (result == -1) {
			sleep(1);
		}
	} while (result == -1);

	printf("파일 이름 입력:");
	scanf("%s", inmsg);
	write(clientFd,inmsg,strlen(inmsg)+1);

	/* 소켓으로부터 파일 내용 읽어서 프린트 */
	while (readLine(clientFd,outmsg)) {
		printf("%s", outmsg);
	}
	close(clientFd);
	exit(0);
}


