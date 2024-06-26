### 목차
- UDP Header
# UDP Header 구조
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/UDP%20Header%20/%20Pasted%20image%2020231202104613.png)
- Source / Destination Port Number
	- 16비트
	- 발신지, 목적지 포트 번호
- Packet Length
	- 최소 8, 최대 2^16 - 1 = 65,535
	- UDP 헤더 8바이트를 포함한 패킷 전체 길이를 바이트 단위로 표시함
	- 데이터의 크기는 데이터를 처리하는 장비들에 의해서 결정된다.
	- 최대 크기는 IP 계층의 헤더 20바이트, 전송 계층의 8바이트를 뺀 65,507바이트이다.
- Checksum
	- 선택
	- 체크섬이 0이면 체크섬 계산도 하지 않음