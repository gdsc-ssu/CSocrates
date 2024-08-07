#HTTP_개관

	얼마나 많은 웹 애플리케이션이 HTTP를이용해통신하고, HTTP가 어떻게 그 일을 해내는지 개략적으로 설명함
	간단하게 HTTP에 대해 훑어보자

---
### HTTP - 인터넷의 멀티 미디어 배달부

**HTTP : Hypertext Transer Protocol
전세계의 웹 브라우저, 서버, 웹 애플리케이션은 모두 http를 통해서로 대화. http는 현대 인터넷의 공용어**

HTTP는 신뢰성있는 데이터 전송프로토콜을 사용하기 때문에, 데이터가 지구 반대편에서 오더라도 전송중 손상되거나 꼬이지 않음을 보장함

*그렇다면 http가 웹 트래픽을 어떻게 전송할까..?

### 웹 클라이언트와 서버

![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTP%20%EA%B0%9C%EA%B4%80%20/%20%EC%9B%B9%20%ED%81%B4%EB%9D%BC%EC%9D%B4%EC%96%B8%ED%8A%B8%EC%99%80%20%EC%84%9C%EB%B2%84.png)
클라이언트는 서버에게 HTTP 요청을 보내고 서버는 요청된 데이터를 HTTP 응답으로 돌려줌

**클라이언트**
	- 웹 서버에게 데이터를 요청
	- 실제 사용자는 웹 브라우저(클라이언트)를 통해 다양한 컨텐츠를 사용
	- HTTP 요청을 통해 웹 서버와 관계를 맺기 때문에 HTTP Client 라고 불리기도 함
	- *ex. 마이크로소프트 인터넷 익스플로러, 구글/크롬 웹브라우저*
 
**서버**
	- 웹 클라이언트의 요청을 처리하여 응답을 보내주는 주체
	- 인터넷이라는 네트워크 통신망을 통해 처리 결과(콘텐츠)를 전달
	- 웹서버는 HTTP 프로토콜로 의사소통하기 때문에 보통 HTTP서버라고 불림

### 리소스

![500](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTP%20%EA%B0%9C%EA%B4%80%20/%20%EC%9B%B9%20%EB%A6%AC%EC%86%8C%EC%8A%A4.png)

웹 서버는 웹 리소스를 관리하고 제공함

**웹 리소스**
	-  웹 서버가 관리하는 컨텐츠(데이터)의 원천을 의미
	-  크게 정적 파일(텍스트, HTML, 이미지, 동영상)과 동적 파일(주식 거래, 부동산 데이터베이스 검색) 로 나눌 수 있음
	- 리소스가 동적 파일이라면 동적 컨텐츠를 만들어내는 프로그램이 될 수도 있음
	- 어떤 종류의 컨텐츠 소스도 리소스가 될 수 있음

### 미디어 타입

![600](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTP%20%EA%B0%9C%EA%B4%80%20/%20%EB%AF%B8%EB%94%94%EC%96%B4%20%ED%83%80%EC%9E%85.png)

인터넷은 수천가지 데이터타입을 다루기 때문에, HTTP는 웹에서 전송되는 객체 각각에 신중하게 ==MIME타입==이라는 데이터 포맷라벨을 붙임

**MIME ( Multipurpose Internet Mail Extensions)** -> 다목적 인터넷 메일 확장

	SMTP할때 나왔던 MIME타입으로 데이터간 전송에서 문제점을 해결하기 위해 나옴
	이는 HTTP에서도 멀티미디어콘텐츠를 기술하고 라벨 붙이기 위해 채택
	
MIME
	- 인터넷은 수많은 데이터 타입을 다루기 때문에 불일치 패러다임을 해결하기 위해 표준화된 데이터 타입이 필요
	- 웹에서 전송되는 객체에 각각 MIME 데이터 포멧 라벨을 붙임
	- MIME 타입은 사선(/)으로 구분된 주 타입과 부 타입으로 이루어진 문자열 라벨
		- ex. HTML -> text/html , JPEG -> image/jpeg
