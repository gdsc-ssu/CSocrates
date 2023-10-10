## Multi Access Control 
or
## Medium Access Control
- LAN환경에서의 데이타링크 계층(2계층)의 2개의 부계층 중 하나.

#### MAC 주소
- mac 계층에서 사용하는 주소, 기기의 고유한 주소를 나타낸다
- 8비트의 숫자 6개, 총 48비트의 숫자로 구성되어있다
- NIC(Network Interface Card)에 물리적으로 저장되어 있다.
- MAC주소는 변하지 않는 주소다.
- ex) 1a-3e-44-5c-9a-d1

### Multi Access Control
- 2계층의 경우 Boradcast 방식의 통신을 사용한다.
	-> 즉 모든 노드가 같은 회선을 공유하므로 collision을 방지하기 위해 MAC이 사용된다.

mac을 만드는 세가지 방법
#### 1. channel partitioning
- 전체 크기의 채널을 작은 부분으로 나눔 (시간, 공간 등)
##### TDMA
- Time Division Multiple access : 각 노드의 차례가 지정되어 있고, 자기 순서에 맞춰서 실행
![[스크린샷 2023-10-10 오후 5.21.34.png]]

##### FDMA
- Frequency Division Multiple Access : 각 노드의 전용 채널을 만듬
	(노드의 개수 m, 전체 채널의 크기 R, 각 노드당 전용 채널의 크기 R/m)
![[스크린샷 2023-10-10 오후 5.22.37.png]]

#### 2. random access
- 각 노드가 사용하고 싶을 때 사용.
- Channel partitioning 보다 좋다
	- 네트워크 환경은 보통 일정하지 않으므로, 전용 차례나 채널이 있을 경우에 사용하지 않는시간이 더 길어 효율이 좋지 않다.
##### [[CSMA]] (현재 표준)
- Carrier Sense Multiple Access
- 데이터를 보내기 전, 전달매체가 사용되고 있는지 확인 후 미사용 시 데이터 전송

#### 3. taking turns
- Partitioning과 Random의 장점을 모두 융합한 방식
- 하지만 분산화를 하지 못하기 때문에 실제로는 사용하지 않는다.

##### Polling
- 하나의 마스터 노드를 두고, 그 마스터 노드가 차례를 체어하는 방식
![[스크린샷 2023-10-10 오후 5.37.39.png]]
###### Token passing
- "토큰"이라는 특별한 메세지를 사용한다
- 이 토큰을 가지고 있는 노드만 메세지를 전송할 수 있는 방식
- 토큰 자체를 잃어버리면 모든 네트워크가 멈춰버리기 때문에 사용하지 않는다.

![[스크린샷 2023-10-10 오후 5.37.54.png]]- 