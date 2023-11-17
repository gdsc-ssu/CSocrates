## 계기
현대에서 사용하는 기술은 Packet Switching 전략으로 데이터를 전송한다.
기본적으로 IP 계층은 신뢰성을 보장하지 않는다. (IP 계층 참조)
이 때, 데이터가 손실이 없도록 만들려면 Transport Layer의 도움이 필요하다.

### Stop and Wait
패킷을 보내고 다시 응답이 올때까지 기다리는 방식이다.
각 Sender, Receiver의 [[Window Size]]는 1이다.
Sender가 패킷 1개를 보내면 Receiver가 잘 받았다는 ACK를 보낼 때까지 기다린다.
절대적인 순서가 보장되지만, 처리하는 속도가 너무 느리다는 단점이 있다.

### GBN (Go-Back-N)
Go Back N이란 receiver 측에서 순서대로 받지 못한 패킷이 있다면 해당 패킷에서부터 다시 재전송하는 방식이다.
즉 Sender의 Window의 크기는 (2^n) - 1이고, Receiver의 Window 크기는 무조건 1로 고정이다.
해당 방식을 진행하는 과정은 다음과 같다.
1. Receiver 측은 정상적으로 받지 못한 패킷이 있는 경우, 해당 패킷이 올 때까지 다른 패킷들을 받아도 받지 못한 패킷에 대한 ACK를 보낸다.
	- 예시로 Sender측이 패킷 1,2,3,4,5를 전송했는데, Receiver 측이 1,2,4,5를 받았다면 Receiver 측은 ACK 1, 2, ,2 ,2를 반환한다.
	- 이를 통해 만약 ACK가 중간에 손실 나더라도, 중간에 있는 패킷들이 정상적으로 전송되었다는 것을 알 수 있다. ([[Cumulative ACK]]의 특성)
2. Sender는 전송한 패킷 중, ACK되지 않은 패킷에 대해서 타이머를 계산한다.
	- 해당 타이머가 만료될 때까지 ACK가 오지 않는다면, Window의 ACK가 되지 않은 모든 패킷들을 재전송한다.
#### 예제 1
Sender의 패킷이 없어지는 경우
![[Pasted image 20231118000520.png]]
#### 예제 2
ACK가 사라지는 경우
![[Pasted image 20231118000540.png]]
### SR(Selective Repeat)
Selective Repeat 방식은 receiver 측에서 받은 각각의 패킷들에 대해 ACK을 보내는 방식이다.
기존의 GBN의 경우는 재전송, retransmission이 너무 과도하게 발생하는 문제점이 있었다.
Sender의 Window Size는 
1. Receiver 측은 ACK가 순서대로 오는 것에 대해 상관하지 않고, 받은 패킷에 대해서 ACK를 보낸다.
	- 예시로 패킷 1, 2, 3, 4, 5를 전송했는데 Receiver측에서 1, 2, 4, 5를 받았다면 Receiver 측은 ACK 1, 2, 4, 5를 보낸다.
1. Sender는 ACK를 받지 못한 패킷들에 대해서 타이머를 계산한다.
	- 타이머가 만료될 때까지 ACK가 도착하지 않는다면, 각 패킷을 재전송한다.
#### 예시1
Sender의 패킷이 없어지는 경우
![[Pasted image 20231118000914.png]]

#### Window Size별 오류 발생 가능성
![[Notes_231118_002709_57c.jpg]]![[Notes_231118_002815_b94.jpg]]
Window Size는 2^(m-1) 으로 해야한다. (m은 Packet ID로 사용할 수 있는 숫자의 개수)