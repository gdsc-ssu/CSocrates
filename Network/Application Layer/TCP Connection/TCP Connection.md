# 참고용 링크
- https://www.youtube.com/watch?v=U905BeDQ_BA&ab_channel=kakaotech

# 목차

## TCP 커넥션
지구상의 HTTP 통신은 Packet Switch 프로토콜과 TCP/IP를 통해서 이루어진다.
또한 커넥션이 이루어지면, 클라이언트와 서버 컴퓨터 간에 주고 받는 메시지들은 손상, 손실, 순서가 바뀌지 않고 안전하게 전달된다.

TCP는 포트번호를 통해서 여러 개의 커넥션을 유지하는데, TCP 커넥션은 4가지 값으로 이루어져있다.
- 발신지 IP 주소
- 발신지 포트 번호
- 수신지 IP 주소
- 수신지 포트 번호
이 것들은 모두 유일한 값임으로, 각 TCP 커넥션은 위 4가지 값이 같을 수 없다.

# TCP 성능
### HTTP 트랜잭션 지연
![](https://velog.velcdn.com/images/broccolism/post/33448e94-de31-48ca-a2ca-63667e7f0238/image.png)
위 사진을 보면 실제로 서버가 요청을 처리하는 시간은 다른 시간에 비해서는 굉장히 짧은 것을 알 수 있다. (TCP 연결, 요청, 응답이 오가는 시간에 비해서)
HTTP 트랜잭션을 지연시키는 원인을 시간 순서대로 보면 다음과 같다.
1. 클라이언트는 URI에서 DNS를 통해 웹 서버의 IP주소와 포트 번호를 알아야 한다.
2. 클라이언트가 TCP 요청을 보내고, 허용할 때까지 기다린다.
3. 클라이언트가 HTTP 요청을 새로 생성된 TCP 파이프를 통해 전송하고, 서버는 요청을 읽고 처리한다.
4. 웹서버가 HTTP 응답을 보낸다.
실제로는 요청을 처리하는데는 아주 짧은 시간이 드는데 말이다!

---
## 성능 관련 중요 요소
시간대별로 확인했다면 실제로 지연시키는 원인들은
- TCP 커넥션 핸드쉐이크
- 인터넷 혼잡 제어를 위한 TCP의 slow-start
- 데이터를 한데 모아서 한 번에 전송하기 위한 네이글(nagle) 알고리즘
- TCP의 piggyback과 acknowledgement를 위한 확인응답 지연 알고리즘
- TIME_WAIT 지연과 포트 고갈
로 볼 수 있다.

#### TCP 커넥션 핸드쉐이크
이전 스터디에서 확인 했듯이, TCP 요청을 보내려면 TCP Handshake가 필요하다.
![TCP 핸드쉐이크](https://miro.medium.com/v2/resize:fit:1282/1*kzf6hPRQop5SOy3Zr7FXSg.png)

만약 데이터의 크기가 작은 HTTP 트랜잭션은 50% 이상의 시간을 TCP 구성을 위해서 작동할 수도 있다.


#### 확인 응답 지연
인터넷, 즉 IP 자체가 패킷 전송을 보장하지 않기 때문에 TCP는 안정적인, 그리고 순서가 보장된 데이터를 주고 받기 위해서 추가적인 확인 구조를 갖는다.

각 TCP Segment는 Sequence 번호와 Checksum을 갖는다.
만약 수신자가 정상적으로 데이터를 수신했다면, 확인 응답 패킷을 송신자에게 다시 발송하는데 송신자가 만약 특정 시간 내에 확인 응답 패킷을 받지 못하면 패킷이 손실된 것으로 판단하고 패킷을 재전송한다.

하지만 모든 데이터에 대해서 즉시 응답 값만 추가한다면, 아무 많은 비효율적인 데이터 전송이 일어날 것이다.
그래서 네트워크를 효율적으로 사용하기 위해 **Piggyback**이라는 방법이 등장하였다.
TCP에서는 같은 방향으로 전송되는 데이터를 한 번에 묶어서 전송+ACK를 한번에 처리하는 것이다.
만약 같이 보낼 패킷이 없다면, 0.1~0.2정도를 버퍼에 저장해두고 같이 보낼 수 있는 패킷을 찾은 후에 같이 보낼 수 있는 패킷이 없다면 별도의 패킷을 만들어 전송, 아니라면 같이 묶어서 보낸다.

하지만 HTTP 프로토콜은 요청/응답으로 이루어져있음으로, ACK가 송출 패킷에 같이 묶어서 보내질 가능성이 줄어든다. 따라서 이것에 대한 확인 응답이 조금씩 느려지게 된다.

#### TCP Slowstart
TCP에서 데이터를 마구마구 보내다보면, 네트워크 전체에 부하가 걸릴 확률이 높아진다.

따라서 TCP가 한 번에 전송할 수 있는 패킷의 수를 조절하게 변경되었고, TCP 전송이 성공할 때마다 보낼 수 있는 패킷의 양이 2배가 된다.
하지만 처음에는 패킷의 수가 1개부터 시작하게 됨으로 새로운 TCP 커넥션은 이미 지속하고 있던 다른 커넥션에 비해서 느린 속도를 가진다.
#### 네이글 알고리즘
https://en.wikipedia.org/wiki/Nagle's_algorithm
TCP 세그먼트의 Header는 40바이트 정도의 크기를 가지고 있는데, 만약 TCP가 작은 크기의 데이터를 지속적으로 전송하면 overhead가 커지게 되고, 전체 네트워크의 성능이 떨어지게 된다.
따라서 패킷을 전송하기 전에 많은 양의 TCP 데이터를 한 덩어리로 합쳐서 데이터를 전송한다.
정확히 얘기하자면 세그먼트가 최대 크기(약 1,500바이트)가 되지 않으면 전송하지 않고 있는다. (모든 ACK를 수신한 경우를 제외하고)

만약 충분한 양의 패킷이 쌓인 경우, 버퍼에 저장된 데이터가 전송된다.
이를 네이글 알고리즘이라고 한다.
HTTP에서 TCP_NODELAY 파라미터 값을 설정하여 비활성화 할 수도 있지만, 이 경우 작은 크기의 패킷이 생기지 않도록 주의해야한다.
[# TCP_NODELAY 활성화](https://access.redhat.com/documentation/ko-kr/red_hat_enterprise_linux_for_real_time/8/html/optimizing_rhel_8_for_real_time_for_low_latency_operation/proc_enabling-tcp_nodelay_assembly_improving-network-latency-using-tcp_nodelay)

>`pseudocode`
>**if** there is new data to send **then**
    **if** the window size ≥ MSS **and** available data is ≥ MSS **then**
        send complete MSS segment now
    **else**
        **if** there is unconfirmed data still in the pipe **then**
            enqueue data in the buffer until an acknowledge is received
        **else**
            send data immediately
        **end if**
    **end if**
**end if**

이 경우 크기가 작은 HTTP 요청은 패킷을 채우지 못하기 때문에 다른 데이터를 계속 기다리고 있어야한다.
또한 위의 확인 응답 지연이랑 같이 이뤄지면 점점 느려질 수도 있다.
#### TIME_WAIT와 포트 고갈
TCP 커넥션을 종료한 경우에 커넥션의 IP주소와 포트번호를 기록해 놓고, 이를 통해 같은 주소로 포트 번호를 사용하는 TCP 커넥션이 일정 시간 동안 생성되지 않도록 한다.
이를 통해 이전 커넥션과 관련된 패킷이 같은 주소, 포트 번호를 가지는 새로운 커넥션에 삽입되는 문제를 막는다.

만약 테스팅 환경에서는 같은 호스트에서 수많은 커넥션을 시도하는 과정을 예시로 들어보자.
이 경우 발신자의 포트 번호 수는 정해져 있음으로 (약 6만개), 각 포트는 2MSL(약 120초) 동안 사용하지 못함으로, 초당 500개 이상의 트랜잭션을 처리한 경우 포트가 고갈되서 접근할 수 없게된다.

만약 처리가 안되더라도, 대기 상태로 많은 포트가 열려 있는 경우도 주의해야한다.

---
## TCP 커넥션 향상
#### 병렬 커넥션
클라이언트는 동시에 HTTP 커넥션 여러개를 맺을 수 있다. 즉, 앞서 보낸 HTTP 트랜잭션의 응답을 받기 전에 새로운 요청을 보낼 수 있으며 서로 다른 호스트에게 보낼 수도 있다. 병렬 커넥션이 항상 단일 커넥션보다 빠르지는 않다. 네트워크 대역폭이 좁을 때는 여러개의 커넥션을 생성하면서 생기는 부하 때문에 순차적으로 데이터를 받는 것보다 오래 걸릴 수도 있다. 메모리도 많이 소모하게 된다.

브라우저는 실제로 병렬 커넥션을 사용하지만 적은 수의 병렬 커넥션만을 허용한다. 원문에는 “대부분 4개”라고 되어있으나 옮긴이는 “현재 최신 브라우저들은 대부분 6~8개의 병렬 커넥션을 지원한다.”고 한다.
#### 지속 커넥션
사이트 지역성(site locality)을 활용하기 위해 한번 맺어진 TCP 커넥션을 유지하여 트랜잭션 여러 개를 만들 수 있다. 
클라이언트나 서버가 커넥션을 끊기 전까지는 계속 유지된다.

지속 커넥션과 병렬 커넥션을 활용하면 시너지 효과가 난다. 적은 수의 병렬 커넥션을 맺고 이걸 계속 유지하는 것이다. 
요청 header에 `Connection: Keep-Alive`가 추가되어 있다면, 이 커넥션을 통해서 다시 데이터를 주고 받는 것이다.
또한 `Keep-Alive`헤더에 추가적인 옵션 (max, timeout)을 통해서 조절할 수 있다.

예시로 다음 추가 5개의 추가 트랜잭션이 처리될 때까지 커넥션을 유지하거나, 2분 동안 유지하라는 의미이다.
```
Connection: Keep-Alive
Keep-Alive: max=5, timeout=120
```

지속 커넥션을 인식하지 못하는 이전 버전의 프락시 서버를 ‘dumb proxy’ 라고 부른다. 클라이언트 입장에서는 계속 유지되고 있는 커넥션으로 요청을 보내지만 프락시 서버는 그 요청을 무시해버리기 때문에, 브라우저는 자신이나 서버가 타임아웃이 나서 커넥션이 끊길 때까지 기다리게 된다. 즉, 프락시 서버에서 keep-alive 을 명확히 구현하는 것이 중요하다.

#### 파이프라이닝 커넥션
HTTP/1.1 은 지속 커넥션을 통해 요청을 파이프라이닝, 그러니까 병렬 처리 할 수 있다. 
덕분에 keep-alive 커넥션의 성능이 더 높아질 수 있다. 하나의 트랜잭션이 끝날 때까지 기다릴 필요 없이 곧바로 다음 트랜잭션을 시작할 수 있기 때문이다. 
병렬 커넥션과의 차이점은 지속 커넥션이기 때문에 매 트랜잭션마다 HTTP 커넥션 open, close 단계가 없다는 것이다.
![파이프라이닝](data:image/jpeg;base64,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)
이렇게 말하면 파이프라이닝 커넥션을 사용하는게 만능 해결책 같아보이지만 몇가지 고려사항이 있다.

- 커넥션이 지속 커넥션인지 먼저 확인하고 파이프라이닝을 시도해야한다.
- 클라이언트는 커넥션이 끊어지는 상황을 대비해야 한다. 완료되지 않은 요청이 있는데 커넥션이 끊겼다면 다시 커넥션을 맺고 남은 요청을 보낼 수 있어야 한다.
- 파이프라인을 통해 보낸 요청 중 일부만 실패했을 때 클라이언트는 어떤 요청이 실패했는지 알 수 없다. 재시도를 위해 멱등성이 없는 POST 요청을 재차 보내면 문제가 생길 수 있기 때문에 이런 요청을 보내지 말아야 한다.

---

## HTTP 커넥션 끊기
![](https://velog.velcdn.com/images/broccolism/post/da449293-db66-44f7-a6fc-28cac2ee09b5/image.png)
#### HalfClose / HalfOpen
첫번째 그림은 서버가 입출력을 모두 끊은 상태, 즉 TCP 커넥션 전체를 끊은 것이다. 
일반적인 HTTP 애플리케이션은 서버 전체 끊기만 사용할 수 있다. 
만약 클라이언트가 이미 연결이 끊긴 서버의 입력 채널로 데이터를 보낸다면 서버는 TCP `connection reset by peer` 메세지를 클라이언트한테 보낸다. 
해당 메세지를 수신하면 ‘음 서버가 이미 연결을 끊었는데 클라이언트는 그걸 모르고 요청을 보내버렸군’ 이라고 이해하면 된다.

주의할 점은 이 메세지를 받았다면 클라이언트 애플리케이션은 응답 데이터를 절대 읽을 수 없다는 것이다. 
또한 이런 경우가 발생할 수 있다: 
	요청 10개를 파이프라인 지속 커넥션을 통해 전송했고, 응답이 OS의 버퍼에 있지만 애플리케이션은 아직 이를 읽지 않은 상태에서 요청 1개를 더 보낸 뒤 `connection reset by peer` 메세지를 받은 경우. 
	애플리케이션은 OS의 버퍼에 있는 응답 10개마저 읽을 수 없다. 
	대부분의 OS 에서는 저 메세지를 심각한 에러로 취급해서 버퍼에 있는 데이터를 모두 삭제해버리기 때문이다.

대부분 HTTP 연결 종료는 어플리케이션이 자신의 출력 채널을 먼저 끊고, 다른 쪽 기기의 출력 채널이 끊기는 것을 기다리는 방식이다. 이러한 경우 서로 데이터 전송하지 않을 것이라는 것을 알려주면 커넥션은 안전하게 종료된다.
하지만 상대방(서버)가 이것을 구현했는지, 절반 끊기를 했는지 보장하지 않기 때문에 입력 채널에 대해서 주기적으로 검사해야하고, 타임아웃 시간을 설정해 특정 시간이 지나면 강제로 연결을 끊도록 할 수도 있다.