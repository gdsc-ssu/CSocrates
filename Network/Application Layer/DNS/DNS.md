## 참고
- https://aws.amazon.com/ko/route53/what-is-dns/
- https://www.ibm.com/kr-ko/topics/dns
- https://cano721.tistory.com/20
## 개요
- [[#DNS란?]]
- [[#DNS 서버 종류]]
- [[#DNS 쿼리 단계]]
- [[#DNS 레코드]]
- [[#DNS 관련 보안]]
- [[#추가 참고 사항]]
## DNS란?
DNS란 Domain Name System의 약자이다.
모든 사용자들은 특정한 호스트와 통신하려면 해당 호스트의 주소를 알아야한다. 대표적으로 사용되는 것이 #IP 이다.
하지만 내가 특정한 웹사이트, 호스트에 접속하기 위해서 모든 번호를 알아야한다면 얼마나 불편할까?
그래서 **전화번호부**와 같은 기술을 도입했다. 바로 DNS이다.
DNS를 사용하면 IP 주소를 기억하는 대신 인터넷 도메인 이름과 URL을 통해서 웹사이트에 접속할 수 있다.

어떻게 확인할 수 있을까?
nslookup을 활용할 수 있다.
![[스크린샷 2023-12-30 오전 2.27.51.png]]![[스크린샷 2023-12-30 오전 2.28.22.png]]
## DNS 서버 종류
- Root
	- ICANN에서 관리하는 최상위 루트 DNS 서버
	- TLD 서버의 IP를 저장하고 있다.
	- 기존에는 13개의 서버였지만, 현재 1034개의 서버가 작동한다.![[Pasted image 20231230030014.png]]
- TLD (Top Level Domain)
	- 도메인 등록 기관이 관리하는 서버이다.
	- Authoritative DNS Server 주소를 저장하고 있다.
- Authoritative DNS Server
	- SLD (Second Level Domain) DNS Server라고도 부른다.
	- 실제 개인 도메인과 IP 주소의 관계가 기록/저장/변경되는 서버
- Recursive DNS Server
	- Local DNS Server라고도 부르며, 사용자가 가장 먼저 접근
	- 한번 데이터를 얻으면 캐시하고, 사용자에게 전달하며, 없다면 상위 서버에 질의한다.

![[Pasted image 20231230025554.png]]
## DNS 쿼리 단계

![[Pasted image 20231230025255.png]]

1. 사용자가 브라우저를 열어 도메인 이름을 작성하고 enter 입력
2. www.example.com 의 요청을 ISP에 쿼리
3. ISP의 DNS 해석기는 이 요청을 DNS Root Name Server로 전달
4. ISP의 DNS 해석기는 .com 도메인의 TLD Name Server로 전달
5. ISP의 DNS 해석기는 Route53 Name Server를 선택하여 요청을 서버에 전달
6. Route53 Name Server는 주소에 맞는 IP 전달.
7. 실제 유저에게 데이터를 전달한다. 추후 동일한 Query가 올 것을 예상하고, 일정 기간동안 IP 주소를 캐싱한다.
8. 브라우저는 DNS 해석기로부터 얻은 정보를 토대로 www.example.com 에 대한 요청, IP 주소로 연결 시도
9. 실제 서버에서 정보가 도착한다.

## DNS 레코드
- A
	- 도메인 이름을 IPv4 주소로 변환한다.
- AAAA 
	- 도메인 이름을 IPv6 주소로 변환한다.
- CNAME (Canonical NAME)
	- 실제 호스트명 (A레코드)과 연결되는 별명, 별칭을 정의한다.
	- 예를 들어 아래와 같은 경우, mydomain.com은 A 레코드로 IP 주소와 연결되어 있지만 fpt.mydomain.com이나 www.blog.mydomain.com 으로 되어있는 부분은 CNAME으로 설정되는 경우, 해당 도메인을 통해 A 레코드의 도메인으로 연결할 수 있다.![[스크린샷 2024-01-01 오전 3.28.47.png]]
- MX (Mail Exchange)
	- 메일서버에 도달할 수 있는 라우팅정보를 제공
- NS (Name Server)
	- 인터넷에서 해당 도메인의 IP를 찾기 위해서 가야할 곳을 안내
	- 결과적으로 어떤 DNS가 해당 도메인의 권한 있는 Name Server인지 지시

AWS의 Route53, GCP의 Cloud DNS와 같은 서비스에서 이러한 DNS를 사용할 수 있다.
![[스크린샷 2023-12-30 오전 2.34.11.png]]
### A vs AAAA
DNS 레코드를 보면 뭐가 다른지 항상 궁금했다.
[CloudFlare의 설명](https://www.cloudflare.com/ko-kr/learning/dns/dns-records/dns-aaaa-record/) 을 보면 A는 IPv4, AAAA는 IPv6에 대응되는 도메인 이름을 가져오도록 한다고 설명한다.
나머지 부분은 동일하다.

## DNS 관련 보안

- DNS 하이재킹
	- DNS 쿼리가 잘못 처리되어, 잘못된 사이트로 리다이렉션 시키는 경우
	- DNS 통신을 가로채는 멀웨어가 설치된 경우, DNS 하이재킹이 발생할 수 있다.
- DNS 캐시 오염
	- 공격자가 DNS 서버에 대한 제어력을 갖고 입력된 IP 주소를 손상시키는 경우, 잘못 입력된 IP 주소는 전세계 인터넷으로 전파되고, 캐시되어서 퍼블릭 DNS처럼 작동
	- DNSSec을 사용한다.

## 추가 참고 사항
#### DNS는 UDP를 사용
저번에도 얘기했듯이, DNS는 UDP를 사용한다.
크기가 작아서 유실 될 확률도 적으며, 단순 통신이 왔다갔다하는 경우이기 때문에 신뢰성이 있는 연결이 필요 없다.