[MIME 타입](https://developer.mozilla.org/ko/docs/Web/HTTP/Basics_of_HTTP/MIME_types/Common_types)

### URI

URI(Uniform Resource Identifier, 통합 자원 식별자)

	웹 서버 리소스는 각자 자신의 이름을 가짐
	URI는 인터넷의 우편물 주소 같은 것으로 고유하게 식별하고 위치를 정할 수 있음
	URL과 URN 두 가지 타입이 존재함

 **URL (Uniform Resource Locator, 통합 자원 지시자)**
	 - 가장 대중화된 리소스 식별자
![300](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTP%20%EA%B0%9C%EA%B4%80%20/%20URL.png)
	 - URL의 첫 번째 부분은 스킴(Scheme)이라고 불리는데, 사용되는 프로토콜을 서술
	 - 두 번째 부분은 인터넷 주소(IP & Port)를 제공
	 - 마지막은 웹 서버의 리소스

**URN(Uniform Resource Name, 통합 자원 이름)**
	- 위치에 영향을 받지 않음
	- 위치 독립적인 URN은 리소스를 여기저기로 옮기더라도 문제 없이 이동
	- 리소스가 그 이름을 변하지 않게 유지하는한, 여러종류의 네트워크 접속 프로토콜로 접근해도 문제없음
	- 하지만 아직 실험중인 단계로 널리 사용되지 않음. 현재의 URI는 URL로 통함
	- ex. RFC 2648을 가리키는 URN
		- urn:ietf:rfc:2648

### 트랜젝션

클라이언트가 웹 서버와 리소스를 주고받기 위해 HTTP를 어떻게 사용하는지 자세히 알아보면...

![600](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTP%20%EA%B0%9C%EA%B4%80%20/%20%ED%8A%B8%EB%9E%9C%EC%A0%9D%EC%85%98.png)

HTTP 트랜젝션은 **요청 명령**과 **응답 결과**로 구성되어 있는데 이는 HTTP 메시지라고 불리는 정형화된 데이터 덩어리를 통해 이뤄짐

**메서드**
	- HTTP는 HTTP 메서드라고 불리는 여러가지 종류의 **요청 명령**을 지원한다.

메서드 종류
	- ==GET== : 서버에서 클라이언트로 지정한 리소스를 보내라
	- ====PUT== : 클라이언트에서 서버로 보낸 데이터를 지정한 이름의 리소스로 저장해라
	- ==DELETE== : 지정한 리소스를 서버에서 삭제해라
	- ==POST==:  클라이언트 데이터를 서버 게이트웨이 애플리케이션으로 보내라
	- ==HEAD== : 지정한 리소스에 대한 응답에서, HTTP 헤더 부분만 보내라

**상태코드**
	- HTTP 응답 메세지는 세자리 숫자로 구성된 **상태 코드**와 텍스트로 된 **사유 구절**(reason phrase)이 함께 반환됨. 서버는 다음과 같이 상태코드를 통해 클라이언트에게 요청이 어떻게 처리되었는지를 알려줌

상태코드 종류
	- 200: 좋다. 문서가 바르게 반환되었다.
	- 302: 다시 보내라. 다른 곳에 가서 리소스를 가져가라.
	- 404: 없음. 리소스를 찾을 수 없다.

	사유 구절
		-사유구절은 단지 설명만을 위해 포함된 것으로 실제 응답 처리에는 상태코드가 사용된다.
		- ex. 200 OK , 200 Document attached , 200 Success , 200 All's cool dude

> 	웹 페이지는 여러 객체로 이루어 질 수 있음
> 	애플리케이션은 보통 하나의 작업을 수행하기 위해 여러 HTTP 트랜잭션을 수행
> 	==웹페이지는 보통 하나의 리소스가 아닌 리소스의 모음==

### HTTP 메세지

![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTP%20%EA%B0%9C%EA%B4%80%20/%20HTTP%20%EB%A9%94%EC%84%B8%EC%A7%80.png)

- HTTP 메세지는 단순한 줄 단위의 문자열
- 일반 텍스트 형식이기 때문에 사람이 읽고 쓰기 쉬움
- 웹 클라이언트에서 웹 서버로 요청 할때 보내는 메세지를 **요청 메세지**라고 하며,  웹 서버가 요청 처리 후, 웹 클라이언트에게 보내는 메세지를 **응답 메세지**라고 함

![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTP%20%EA%B0%9C%EA%B4%80%20/%20HTTP%20%EB%A9%94%EC%84%B8%EC%A7%80%202.png)

- 시작줄
	- 요청 메세지든 응답 메세지든 메세지의 첫 줄은 시작줄로, 요청이라면 무엇을 해야 하는지 응답이라면 요청으로 인해 무슨 일이 일어났는지를 나타냄
- 헤더
	- 시작줄 다음에는 0개 이상의 헤더 필드가 이어짐
	- 각 헤더 필드는 쉬운 구문분석을 위해 쌍점(:)으로 구분되어 있는 하나의 이름과 하나의 값으로 구성됨
	- 헤더 필드를 추가하려면 그저 한 줄을 더하기만 하면 됨
- 본문
	- 헤더에 이어 빈 줄([CR+LF])이 나오고 본문이 이어짐
	- 본문에는 어떤 종류의 데이터든 들어갈 수 있는 메세지 본문이 필요에 따라 올 수 있음 
	- 요청의 본문은 데이터를 실어 보내며, 응답의 본문은 데이터를 반환 
	- 시작줄이나 헤더와 달리 이진 데이터를 포함 할 수 있음

### TCP 커넥션

HTTP 포로토콜은 네트워크 통신에는 신경 쓰지 않으며, 이와 관련된 부분은 TCP 프로토콜에 위임  
클라이언트는 요청을 위해 요청 메세지를 전송하기 전에, 서버의 IP와 Port를 가지고 서버와 TCP/IP 커넥션을 맺어야 함
서버의 IP와 Port 는 요청하는 URL을 통해 알 수 있음

### 프로토콜 버전

- HTTP/0.9
- НТТР/1.0
- НТТР/1.0+
- HTTP/1.1
- HTTP/2.0

### 웹의 구성요소

어떻게 메세지를 주고 받는지 알아보았다면, 인터넷과 상호작용 할 수 있는 웹 애플리케이션에 대해 알아보자

**프락시 (Proxy)**

![300](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTP%20%EA%B0%9C%EA%B4%80%20/%20%ED%94%84%EB%9D%BD%EC%8B%9C.png)

프락시(Proxy)는 중개인이라는 뜻으로 이름에서도 알 수 있듯이 웹 클라이언트와 웹 서버 사이에 위치하여, 클라이언트의 모든 HTTP 요청을 받아 서버에 전달함

*그렇다면 왜 웹 클라이언트에서 바로 웹 서버로 요청을 보내는 것이 아니라, 중간에 프락시를 둘까?*
	- **보안을 위해서**
		- 사용자(웹 클라이언트)를 대신해 서버에 접근하여 요청을 하고 돌아온 응답에 대해 에상되는 웹 콘텐츠 및 악성 코드를 필터링 함으로써 클라이언트 측의 보안을 향상시킴
	- **캐싱을 통해 빠르게 리소스에 접근 할 수 있음**
		- 웹 클라이언트와 웹 서버 사이에 존재하기 때문에, 웹 클라이언트가 자주 요청하는 데이터(사본)를 프락시 서버에 저장해 놓을 수 있음
		- 이를 통해 웹 서버에 접근하기 전에 더욱 빨리 프락시 서버로 부터 데이터를 가져올 수 있음
	- **서버의 병목 현상을 방지할 수 있음**
		- 앞에서 설명한 캐시 기능 때문에 모든 웹 클라이언트가 웹 서버에 접근할 필요가 없음. 따라서 병목 현상을 방지할 수 있음

**캐시**

웹 캐시와 캐시 프락시는 자신을 거쳐 가는 문서들 중 자주 찾는 것의 사본을 저장해두는, 특별한 종류의 HTTP프락시 서버. 다음번에 클라이언트가 같은 문서를 요청하면 그 캐시가 갖고있는 사본을 받을 수 있음

![500](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTP%20%EA%B0%9C%EA%B4%80%20/%20%EC%BA%90%EC%8B%9C.png)

**게이트 웨이**

게이트웨이는 **다른 서버들의 중개자로 동작하는 특별한 서버**. 앞에서 설명한 프락시와 비슷한 역할을 하지만 차이가 있음

게이트웨이는 프락시와 마찬가지로 중개자 역할을 하지만 서로 다른 **네트워크 통신에서 서로 다른 프로토콜을 호환가능하게 하는 역할**
주로 Http 프로토콜을 다른 프로토콜로 변환하기 위해 사용

![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTP%20%EA%B0%9C%EA%B4%80%20/%20%EA%B2%8C%EC%9D%B4%ED%8A%B8%20%EC%9B%A8%EC%9D%B4.png)

**터널**

터널은 두 커넥션 사이에서 raw 데이터를 열어보지 않고 그대로 전달해주는 HTTP 어플리케이션  
사용 목적은 HTTP 형태가 아닌 데이터를 HTTP 연결을 통해 그대로 전송해주기 위해 사용됨

HTTP 터널을 활용하는 대표적인 예로, 암호화된 SSL 트래픽을 HTTP 커넥션으로 전송함으로써 웹 트래픽만 허용하는 사내 방화벽을 통과시키는 것이 있음

![600](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/HTTP%20%EA%B0%9C%EA%B4%80%20/%20%ED%84%B0%EB%84%90%20%EC%98%88%EC%8B%9C.png)

**에이전트**

사용자 에이전트는 사용자를 위해 HTTP 요청을 만들어주는 클라이언트 프로그램  
웹 요청을 만들어줄 수 있으면 에이전트라고 할 수 있는데, **가장 대표적인 에이전트는 브라우저임**

브라우저는 사용자를 대신해 웹 서버에게 HTTP 요청을 보내며, 받아온 HTTP 응답을 사용자 편의에 맞게 보여줌