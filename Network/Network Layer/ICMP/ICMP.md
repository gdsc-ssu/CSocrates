## ICMP란?
ICMP(Internet Control Message Protocol), 인터넷 제어 메시지 프로토콜은 네트워크 장치에서 네트워크 통신 문제를 진단하는데 사용하는 프로토콜이다.
대부분 라우터와 같은 네트워크 장비에서 사용된다.

---
## 왜 사용하는가?
인터넷을 통해 두 개의 장치가 연결될 때마다 ICMP를 사용하여 일부 데이터가 예상대로 도착하지 않은 경우 수신 장치에서 전송 장치로 이동할 수 있는 오류를 생성할 수 있다. 
예를 들어, 지나치게 대규모 데이터 패킷은 라우터가 관리하기에는 너무 큰 경우, 라우터는 데이터 패킷을 폐기하고 ICMP 메시지를 발신자에게 전송하여 문제를 알립니다.

또한 네트워크 성능을 평가하기 위한 진단 도구입니다. `traceroute`와 `ping` 모두 ICMP를 사용해서 만들어져 있다. `traceroute`와 `ping`은 데이터가 정상적으로 전송되었는가를 확인하는 메시지이다. 
***traceroute***
모든 라우터는 패킷을 수신하면 TTL을 1을 감소시키고 전달해야 하는데, 만약 TTL 이 0 이 되면 패킷을 버리고 time exceeded 메시지를 송신측에게 돌려 주게 된다. 이를 통해 네트워크가 어떻게 연결되는지 알 수 있다.
***ping***
해당 IP 를 가진 장비에 접속 가능한지 확인하는 프로그램이며 echo request 를 던지고, 이로 부터 받은 echo reply 를 확인한다.

---
### ICMP 계층의 위치
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/ICMP%20/%20Pasted%20image%2020231111001911.png)
ICMP는 IP 프로토콜의 상위 계층처럼 행동하지만, IP 계층에 포함되며 IP 데이터그램의 데이터 부분에 포함되어 전달된다.

---
### ICMP 메시지 포맷
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/ICMP%20/%20Pasted%20image%2020231111001958.png)

---
### ICMP == 핑 ?
ICMP와 핑은 서로 관련이 있지만 전혀 다르다. 
ICMP는 장치 간 메시지가 전송되는 방법을 제어하는 프로토콜이고, ICMP 프로토콜이 보내는 에코 요청 및 에코 응답을 일반적으로 핑이라고 한다. 
따라서 핑은 ICMP를 사용하여 생성되는 반면 ICMP는 핑으로 생성되지 않는다.

---
## Reference
- https://www.cloudflare.com/ko-kr/learning/ddos/glossary/internet-control-message-protocol-icmp/
- https://www.fortinet.com/kr/resources/cyberglossary/internet-control-message-protocol-icmp