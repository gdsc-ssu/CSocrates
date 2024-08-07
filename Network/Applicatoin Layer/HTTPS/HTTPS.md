
### HTTP를 어떻게 안전하게 할 수 있을까?
- http의 보안버전은 효율적이고 이식성이 좋고, 관리가 쉬워야 하며, 현실 세계의 변화에 대한 적응력이 좋아야한다. 또한 사회와 정부의 요구사항에도 맞아야한다.
- 다음을 제공해주는 HTTP의 보안기술이 필요하다.
    - 서버 인증 : 클라이언트는 자신이 위조된 서버가 아닌 진짜와 이야기하고 있음을 알 수 있어야함
    - 클라이언트 인증 : 서버는 자신이 가짜가 아닌 진짜 사용자와 이야기하고 있음을 알 수 있어야 한다.
    - 무결성 : 클라이언트와 서버는 데이터가 위조되는것을 방지해야한다.
    - 암호화 : 클라이언트와 서버가 서로 안전하게 대화해야 한다.
    - 효율 : 저렴한 클라이언트나 서버도 이용할 수 있도록 알고리즘은 충분히 빨라야 한다.
    - 편재성(Ubiquity) : 프로토콜은 거의 모든 클라이언트와 서버에서 지원되어야 한다.
    - 적응성 : 현재 알려진 최선의 보안 방법을 지원해야 한다.

## HTTPS
- http를 안전하게 만드는 방식 중에서 가장 인기 있는 것 (SPDY, IPSec 등 다른 프로토콜도 존재)
	- 보안 전송 계층을 통해 전송되는 http이다
- 모든 주류 브라우저와 서버에서 지원한다.
	- firefox, safari, edge 등등

- 모든 http 요청과 응답 데이터는 네트워크로 보내지기 전에 암호화된다. https는 http의 하부에 “전송 레벨 암호 보안 계층”을 제공함으로써 동작.
    → 이 보안 계층은 안전 소켓 계층(SSL, Secure Sockets Layer)혹은 그를 계승한 전송 계층 보안(TLS, Transport Layer Security)을 이용하여 구현.
    → SSL과 TLS는 사실상 같기 때문에 SSL이라고 표기하기도 함
    - SSL : Netscape사에서 1995년에 만든 통신 프로토콜
    - TSL : SSL의 3.0버전을 가지고 Netscape가 개발에서 빠지며 국제 인터넷 표준화 기구 ****IETF(**[Internet Engineering Task Force](https://www.ietf.org/))**에서 만든 프로토콜
    ⇒ 현재는 SSL 2.0 및 3.0이 전부 사용 중지, 사실상 TLS만 사용.
    ⇒ 또한 TLS 1.0과 1.1도 사용 중지 예정
    ⇒ TLS 1.2 (2008년), TLS 1.3 (2018년)이 표준. (http3.0 은 TLS 1.3 필수)
    
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTPS%20/%20123.png)
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTPS%20/%20765432.png)
	    
- 인코딩 및 디코딩 작업은 대부분 SSL 라이브러리 안에서 일어나기 때문에 http의 로직을 크게 변경할 필요가 없다.

## 암호(cipher)
- 암호 : 메시지를 인코딩하는 어떤 특정한 방법과 나중에 그 비밀 메세지를 디코딩하는 방법을 말함.
- 원본 메세지(텍스트 or 평문)에 암호를 적용하면 암호문이 된다.
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTPS%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202023-01-06%20%EC%98%A4%ED%9B%84%205.31.12.png)
- 역사상 최초의 암호 : 스키테일 암호
    
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTPS%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202023-01-06%20%EC%98%A4%ED%9B%84%205.40.24.png)
- 카이사르의 순환암호
    
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTPS%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202023-01-06%20%EC%98%A4%ED%9B%84%205.40.44.png)
- 메세지의 각 글자를 알파벳 순서상 세번 뒤의 글자로 바꾸는 방법 사용

### 디지털 암호
- 디지털 시대로 넘어오면서 두가지의 변화
    - 속도 및 기능에 대한 전폭적인 성장, 훨씬 더 복잡한 인코딩과 디코딩이 가능해짐
    - 매우 큰 키를 지원하는 것이 가능해져 단일 암호 알고리즘으로 키의 값마다 다른 수조개의 암호 알고리즘을 만들어 낼 수 있게 됨.
