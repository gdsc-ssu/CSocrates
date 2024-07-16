### 출처
* https://www.quora.com/What-is-the-reason-behind-Youtube-using-TCP-and-not-UDP  (왜 유튜브는 tcp를 쓸까?)
* https://stackoverflow.com/questions/21266008/can-i-use-broadcast-or-multicast-for-tcp (브로드캐스트는 왜 udp만?)
* https://www.cloudflare.com/ko-kr/learning/ddos/glossary/user-datagram-protocol-udp/ (udp의 기초)
* https://www.cloudflare.com/ko-kr/learning/ddos/udp-flood-ddos-attack/ (udp 폭주)
____
### 개요
* [[#UDP란]]
* [[#유튜브는 UDP를 쓸까?]]
* [[#UDP와 DDOS]]
* [[#UDP 브로드캐스트]]
* [[#간단한 UDP 에코 서버]]
___
### UDP란
UDP는 사용자 데이터그램 프로토콜의 줄임말로써 전송 계층에서 사용하는 프로토콜이다. UDP는 TCP와 대척점에 놓인 프로토콜로 TCP와 달리 패킷의 전달을 보장하지 않는다. 이로 인해 ==**UDP는 빠른 전송을 실시할 수 있지만, 패킷의 손실이 발생할 수 있다.**==

따라서 <b><u>UDP는 패킷 손실이 발생하더라도 속도가 더 중요한 서비스 혹은 손실된 패킷을 곧장 복구 할 수 있는 서비스에서 활용한다. </u></b> 전자의 예시로는 실시간 스트리밍 서비스나, 온라인 게임 등이 있는데 이 경우 과거의 패킷의 정보를 현재의 패킷이 어차피 덮어 사용하기 때문에 과거의 패킷에 손실이 발생하더라도 집착할 필요는 없다. 후자의 예시로는 DNS가 있다.

DNS는 도메인에 따른 ip 주소만을 넘겨주면 모든 작업을 마친다. 따라서  만약 손실이 발생하더라도 ip만 다시 전송하면 되기 때문에 손실에 대한 오버헤드가 무척이나 작은 편이다. 이에 따라 굳이 핸드 쉐이크를 통한 오버헤드를 감내하지 않고 UDP로 통신하고 만약 유실될 경우 재전송을 요청한다.

> [!info]
> UDP는 빠르지만 신뢰성을 갖지는 않는다. TCP가 캐치볼이면 UDP는 기관총 난사다.

![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/UDP%20%ED%86%BA%EC%95%84%EB%B3%B4%EA%B8%B0%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202023-12-01%20%EC%98%A4%ED%9B%84%2010.04.17.png)

___
### 유튜브는 UDP를 쓸까?
**유튜브는 TCP를 쓴다. 위에서 스트리밍 서비스에 UDP를 사용한다고 했지만, 대표적인 스트리밍 서비스인 유튜브는 TCP를 사용한다.** 이는 크게 보안 이슈와 녹화 파일이라는 특성 떄문이다.

보안 이슈부터 살펴보면 UDP는 DDOS등에 취약한 방법인데 이는 전송 여부를 서로 확인하는 시간 없이 무지성 송,수신이 가능하기 때문이다. 이러한 문제로 인해 UDP의 사용을 자제하는 경향이 있다.

또한 유튜브의 메인 서비스는 실시간 스트리밍이 아닌 녹화 파일 스트리밍이다. 유튜브는 녹화 파일이기 때문에 파일이기 때문에 파일의 패킷이 손실된다면 패킷이 깨지는 등의 문제가 발생할 수 있다.  

* **그럼 유튜브는 느린가?**
유튜브는  UDP를 활용해 전송 속도를 늘리기보다. TCP를 통해 네트워크 상태에 대한 피드백을 받고 네트워크 상황에 따른 전송 데이터의 양을 조절하는  DASH 방식을 채택했다.
___
### UDP와 DDOS
앞서 보안 이슈로 인해  UDP를 사용하지 않는 것일 수도 있다 했는데 실제로 UDP를 활용하면 DDOS 공격을 진행할 수 있다. 이는 **응답을 확인하지 않는다는 UDP의 맹점을 활용한 방식인데 UDP 패킷을 기관총 처럼 난사해 서버를 다운 시키는 방법**이다. 이 경우 서버의 포트가 전부 차거나 리소스 과부하로 서버가 다운될 수 있다. 실제로 DNS를 이런 식으로 공격해 다운 시키는 경우가 종종 있었다.
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/UDP%20%ED%86%BA%EC%95%84%EB%B3%B4%EA%B8%B0%20/%20Pasted%20image%2020231201223133.png)
___
### UDP 브로드캐스트
브로드캐스팅을 하기 위해선 UDP를 사용해야만 한다.  TCP로는 브로드 캐스팅을 할 수 없다. 추가적으로 복수 개의 대상에 동시에 전송하는 멀티 캐스트 역시 UDP로만 가능하다.

* **잠깐 브로드 캐스팅, 멀티 캐스팅이 뭔가요?**
**브로드캐스팅은 소속된 LAN 전체에 패킷을 전송하는 행위**를 말한다. 이때 패킷의 응답을 기대하지 않는다. 브로드캐스팅은 주로 ip, MAC등의 주소 파악을 위해 활용한다. [[ARP]]

**멀티 캐스팅은 브로드 캐스팅과 달리 전체가 아닌 특정 집단을 대상으로만 전송하는 행위**를 말한다. 멀티 캐스트와 브로드캐스트는 모두 1번에 여러 대상에게 전송을 하기 때문에 송신자와 네트워크의 부담을 덜어준다는 간점이 있다.

수신자가 복수 개 존재하는 경우 TCP를 사용할 수 없는 이유는 단순하다.  TCP의 경우 핸드 쉐이크를 통해 연결을 수립하고 해당 연결을 통해서만 데이터를 전송하는 형태이기 때문이다. 따라서  <u><b>각 커넥션 별로 패킷을 전송해야하지 한번에 복수 대상에 패킷을 전송하는 것은 불가능</b></u>하다.
___
### 간단한 UDP 에코 서버

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char *argv[])
{
    int serv_sock;
    char message[BUF_SIZE];
    int str_len;
    socklen_t clnt_adr_sz;

    struct sockaddr_in serv_adr, clnt_adr;

    if (argc != 2)
    {
        printf("Usage:%s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (serv_sock == -1)
        error_handling("UDP socket creation error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");

    while (1)
    {
        memset(message, 0, BUF_SIZE);
        clnt_adr_sz = sizeof(clnt_adr);
        str_len = recvfrom(serv_sock, message, BUF_SIZE, 0, (struct sockaddr *)&clnt_adr, &clnt_adr_sz);
        printf("server received: %s\n", message);
        sendto(serv_sock, message, str_len, 0, (struct sockaddr *)&clnt_adr, clnt_adr_sz);
    }
    close(serv_sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
```
위는 UDP로 작성한 간단한 에코 서버 코드의 예시이다. TCP 서버와 달리 listen과 accpet 작업을 할 필요 없다. 