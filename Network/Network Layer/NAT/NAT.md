Network Address Translation
네트워크 주소 변환

# NAT란?

인터넷 상에 제한된 공인 IP를 재사용할 수 있도록 사설 IP 주소 공간을 별도로 정한 후 주소 변환을 하는 방식.

# 사용 이유

IPv4 상에서 사용할 수 있는 IP 개수는 제한적임. 
![ㅁㄴ](http://www.ktword.co.kr/img_data/4864_1.JPG)

우리 나라에서 사용하는 공인 IP 주소들은 KISA (한국 인터넷 진흥원) 산하에 있는 한국 인터넷 정보 센터 (KRNIC) 에서 모두 할당함.

계층적으로 할당되는데,
IANA -> APNIC -> KISA(KRNIC) -> ISP (KT 등 인터넷 서비스 제공 업체) -> 개별 사용자 
이렇게 할당 된다.

ISP는 일반적으로 개별 사용자 (각 가정이나 기업)에 공인 IP 대역을 할당한다.

각 가정이나 기업의 라우터는 인터넷에 연결하려고 할 때 이 대역 중 하나의 IP를 받고, 이 IP는 다른 어떤 네트워크와도 중복이 되지 않는다. (그렇게 ISP가 할당해준다. 또한 DHCP를 이용해서 IP를 동적으로 할당하기도 한다.)

해당 라우터는 NAT기능을 거의 무조건 사용한다. (iptime 같은 라우터는 추가로 스위칭, 무선 네트워크 관리, NAT, 방화벽, DHCP 등도 같이 제공한다)

NAT 기능을 통해 공인 ip와 사설 ip간 주소 변환이 가능하고, 각각의 디바이스는 사설 ip로 할당이 된다.


즉, NAT는 IPv4의 주소 부족 문제를 어느정도 해결하는 솔루션인 것이다.

# NAT의 종류

NAT는 input이 1개이고, output이 1개인 변환 함수라고 생각할 수 있다.
하나의 공인 IP 주소를 여러 개의 사설 IP 주소로 변환하거나,
반대로 여러 개의 사설 IP 주소를 하나의 공인 IP 주소로 변환한다.

변환 방식에 따라 2가지로 분류할 수 있다.

### Static NAT
하나의 사설 IP 주소를 하나의 공인 IP 주소에 정적으로 매핑함. 서버에서 주로 이 방법을 사용.

### Dynamic NAT
여러 개의 사설 IP 주소를 풀(pool)로 관리하고, 이 풀에서 동적으로 매핑하여 외부 통신에 사용. 여러 디바이스가 공인 IP 주소를 공유함.

### NAPT (Network Address Port Translation) or PAT (Port Address Translation)
IP 주소 뿐만 아니라 포트 번호 등도 같이 포함시켜서 내부 호스트를 구분하는 방식. (TCP, UDP에서는 포트 번호를, ICMP에서는 질의식별자를 통해 구별함.)


# 실제 공유기 까보기

### NAT Hairpinning

![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/NAT%20/%20NAT_1_Hairpinning.png)

다른 말로, NAT Loopback.
로컬 네트워크의 내부 디바이스가 해당 네트워크의 공인 IP 주소를 통해 자신의 서비스에 접근할 수 있도록 하는 기능.

두 가지 상황에서 적용된다.
1. 내부 네트워크에서 호스트(서버 등)가 공인 IP 주소를 사용해서 외부 네트워크에 서비스를 제공하는 경우
2. 내부 네트워크에서 호스트가 해당 네트워크의 공인 IP 주소를 통해 내부 서비스에 접근하려는 경우

내부 디바이스가 내부 서비스에 접근하는 거나, 외부 디바이스가 내부 서비스에 접근하는 거나 동일하게 서비스하고 싶으면 이 기능을 활성화 하면 된다.


## Port Forwarding

![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/NAT%20/%20NAT_2_Port_Forward.png)

네트워크에서 사용하는 특정 포트 번호를 한 장치에서 다른 장치로 전달하는 기술. 

### 언제 사용할까?
* 내부 네트워크에서 서버를 호스팅하고, 외부에서 해당 서비스에 접근할 수 있도록 하는 경우
* 내부 네트워크에서 보안 카메라 등 장치를 사용하고, 외부에서 해당 장치에 접근할 수 있도록 하는 경우

### 뭐가 필요할까?
* 프로토콜
	* TCP/UDP 둘 다
	* TCP
	* UDP
* 외부 포트 시작
* 외부 포트 끝
	* 외부에서 접근하고자 하는 포트의 범위를 시작 ~ 끝으로 지정.
	* 보통 하나만 있으므로 시작과 끝을 같은 값으로 지정.
* 내부 IP 주소
	* 포트 포워딩을 적용시키려고 하는 로컬 IP 주소를 입력.
	* 즉 어떤 디바이스에 대해 이 포트포워딩을 수행할것인지 결정.
* 내부 포트 시작
* 내부 포트 끝
	* 내부에서 접근하고자 하는 포트의 범위를 시작 ~ 끝으로 지정.
	* 보통 하나만 있으므로 시작과 끝을 같은 값으로 지정.

### NAT와의 순서?

외부에서 내부로 들어오는 네트워크에 대해:
	1. NAT가 작동. 공인 IP -> 사설 IP 로 변환
	2. 포트 포워딩 작동. 포트 변환.

## DMZ

![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/NAT%20/%20NAT_3_DMZ.png)
DMZ 선택 시 - IP 주소 입력 란 활성화
Super DMZ 선택 시 - 네트워크 내에 감지된 MAC 주소 선택 란 활성화

외부 네트워크에 서비스를 제공하면서 내부 네트워크는 보호하는 영역. (외부에 오픈된 서버영역)

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FGdtg3%2FbtrC1iDQiOD%2FRPakGslhkJo3Cgvyc6Ba70%2Fimg.png)


