#tcp 
### 출처
* https://d2.naver.com/helloworld/47667 (전체 자료 출처)
* https://unix.stackexchange.com/questions/418275/which-process-is-responsible-for-tcp-in-linux (TCP는 커널에서 처리)
___
### 개요
* [[#TCP는 어디서 처리할까?]]
* [[#TCP Send in OS]]
* [[#TCP Receive in OS]]
* [[#정리]]
___
### TCP는 어디서 처리할까?
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/TCP%EB%8A%94%20%EC%BB%A4%EB%84%90%EC%97%90%EC%84%9C%20%EC%B2%98%EB%A6%AC%ED%95%9C%EB%8B%A4%20/%20Pasted%20image%2020231117224311.png)
<span class="red-bg"><b>tcp는 커널에서 처리하며 커널 내부에 위치한 코드로 구현된다.</b></span> 따라서 데이터가 소켓을 거치는 순간 해당 데이터는 커널의 주관이 되며 운영체제가 자체적으로 처리하게 된다.
>[!info]
>TCP는 커널에서 처리한다.

___
### TCP Send in OS
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/TCP%EB%8A%94%20%EC%BB%A4%EB%84%90%EC%97%90%EC%84%9C%20%EC%B2%98%EB%A6%AC%ED%95%9C%EB%8B%A4%20/%20Pasted%20image%2020231117224554.png)
유저 영역에 위치한 **애플리케이션은 write 시스템 콜을 호출해 데이터를 아래 계층으로 내보낸다.** 시스템 콜을 통해 영역은 유저 영역에서 커널 영역으로 전환된다.

소켓은 송신과 수신을 위한 두개의 버퍼를 가지고 있다. 이때 **write 시스템 콜을 애플리케이션이 호출하면, 송신용 send_buffer에 유저 영역의 데이터가 복사된다. 이 다음 tcp를 커널로 부터 호출해 버퍼에 복사한 데이터를 처리한다.**

커널에 위치한 TCP는 데이터 전송을 위한 TCP segment를 생성하고 TCP 통신에 필요한 정보들을 기록한다. 생성된 세그먼트는 이후 IP 레이어로 이동한다. 세그먼트에는 IP 헤더가 추가되고 라우팅(다음 전송지를 찾는 행위)을 진행한다. 이후 데이터는 이더넷 레이어로 전달된다.

이후 NIC는 패킷 전송을 요청받고 메인 메모리에 있는 패킷을 드라이버를 통해 자신의 메모리로 복사한다. NIC는 네트워크 선을 통해 해당 메모리를 라우팅을 통해 얻은 목적지로 전송한다.

**User → System_call → Socket → Kernel → TCP → IP → Ethernet → NIC**
____
### TCP Receive in OS
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/TCP%EB%8A%94%20%EC%BB%A4%EB%84%90%EC%97%90%EC%84%9C%20%EC%B2%98%EB%A6%AC%ED%95%9C%EB%8B%A4%20/%20Pasted%20image%2020231117224804.png)

IP레이어도 마찬가지로 패킷을 검증하고 헤더를 제거한 후 TCP 레이어로 전달한다. TCP 레이어로 전달되면 패킷이 속하는 연결을 찾는다. 즉 데이터를 수신해야하는 대상을 탐색하는 작업을 수행한다. 이때 **대상을 찾는 식별자는 *<소스 IP, 소스 port, 타깃 IP, 타깃 port>*가 되며 이는 소켓의 식별자와 동일**하다.

**연결을 찾으면 새로 전달받은 패킷 데이터를 receive socket buffer에 추가한다. 이후 애플리케이션 영역에서 read 시스템 콜을 통해 해당 버퍼의 데이터를 읽고 어플리케이션 메모리로 복사해 가고 버퍼는 비워지게 된다.**
___
### 정리
정리하자면 **TCP는 커널에 의해 실행되고 구현**된다. 응용 프로그램은 TCP에 직접적으로 관여할 수 없고 이는 운영체제 영역에서 다뤄지는 일이다. **응용 프로그램에서 TCP를 활용한다면 이는 TCP를 직접적으로 다루는 것이 아닌 시스템 콜을 통해 커널 영역에 있는 TCP와 소통**하는 것이다. 소켓이 가장 대표적인 인터페이스로 소켓을 read하거나 write할 때마다 시스템 콜을 통해 커널 영역에서 동작하는 TCP에 데이터를 송,수신 할 수 있다.