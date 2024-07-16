## Logical Link Control (논리 링크 제어)
- LAN환경에서의 데이타링크 계층(2계층)의 2개의 부계층 중 하나.
- DLC (Date Link Control) 이라고도 불림.

- IEEE 802.2 프로토콜을 LLC(Logical Link Control)이라고 한다.

- LLC 계층은 두 장비간의 링크를 설정하고, 프레임을 송수신하는 방식과 상위 레이어 프로토콜의 종류를 알리는 역할

- LLC 프레임의 구조
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/LLC%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202023-10-10%20%EC%98%A4%ED%9B%84%208.01.18.png)

DSAP는 Destination Service acees point의 줄인말로 목적지 주소 즉 3계층 세부정보를 나타낸다.
SSAP는 Source service access point로 end point라고도 부르며 출발지 3계층 주소를 나타낸다.

LLC제어는 CTRL로도 부르며 제어는 3계층 이상의 장비와 협상용으로 존재한다.

이후 정보데이터, 즉 3계층 데이터가 오게된다.

-> 3계층의 데이터를 가지고, 해당하는 프로토콜에 따라서 프레임을 구성. 
	구성된 프레임은 MAC계층에서 처리