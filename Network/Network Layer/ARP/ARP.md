## ARP란?
주소 결정 프로토콜(Address Resolution Protocol, ARP)은 네트워크 상에서 IP 주소를 물리적 네트워크 주소로 대응(bind) 시키기 위해 사용되는 프로토콜이다.
이를 통해 IP 주소와 MAC 주소를 1대1 매칭시켜 LAN에서 목적지를 제대로 찾아갈 수 있도록 돕는다.
IP 주소와 MAC주소를 일대일 대응으로 정리하고, 목적지 IP에 맞는 목적지 주소로 전달하는 ARP Table이 있다.

## ARP Table 생성 과정
![[Pasted image 20231111012342.png]]
1. PC0 (192.168.1.1)은 PC2(192.168.1.3)으로 데이터를 전달하려고 한다. Routing Table에 자신과 PC2가 같은 LAN에 속한것을 확인했다.
2. PC2의 MAC주소를 알기 위해 ARP Request (Who has 192.168.1.3? Tell 192.168.1.1)을 뿌린다.
3. PC0는 Broadcase(FF:FF:FF:FF:FF:FF)인 ARP Request를 날리고 이는 PC1, PC2, P3에 전달된다. 이에 ARP Request의 목표인 PC2가 반응하여 ARP Response(PC2의 MAC주소)를 보낸다.
4. PC0(192.168.1.1)은 PC2가 보낸 ARP Response를 받고 ARP Table에 PC2의 IP와 MAC주소를 적는다. 그리고 데이터의 목적지 IP를 192.168.1.3으로 지정하면 자연스럽게 ARP Table을 보고 PC2의 MAC주소를 목표로 전달한다.

---
## Reference
- https://aws-hyoh.tistory.com/entry/ARP-%EC%89%BD%EA%B2%8C-%EC%9D%B4%ED%95%B4%ED%95%98%EA%B8%B0