- 평문 메세지 P, 인코딩 함수 E, 디지털 인코딩 키 e가 주어졌을 때 암호문 C를 생성할 수 있다.
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTPS%20/%2062138761283.png)

- 암호화 기법과 디지털 서명은 [[암호화 기법]]에 이미 존재하므로 여기서는 넘어간다.

### 사이트 인증서 검사
- 날짜 검사
	- 인증서의 유효기간을 검사
- 서명자 신뢰도 검사
	- 발급받은 CA가 믿을만한 기관인지 검사
- 서명 검사
	- CA의 공개키를 사용해 인증서의 무결성 검증
- 사이트 신원 검사
	- 인증서의 도메인 이름과 서버의 도메인 이름이 맞는지 검사



### 와이어 샤크로 ssl handshaking 뜯어보기
- 와이어 샤크를 사용해서 naver에 접속할 때 ssl 인증이 어떻게 이루어지는지 확인하기

- naver의 ip주소를 알아내기 위해서 nslookup 명령어 사용
	- 와이어샤크를 확인해보니 ipv6를 사용하길래 네이버의 ipv6 주소를 알아냄
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTPS%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-01-13%20%EC%98%A4%EC%A0%84%209.53.23%201.png)

- 와이어 샤크에서 naver의 ssl handshake만 보기 위해서 설정
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTPS%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-01-13%20%EC%98%A4%EC%A0%84%209.53.29%201.png)

- 설정 후 네이버 창을 켠뒤 와이어샤크 측정 종료

1. client hello 
	- 클라이언트가 서버에 처음으로 연결을 요청할 때 보냄
	- client의 SSL 버전, 세션 ID, Cipher Suites 등을 보낸다.
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTPS%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-01-13%20%EC%98%A4%EC%A0%84%209.52.21%201.png)
2. server hello
	- 클라이언트의 응답을 받았으며 SSL/TLS Handshake 를 진행
	- 클라이언트에서 받은 Cipher Suites 목록 중에 사용할 버전 확정해서 응답
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTPS%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-01-13%20%EC%98%A4%EC%A0%84%209.52.33%201.png)

3. Certificate
	- 서버가 클라이언트에게 자신의 디지털 인증서를 제공
	- 이 메세지에 있는 디지털 인증서를 기반으로 클라이언트가 서버의 신뢰성을 확인.
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTPS%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-01-13%20%EC%98%A4%EC%A0%84%209.52.46%201.png)
4. Server Key Exchange 
	- 서버 측에서 키 교환을 위해 서버의 인증서를 넘어서는 추가 데이터가 필요할 때 요청하는 메세지
		(서버의 공개키가 ssl 인증서에 없는 경우 여기서 보낸다.)
	 Server Hello Done
	 - ssl handshake에서 서버의 역할이 완료되었음을 알림 (서버가 보낼 건 다보냈다)
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTPS%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-01-13%20%EC%98%A4%EC%A0%84%209.52.53%201.png)

5. Client key Exchange
	- 클라이언트에서 공유할 비밀키 생성
	change Cipher Spec
	- 이제부터는 아까 위에서 협상했던 암호화 방법으로 통신을 전환하자고 알리는 것
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTPS%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-01-13%20%EC%98%A4%EC%A0%84%209.53.01%201.png)
6. New Session Ticket
	- 일종의 캐시 역할.
	- 클라이언트가 나중에 연결 시 빠른 연결을 위해 세션 티켓을 저장
	change Cipher Spec
	- 클라이언트의 요청과 똑같이 이제 암호화된 통신이라는 것을 의미
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTPS%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-01-13%20%EC%98%A4%EC%A0%84%209.53.11%201.png)
7. Application Data
	- 클라이언트에서 암호화된 통신으로 서버로 전송
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTPS%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-01-13%20%EC%98%A4%EC%A0%84%209.54.28%201%201.png)
8. Application Data
	- 서버에서도 클라이언트에 대한 응답으로 암호화된 데이터 전송
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTPS%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-01-13%20%EC%98%A4%EC%A0%84%209.54.41%201.png)



### Reference

https://a-gyuuuu.tistory.com/357
https://doongdangdoongdangdong.tistory.com/249
https://mandoo12.tistory.com/26