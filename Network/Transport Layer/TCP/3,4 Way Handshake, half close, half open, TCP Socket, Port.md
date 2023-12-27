# 3 Way Handshake

TCP는 안정적이고 연결지향적인 4계층용 프로토콜이다.
연결 세션 설정을 하기 위해 3 way handshake를 한다.

![](http://www.ktword.co.kr/img_data/1901_1.JPG)

TCP 패킷의 SYN 플래그, ACK 플래그를 설정하면 어떤 세그먼트인지 식별할 수 있다.

첫 번째 세그먼트인 SYN 세그먼트에서는 클라이언트가 서버에게 연결 요청을 한다.
데이터는 전송하지 않지만 하나의 순서번호를 소비한다. (순서 번호 = 클라이언트 측 ISN)
여기서 순서번호란? TCP연결 설정을 위해 TCP 세그먼트의 첫 번째 바이트에 부여되는 번호로, 난수 발생기를 통해 발생시키고 순서 번호 필드에 넣어서 보낸다. 양방향 설정이 기본이므로 각 방향마다 서로 다른 ISN(Initial Sequence Number) 번호가 사용된다.
확인응답 번호나 윈도우 크기 필드는 정의되지 않는다.

서버에서는 연결 요청을 받으면 연결 허락을 보낸다. 이게 두 번째 세그먼트인 SYN+ACK 세그먼트.
데이터는 전송하지 않지만 하나의 순서 번호를 소비한다. (순서 번호 = 서버 측 ISN)
확인 응답 번호는 수신된 순서번호 + 1 값을 가진다. (다음 ACK 세그먼트에서 이 값을 순서번호로 받아야 한다.)
서버는 LISTEN 상태에서 SYN-RECEIVED 상태로 전이되며, 이를 Half Open이라고 함.

클라이언트에서 서버의 연결 허락을 받으면 연결 설정을 해야 한다. 이게 마지막 세그먼트인 ACK 세그먼트.
수신된 순서번호 + 1을 승인 번호로 보내고, 순서 번호 (확인 응답 번호)를 두번째 세그먼트에서 받은 확인 응답 번호를 복사해서 보낸다.
데이터는 전송하지 않고, 순서 번호도 소비하지 않는다.

SYN Flooding : SYN만 보내놓고 손 떼면 서버는 어리둥절.

# 4 Way Handshake
![](http://www.ktword.co.kr/img_data/2436_1.JPG)

4 way handshake는 정상적인 연결 종료 방법이다.
클라이언트가 FIN 세그먼트를 어플리케이션 종료하면서 날린다.
ACK 세그먼트로 연결 종료 요청에 대해 서버의 응답을 클라이언트로 보낸다.
서버측 Application의 종료를 기다린 다음 서버가 FIN+ACK 세그먼트로 종료 알림을 보내면, 
클라이언트 측이 ACK 를 보내고 끝낸다. 이 때 클라이언트는 최대 세그먼트 수명의 2배를 기다린 다음 closed된다.

# Half Close, Half Open

### Half Close
half close는 연결이 형성된 상태에서 한 쪽이 연결을 끊고 싶을 때 입력, 전송 스트림 중 전송 스트림을 닫는 행위를 말한다.
서버쪽에서 데이터를 모두 보냈고, 연결을 끊고 싶을 때 전송 스트림을 통해 EOF를 보내고 전송 스트림을 닫는다.
클라이언트 쪽에서 데이터를 모두 받고 나서 입력 및 전송 스트림을 닫는다.

왜 필요한가? -> 데이터의 소실을 막기 위해.

### Half Open
위에서 살펴봤듯, SYN-Received 상태를 말한다. 이를 활용해서 포트 스캐닝 공격이 이루어진다.
![](https://velog.velcdn.com/images/younghyun/post/5b505963-b041-49b9-a844-6aeaa93c6e6e/image.png)
![](https://velog.velcdn.com/images/younghyun/post/cec0f8ce-d25d-4794-8732-355e6762fbef/image.png)
포트가 열려있는 것을 확인해도 RST를 보내기 때문에 연결 로그가 남지 않는다.
포트가 열려있지 않으면 RST/ACK가 오기 때문에 역시 연결 로그가 남지 않는다.
하지만 SYN 자체 수신 로그는 남기 때문에 발각 위험이 있다.

# TCP Socket, Port

### Socket

Socket이란? 소프트웨어로 구현시킨 추상적인 포트를 의미함.
놀랍게도! Unix 뿐만 아니라 Windows에서도 운영체제 레벨에서 지원. (시스템 콜)

프로세스 대 프로세스 통신 기능을 범용화시킨 추상적인 포트. (통신 상의 endpoint임.)
기본적으로 네트워킹을 위한 IO(입출력)임.
클라이언트/서버 모델이 기초함.

소켓 주소는 IP Address + Port Number를 의미. (유일해야 함)
데이터 전달이 양방향으로 가능함. (서버도 클라이언트에게 전송 가능!)

TCP 연결의 식별은 소켓으로 함. 2개의 IP주소, 2개의 포트 번호를 이용해서 식별.

C언어 소켓 프로그래밍
![](https://blog.kakaocdn.net/dn/bVSNqV/btryXerTjV9/lV04Fo13UmKP44W4XUb7LK/img.gif)

### Port
포트는 전송계층에서 이루어짐.
port address : 사용자 프로세스 또는 응용 프로세스의 통로를 식별해준다.

프로세스 간 통신을 할 때 포트라는 개념을 사용, TCP, UDP, SCTP 등에 의해 통신을 할 수 있음.

세션을 식별할 때 연결 및 방향 식별 가능 : (발신지 IP 주소, 발신지 포트 번호, 수신지 IP 주소, 수신지 포트 번호)

16 비트 길이를 갖게 되며 이론상 65536개의 연결이 가능함.

전달? UDP 헤더 또는 TCP 헤더 내에 포함되어서 전달. 같은 포트 번호라도 프로토콜이 다르면 다르게 식별됨.

Well Known Port : 0 ~ 1023 (IANA에서 관리 : NAT에서도 본 친구)
	DHCP (출발 67, 목적 68), DNS(53), FTP(control 20, data 1), HTTP(80), HTTPS(443), SMTP(25), SSH(22), Telnet(23) 등등
	http://www.iana.org/assignments/service-names-port-numbers/service-names-port-numbers.xml

Registered Port : 1024 ~ 49151

Dynamic, Private Port : 49152 ~ 65535

임시 포트 번호 : 클라이언트 쪽에서는 포트 번호에 신경쓰지 않음. 호스트 내부에서 유일한 값인지만 판단하면 되고, 1024 ~ 5000번이 주로 할당됨.
