### 참고
https://www.oreilly.com/library/view/internet-core-protocols/1565925726/re69.html
http://www.ktword.co.kr/test/view/view.php?m_temp1=1889
https://blog.naver.com/ak0402/221539958656
https://rhyshan.com/278
### 목차
- TCP Header
- TCP Header Option
### TCP Header
TCP는 TCP Segment를 위한 헤더를 다음과 같이 정의하고 있다.

![[Pasted image 20231202091256.png]]
- Source / Destination Port Number
	- 16비트
	- IP Datagram의 IP Address, TCP Segment의 Port Number를 합쳐서 Socket의 주소가 된다.
	- Source, Destination의 포트 번호를 모두 갖고 있으니, 양쪽 호스트들의 end point (종단 프로세스)를 식별할 수 있다.
- Sequence Number
	- 32비트
	- 바이트 단위로 구분되고, 이것을 활용해 패킷에 순서를 부여할 수 있다.
	- TCP에서는 해당 필드를 통해 신뢰성 및 흐름 제어 기능을 제공한다.
		- Sliding Window 참고
	- 초기 값은 랜덤한 값이고, 최대값 (4,294,967,295) 이후에는 '0'으로 다시 시작
	- TCP는 양방향 통신임으로 각 방향별로 다른 Sequence Number를 사용한다.
- Acknowledgement Number
	- 32비트
	- 수신을 기대하는 다음 Sequence Number 번호를 의미한다.
	- 즉 마지막 수신 성공한 Sequence Number + 1 값을 전송한다.
- Header Length
	- 4비트
	- TCP 헤더는 최소 20바이트부터 60바이트 까지 가능하다.
	- 따라서 동적으로 값이 들어갈 수 있기 때문에 설정해줘야한다.
- Flag bits
	![[Pasted image 20231202093516.png]]
	- 6개의 Flag Bit로 이루어져 있다.
		- CWR (Congestion Window Reduced)
			- 혼잡 제어 메커니즘에 응답했다는 의미
		- ECE (ECN Echo)
			- 네트워크 트래픽이 많아지는 경우, 라우터가 송신 프로세스에게 명시적으로(Explicit) 혼잡을 알리려고 사용
			- 비트가 설정된 경우, [ECN(Explicit Congestion Notification)](https://www.ietf.org/proceedings/92/slides/slides-92-iccrg-1.pdf) 가능함
			- 설정되지 않은 경우, IP 헤더에 CE(Congestion Experienced) 플래그가 설정되어서 정상처리 되었음을 의미
		- URG (Urgent)
			- 긴급하다는 패킷을 의미
			- 1로 설정된 경우, 패킷 순서와 상관 없이 먼저 전송된다.
		- ACK (Acknowledgement)
			- ACK Field에 값이 지정되었음을 의미
			- SYN 이후부터는 모든 세그먼트에 붙어서 전송됨
		- PSH (Push)
			- 버퍼링된 데이터를 즉시 상위 계층으로 전송하도록 설정
			- 예시
				- Telnet 세션에서 `q` 누르고 세션 종료 시
				- 서버 측에서 데이터 전송할 게 더 없다는 의미
		- RST (Reset)
			- ESTABLISHED된 회선에 강제 리셋
			- 연결 상에 문제가 있을 때, 해당 문제를 발견한 장비가 RST를 1로 설정하고 전송
			- 예시
				- LISTEN, SYN_RCVD 상태일 때, RST 수신한 경우 `LISTEN` 상태로 돌아감
				- 그 밖의 상태인 경우엔 CLOSED 상태로 돌아감
		- SYN (Synchronize)
			- 연결 설정 초기화를 위한 Flag
		- FIN (Finish)
			- 데이터 전송을 마치기 위한 Flag
- Window Size
	- 16비트
	- Congestion Control을 위해서 사용됨
	- TCP 흐름제어를 위해 송신자에게 자신의 수신 버퍼 여유 용량을 지속적으로 통보
- Checksum
	- 16비트
	- TCP 헤더 체크섬
- Urgent pointer
	- 16비트
	- 긴급한 데이터가 어디까지인지 알려줌 (긴급 데이터의 마지막 바이트)
	- 평소에 URG 플래그를 사용하지 않는 것을 추천

### TCP 옵션
TCP 헤더의 길이는 20바이트에서 60바이트까지 가능하다.
그 이유는 TCP 헤더에 옵션이 들어가는 경우, 크기가 달라지기 때문이다.

**TCP Header Option Field**
![[Pasted image 20231202091619.png]]
- EOL (End of Option)
	- 1바이트
	- 더 이상 처리할 옵션이 없음 (옵션 리스트의 끝)
- NOP (No Operation)
	- 1바이트
	- 4바이트 배수로 패딩 채우기 위해서
- MSS (Maximum Segment Size)
	- 4바이트
	- TCP 최대 세그먼트 크기 옵션
- WSCALE (Window Scale factor / WSOPT)
	- 3바이트
	- 윈도우 스케일 옵션, 즉 윈도우 크기 범위 확장 (16비트 -> 32비트)
	- TCP 헤더 내 윈도우 크기 필드 값을 윈도우 스케일 옵션 값(단위는 비트) 만큼 왼쪽 쉬프트 하여 크기 스케일 변화
- SACK Permitted (Selective Acknowledgement Permitted)
	- 2바이트
	- 선택 확인 응답 옵션 허용
	- 여러 패킷 중 손실된 패킷만 선택적으로 재전송하기 위한 TCP 연결 시 옵션
- SACK (Selective Acknowledgment)
	- 가변 길이
	- 수신측에서 손실되어 재전송을 원하는, 불연속적인(순서 어긋난) 세그먼트 블록을 명시하기 위함
- Timestamp
	- 10바이트
- UTO (User Timeout)
	- 4바이트
	- 사용자 타임아웃을 명시
- [TCP-A0](https://datatracker.ietf.org/doc/html/rfc5925)
	- 가변 길이
	- 인증 옵션

TCP 헤더는 최대 60바이트이다.
```
If all of the bits in this field were “on,” the maximum value would be 15. Thus, a TCP header can be no larger than 60 bytes (15 × 32 bits = 480 bits = 60 bytes).
```
