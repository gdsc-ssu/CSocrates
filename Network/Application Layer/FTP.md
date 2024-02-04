File Transfer Protocol. 파일을 주고 받기 위해 만들어진 프로토콜. 1971년에 원본 모델이 만들어졌다. (인류 최초 달 착륙 2년 후)
한국어로는 파일 전송 프로토콜이라고 읽음.

![](https://www.easymedia.net/__DATA/_editor/FTP%20%EC%9B%90%EB%A6%AC.png)

TCP/IP를 활용하여 파일을 전송한다. 

FTP를 사용해서 파일을 주고 받고 싶다면 FTP 서버와 FTP 클라이언트가 필요.

![](https://www.sharetechnote.com/image/Network_IP_Ftp01_Login.png)

TCP 연결 후 username, password를 전달하고, response 230을 받게 되면 연결 설정이 된다.

# 연결 종류

2가지 연결 종류가 있다.

- 명령 연결
	- 제어 포트 (21번)로 사용자 인증, 명령을 위한 연결이 만들어짐.
	- 이를 통해 클라이언트에서 지시하는 명령어가 전달.
- 데이터 전송용 연결
	- 실제의 파일을 전송하기 위한 연결.
		- 능동 모드 (엑티브) : 20번 포트에서 클라이언트가 지정한 지점으로의 데이터 연결을 만듦.
		- 수동 모드 (패시브) : 클라이언트가 서버가 지정한 서버 포트로 연결할 수 있게 함.
![](https://upload.wikimedia.org/wikipedia/commons/thumb/8/84/Passive_FTP_Verbindung.svg/1920px-Passive_FTP_Verbindung.svg.png)
21번포트로 연결 요청을 한 다음(패시브로 요청) 후에 연결이 되면 지정된 포트 번호로 연결한다.
# 보안 측면
FTP는 보안 측면에서는 전혀 고려되지 않았기 때문에 다음 공격들에 대해 취약하다. (1999년 RFC에 발표된 취약점)
서버의 파일을 바꾸는 응용 계층인데, 암호를 단 한번만 확인하고, 이후 모든 권한을 취득하기 때문에 문제가 많다.
- 무차별 대입 공격 : brute-force로 암호를 대입해도 막기 힘들다.
- FTP 바운스 어택
	- FTP서버가 데이터를 전송할 때 목적지가 어디인지 검사하지 않는 설계상의 문제점을 이용한 공격
	* FTP서버의 전송 목적지 주소를 임의로 지정하여, FTP 서버를 경유해 임의의 목적지로 메시지나 자료를 전송하도록 할 수 있다.
	* 이를 통해 포트스캐닝을 할 수 있다.
- 패킷 캡쳐 (스니핑)
	- 별다른 암호화가 되어있지 않기 때문에 스니핑에 취약하다. (와이어샤크 등 관제 프로그램을 이용하여 패킷을 훔쳐보는 행위)
- 포트 훔치기 (다음에 열릴 포트를 추측하여 적절한 연결을 빼앗는 것)
- 스푸핑 공격
	- 자신이 서버로 위장하고 접속을 받는 방식.
- 사용자 이름 열거
	- 악의적인 사용자가 계정 이름 목록을 확인할 수 있음.
- 서비스 거부 공격
=> SFTP (ssh를 활용한 ftp), SCP (Secure Copy) 등 ssh를 활용한 파일 전송을 통해 해결한다.

# 구현

TCP/IP를 통한 연결을 하기 때문에 소켓 통신이 필요하다.

사실은 요청과 실제 파일 통신의 포트가 달라야 하지만, 간단한 파일 전송을 구현하기 위해 하나의 포트로 연결.

https://crazythink.github.io/2018/06/03/ftp/
여기 코드를 기반으로 작성.

sendfile 함수의 원형이 bsd 기반에서는 다르기 때문에 바꾸어 넣었다. (darwin 9.0에 처음 나왔다 : 2007년)
sendfile은 두 디스크립터 간 데이터를 복사하는 역할을 하며, 커널 내에서 원자적으로 이루어지기 때문에 read & write 조합보다 안정적이다.

- Linux의 sendfile(2) (https://man7.org/linux/man-pages/man2/sendfile.2.html)
```c
#include <sys/sendfile.h>

ssize_t sendfile(int out_fd, int in_fd, off_t *_Nullable offset, size_t count);
```
- out_fd : 수신측 파일 디스크립터(소켓)
- in_fd : 송신측 파일 디스크립터 (in_fd에 해당하는 파일을 out_fd에 쓴다.)
- offset : in_fd의 오프셋
- count : 보낼 크기

- BSD의 sendfile(2) (https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man2/sendfile.2.html)
```c
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>

int
sendfile(int fd, int s, off_t offset, off_t *len, struct sf_hdtr *hdtr, int flags);
```
- fd : 송신측 파일 디스크립터
- s : 수신측 파일 디스크립터(소켓) (fd에 해당하는 파일을 s에 쓴다.)
- offset : fd의 오프셋
- len : 보낼 크기, 함수 수행 이후엔 보낸 바이트가 저장됨.
- hdtr : 헤더와 트레일러. 즉 파일 앞과 뒤에 붙게 되는 iovec 정보.
- flag : 플래그. 잘 사용하지 않음. 0이 아닌 값이 들어가면 오류.



```c
/*
server.c

$ gcc -o server server.c
$ ./server 9999
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

int tcp_listen(int host, int port, int backlog) {
	int sd;
	struct sockaddr_in servaddr;

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket fail");
		exit(1);
	}
	// servaddr 구조체의 내용 세팅
	bzero((char *)&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(host);
	servaddr.sin_port = htons(port);
	if (bind(sd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		perror("bind fail");  exit(1);
	}
	// 클라이언트로부터 연결요청을 기다림
	listen(sd, backlog);
	return sd;
}

int main(int argc, char *argv[])
{
	struct sockaddr_in server, client;
	struct stat obj;
	int sock1, sock2;
	char buf[100], command[5], filename[20];
	int k, i, size, c;
    socklen_t len;
	int filehandle;

	sock1 = tcp_listen(INADDR_ANY, atoi(argv[1]), 5);

	len = sizeof(client);
	sock2 = accept(sock1, (struct sockaddr*)&client, &len);
	while (1) {
		recv(sock2, buf, 100, 0);
		sscanf(buf, "%s", command);
		if (!strcmp(command, "ls")) {//ls명령어를 입력받았다면
			system("ls >temps.txt");
			stat("temps.txt", &obj);
			size = obj.st_size;
			send(sock2, &size, sizeof(int), 0);
			filehandle = open("temps.txt", O_RDONLY);
			// sendfile(sock2, filehandle, NULL, size);
            off_t sent = size;
			sendfile(filehandle, sock2, 0, &sent, NULL, 0);
            printf("sent : %lld bytes\n", sent);
		}
		else if (!strcmp(command, "get")) {//get명령어를 입력받았다면
			sscanf(buf, "%s%s", filename, filename);
			stat(filename, &obj);
			filehandle = open(filename, O_RDONLY);
			size = obj.st_size;
			if (filehandle == -1)
				size = 0;
			send(sock2, &size, sizeof(int), 0);
			if (size){
				// sendfile(sock2, filehandle, 0, NULL, NULL, size);
                off_t sent = size;
				sendfile(filehandle, sock2, 0, &sent, NULL, 0);
                printf("sent : %lld bytes\n", sent);
            }
		}
		else if (!strcmp(command, "put")) {//put명령어를 입력받았다면
			int c = 0, len;
			char *f;
			sscanf(buf + strlen(command), "%s", filename);
			recv(sock2, &size, sizeof(int), 0);

			while (1) {
				filehandle = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0666);
				if (filehandle == -1)
					sprintf(filename + strlen(filename), "_");
				else break;
			}
			f = malloc(size);
			recv(sock2, f, size, 0);
			c = write(filehandle, f, size);
			close(filehandle);
			send(sock2, &c, sizeof(int), 0);
		}
		else if (!strcmp(command, "pwd")) {//pwd명령어를 입력받았다면
			system("pwd>temp.txt");
			i = 0;
			FILE*f = fopen("temp.txt", "r");
			while (!feof(f)) buf[i++] = fgetc(f);
			buf[i - 1] = '\0';
			fclose(f);
			send(sock2, buf, 100, 0);
		}
		else if (!strcmp(command, "cd")) {//cd명령어를 입력받았다면
			if (chdir(buf + 3) == 0) c = 1;
			else c = 0;	
			send(sock2, &c, sizeof(int), 0);
		}
		else if (!strcmp(command, "bye") || !strcmp(command, "quit")) {
		//종료 명령어를 입력받았다면
			printf("FTP server quitting..\n");
			i = 1;
			send(sock2, &i, sizeof(int), 0);
			exit(0);
		}
	}
	return 0;
}
```


```c
/*
client.c

$ gcc -o client client.c
$ ./client 127.0.0.1 9999
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXLINE  511

int tcp_connect(int af, char *servip, unsigned short port) {
	struct sockaddr_in servaddr;
	int  s;
	// 소켓 생성
	if ((s = socket(af, SOCK_STREAM, 0)) < 0)
		return -1;
	// 채팅 서버의 소켓주소 구조체 servaddr 초기화
	bzero((char *)&servaddr, sizeof(servaddr));
	servaddr.sin_family = af;
	inet_pton(AF_INET, servip, &servaddr.sin_addr);
	servaddr.sin_port = htons(port);

	// 연결요청
	if (connect(s, (struct sockaddr *)&servaddr, sizeof(servaddr))
		< 0)
		return -1;
	return s;
}

int main(int argc, char *argv[])
{
	struct sockaddr_in server;
	struct stat obj;
	int sock;
	char bufmsg[MAXLINE];
	char buf[100], command[5], filename[MAXLINE], *f;
	char temp[20];
	int k, size, status;
	int filehandle;

	if (argc != 3) {
		printf("사용법 : %s server_ip port\n", argv[0]);
		exit(1);
	}

	sock = tcp_connect(AF_INET, argv[1], atoi(argv[2]));
	if (sock == -1) {
		printf("tcp_connect fail");
		exit(1);
	}

	while (1) {
		printf("\033[1;33m명령어 : get, put, pwd, ls, cd, quit\n");
		printf("\033[1;32mclient> ");
		fgets(bufmsg, MAXLINE, stdin); //명령어 입력
		fprintf(stderr, "\033[97m");   //글자색을 흰색으로 변경
		if (!strcmp(bufmsg, "get\n")) {//get명령어를 입력받았다면
			printf("다운로드할 파일 : ");
			scanf("%s", filename);       //파일 이름 입력
			fgets(temp, MAXLINE, stdin); //버퍼에 남은 엔터 제거
			strcpy(buf, "get ");
			strcat(buf, filename);
			send(sock, buf, 100, 0);         //명령어 전송
			recv(sock, (void *)&size, sizeof(int), 0);
			if (!size) {//파일이 없다면
				printf("파일이 없습니다\n");
				continue;
			}
			f = malloc(size);
			recv(sock, f, size, 0);
			while (1) {
				filehandle = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0666);
				if (filehandle == -1) //같은 이름이 있다면 이름 끝에 _1 추가
					sprintf(filename + strlen(filename), "_1");
				else break;
			}
			write(filehandle, f, size);
			close(filehandle);
			printf("다운로드 완료\n");//전송이 잘 되었다면
		}
		else if (!strcmp(bufmsg, "put\n")) {//put명령어를 입력받았다면
			printf("업로드할 파일 : ");
			scanf("%s", filename);       //파일 이름 입력
			fgets(temp, MAXLINE, stdin); //버퍼에 남은 엔터 제거
			filehandle = open(filename, O_RDONLY);
			if (filehandle == -1) {//파일이 없다면
				printf("파일이 없습니다.\n");
				continue;
			}
			strcpy(buf, "put ");
			strcat(buf, filename);
			send(sock, buf, 100, 0);
			stat(filename, &obj);
			size = obj.st_size;
			send(sock, &size, sizeof(int), 0);//명령어 전송
			// sendfile(sock, filehandle,, NULL, size);//파일 전송
            off_t sent = size;
			sendfile(filehandle, sock, 0, &sent, NULL, 0);//파일 전송
			recv(sock, &status, sizeof(int), 0);
			if (status)//업로드가 잘 되었다면
				printf("업로드 완료\n");
			else
				printf("업로드 실패\n");
		}
		else if (!strcmp(bufmsg, "pwd\n")) {//pwd명령어를 입력받았다면
			strcpy(buf, "pwd");
			send(sock, buf, 100, 0);
			recv(sock, buf, 100, 0);
			printf("--The path of the Remote Directory--\n%s", buf);
		}
		else if (!strcmp(bufmsg, "ls\n")) {//ls명령어를 입력받았다면
			strcpy(buf, "ls");
			send(sock, buf, 100, 0);
			recv(sock, &size, sizeof(int), 0);
			f = malloc(size);
			recv(sock, f, size, 0);
			filehandle = creat("temp.txt", O_WRONLY);
			write(filehandle, f, size);
			close(filehandle);
			printf("--The Remote Directory List--\n");
			system("cat temp.txt");	//현재 디렉토리의 파일 출력
		}
		else if (!strcmp(bufmsg, "cd\n")) {//cd명령어를 입력받았다면
			strcpy(buf, "cd ");
			printf("이동할 경로 이름 : ");
			scanf("%s", buf + 3);        //위치 입력
			fgets(temp, MAXLINE, stdin); //버퍼에 남은 엔터 제거
			send(sock, buf, 100, 0);     //명령어 전송
			recv(sock, &status, sizeof(int), 0);
			if (status)
				printf("경로 변경 완료\n");
			else
				printf("경로 변경 실패\n");
		}
		else if (!strcmp(bufmsg, "quit\n")) {//quit명령어를 입력받았다면
			strcpy(buf, "quit");
			send(sock, buf, 100, 0);
			recv(sock, &status, 100, 0);
			if (status) {
				printf("서버를 닫는 중..\n");
				exit(0);
			}
			printf("서버 닫기 실패\n");
		}
	}
}
```

### Reference
https://www.easymedia.net/Culture/EasyStory/index.asp?no=172&mode=view&IDX=1170&p=1
https://ko.wikipedia.org/wiki/%ED%8C%8C%EC%9D%BC_%EC%A0%84%EC%86%A1_%ED%94%84%EB%A1%9C%ED%86%A0%EC%BD%9C
https://itwiki.kr/w/FTP_%EB%B0%94%EC%9A%B4%EC%8A%A4_%EA%B3%B5%EA%B2%A9

