## VLAN이 필요한 이유
1. LAN에서 [[ARP]]를 활용해 IP Address와 매칭하는 MAC Address를 알아낼 수 있다.
   [[ARP]] Request는 연결된 네트워크 장비와 커퓨터에 모두 전달되는 브로드캐스트(Broadcast)를 진행한다.
   그렇다면 네트워크 장비에 10대의 컴퓨터가 연결되어 있다고 가정했을 때, 각각의 컴퓨터가 다른 컴퓨터의 MAC Address를 알기 위해서는 최소 10번의 ARP Request가 발생할 것이다.
   여기서 연결된 장비가 더 많아진다면 ARP를 위한 Broadcast가 점점 늘어날 것이고, 브로드캐스트를 처리하느라 정상적인 수행이 불가능할 것이다.
2. Subnet Mask가 다른 여러 개의 IP 대역을 사용해야한다면 어떻게 해야할까?
   공유기를 여러개 설치해야할까? 그렇다면 새로운 IP 대역이 추가되면 추가적으로 작업해야할까?
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/VLAN%20/%20Pasted%20image%2020231111010902.png)

---
## VLAN이란?
컴퓨터 네트워크에서 여러 개의 구별되는 브로드캐스트 도메인을 만들기 위해 단일 2계층 네트워크를 분할할 수 있는데, 이렇게 분리하면 패킷은 하나 이상의 라우터들 사이에서만 이동할 수 있도록 하고, 이를 가상 랜(Virtual LAN)이라 한다.

VLAN을 통해 브로드캐스트 도메인을 분리할 수 있습니다.
분리된 각 VLAN끼리는 통신하기 위해선 L3 이상의 스위치 혹은 라우터를 통해서만 가능하다.
또한 VLAN ID를 1~4096까지의 번호를 사용해서 구분할 수 있다.

![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/VLAN%20/%20Pasted%20image%2020231111005216.png)
결과적으로 VLAN을 사용하면 해당하는 VLAN 내의 호스트들에게만 브로드캐스트를 진행할 수 있다.
예시로 사진에서 VLAN10과 VLAN20으로 나뉘어 있는 것을 볼 수 있다.
PC2와 PC3는 서로 같은 VLAN으로 연결되어 직접 통신이 가능하다. 하지만 서로 다른 VLAN에 존재하는 
PC1와 PC2, PC3는 연결될 수 없다.
결과적으로 VLAN으로 나뉘어 있다는 것은 브로드캐스트가 발생했을 때, 전달하는 곳이 해당 VLAN 내부만 해당된다는 이야기이다.
## Reference
- https://aws-hyoh.tistory.com/75