## VPN

![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/NAT%20/%20NAT_4_VPN.png)

VPN passthrough : VPN 트래픽이 이 라우터 (방화벽)을 통과할 수 있는지 설정
- IPSEC : 안전한 통신을 위한 프로토콜.
- PPTP : 오래된 VPN 프로토콜 중 하나.

이를 활성화하지 않는다면, VPN 트래픽을 우리 네트워크로 들여올 수 없다.

## Network 설정

![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/NAT%20/%20NAT_5_Network_Config.png)

WAN 설정, LAN 설정, DHCP 서버 설정, DHCP 서버 예약 IP 추가 및 리스트를 관리할 수 있다.

특히 WAN 설정에서 운용 모드가 NAT라고 되어있는데, 다음 옵션을 선택할 수 있다.
- NAT : 공인 IP 주소를 사설 IP 주소로 변환시키는 모드
- Bridge : 라우터를 단순 브릿지로 동작시키는 모드. 네트워크 계층이 아닌, 스위치나 허브처럼 동작함.
- Controller/NAT : 컨트롤러 역할 + NAT역할을 함. 컨트롤러는 네트워크 트래픽을 관리하고 분배함.
- Controller/Bridge : 컨트롤러 역할 + 브릿지 역할
- Agent : 라우터가 다른 네트워크 디바이스 또는 시스템과 협력하여 특별한 기능(네트워크 관리 및 감시, 보안 및 방화벽 협력, 품질 서비스 관리, 외부 시스템과의 통합, 프록시 또는 캐시 서버 기능)을 수행.
- Repeater : 신호를 중계하여 무선 네트워크의 범위를 확장하는 역할.

연결 방식은 다음 옵션을 사용할 수 있다.
- DHCP : 네트워크에서 자동으로 IP주소, 서브넷마스크, 기본 게이트웨이, DNS 등 네트워크 설정을 부여하는 프로토콜.
- Static : IP 주소, 서브넷마스크, 기본 게이트웨이, DNS 등 네트워크 설정이 고정되어 있는 상태. (군대에서 애용함.)

