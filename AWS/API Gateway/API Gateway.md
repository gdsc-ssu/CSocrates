## RESTful API

### REST(REpresentational State Transfer)

HTTP 통신에서 어떤 자원에 대한 CRUD 요청을 Resource와 Method로 표현하여 특정한 형태로 전달하는 방식

> [!REST(REpresentational State Transfer)]
> **HTTP 통신에서 어떤 자원에 대한 CRUD 요청을 Resource와 Method**

즉 REST란 어떤 자원에 대해 CRUD(CREATE, READ, UPDATE, DELETE) 연산을 수행하기 위해 URI(Resource)로 요청을 보내는 것으로, Get, Post 등의 Method를 사용하여 요청을 보내며 요청을 위한 자원은 특정한 형태로 표현 됨.

	ex) 
	게시글을 작성하기 위해 특정 URI(http://localhost:8080/board)에 
	POST 방식을 통해 JSON 형태의 데이터를 전달 가능

위와 같이 CRUD 연산에 대한 요청을 할 때 요청을 위한 Resource(자원, URI)와 이에 대한 Method(행위, POST) 그리고 Representation of Resource(자원의 형태, JSON)을 사용하면 표현이 명확해지므로 이를 REST라고 하며, 이러한 규칙을 지켜서 설계된 API를 REST API 또는 RESTful API라고 함

> [!RESTful API 구성요소]
> - **Resource**  
 >   서버는 Unique한 ID를 가지는 Resource를 가지고 있으며, 클라이언트는 이러한 Resource에 요청을 보냄
 >   이러한 Resource는 URI에 해당합니다.
>- **Method**  
 >   서버에 요청을 보내기 위한 방식으로 GET, POST, PUT, PATCH, DELETE 존재
 >   CRUD 연산 중에서 처리를 위한 연산에 맞는 Method를 사용하여 서버에 요청을 보내야 함
>- **Representation of Resource**  
 >   클라이언트와 서버가 데이터를 주고받는 형태로 json, xml, text, rss 등이 존재
 >   최근에는 Key, Value를 활용하는 json을 주로 사용

#### GET VS POST
>**GET**은 어떤 정보를 조회하기 위해 사용하는 방식
>- URL에 변수를 포함시켜 요청
>- 데이터를 HEADER에 포함하여 전송
>- URL에 데이터가 노출되어 보안에 취약
>- 캐싱 가능
>GET 방식은 간단한데이터를 URL에 넣도록 설계된 방식으로 데이터를 보내는 양에 한계 존재
>HTTP 자체는 GET 방식의 URL 길이에 제약을 두진 않지만 브라우저에서 최대 길이 제한
>URL 형식에 맞지 않는 파라미터 이름이나 값은 인코딩되어 전달되어야 함

>**POST**방식은 데이터를 서버로 제출하여 추가 또는 수정하기 위해서 사용되는 방식
>- URL에 변수(데이터)를 노출하지 않고 요청
>- 데이터를 BODY에 포함
>- URL에 데이터가 노출되지 않아서 기본 보안은 존재
>- 캐싱 불가능
>POST 방식은 BODY에 데이터를 넣어서 전송하기에 헤더필드 중 BODY 의 데이터를 설명하는 Content-Type이라는 헤더 필드가 들어가고 어떠한 데이터 타입인지를 명시해주어야 함
>BODY에 데이터를 적재하기 때문에 메시지 길이 제한은 없지만 최대 요청을 받는 시간인 Time Out이 존재하므로 클라이언트에서 페이지를 요청하고 기다리는 시간이 존재
>실제로 POST 방식은 URL에 데이터가 노출되지 않으므로 즐겨찾기나 캐싱이 불가능하지만 쿼리스트링 데이터 뿐만 아니라 라디오 버튼, 텍스트 박스와 같은 객체들 값도 전송 가능 


#### URI VS URL
>**URL(Uniform Resource Locator)**
>인터넷 상 자원의 위치를 의미 즉 파일의 위치를 의미하는 것과 같음

>**URI(Uniform Resource Identifier)**
>인터넷 상의 자원을 식별하기 위한 문자열의 구성으로, URI는 URL을 포함하는 개념임

#### REST의 조건
1. **Uniformed Interface**
	1. Resource(URI)에 대한 요청을 통일되고 한정적으로 수행하는 아키텍처 스타일
	2. 요청 주체인 Client가 플랫폼에 무관하며 특정 언어나 기술에 종속 받지 않는 특징을 의미
	3. HTTP를 사용하는 모든 플랫폼에서 요청 가능하며, 느슨한 결합 형태를 갖춤
2. **Stateless**
	1. 서버는 각각의 요청을 별개로 인식 및 처리해야 함
	2. Rest API는 세션정보나 쿠키 정보를 활용하여 작업을 위한 상태정보를 저장하지 않음
	3. 무상태성은 서버 처리방식에 일관성을 부여하고 서버의 부담을 줄임
3. **Cacheable**
	1. REST API는 결국 HTTP라는 기존의 웹표준을 사용하기 때문에 캐싱 기능을 적용 가능
4. **Client-Server Architecture**
	1. REST API에서 자원을 가지고 있는 서버, 자원을 요청하는 클라이언트로 구조화 되어있으며 서버는 API를 제공하고 클라이언트는 사용자 인증, CONTEXT(세션, 로그인 정보) 등을 직접 관리하는 등 역할을 구분하여 의존성을 줄임
	2. ![[Pasted image 20240810033429.png]]
		1. 객체지향은 오로지 협력과 메시지로 구성
		2. 협력은 클라이언트가 서버의 서비스를 요청하는 단방향 상호작용
		3. 객체는 협력에 참여하는 동안 클라이언트와 서버의 역할을 동시에 수행하는 것이 일반적
		4. Message
		    1. 객체지향에서 협력을 구성하기 위한 유일한 수단
		    2. 협력 →송신자, 수신자 생김
		        1. 메세지 전송자
		        2. 메세지 전송
		        3. 메세지 수신자
		        ![[Pasted image 20240810033718.png]]
		5. Method
			1. discount validator는 discountcondition에 할인을 만족하는지를 확인 위해 메시지를 통해 협력을 요구
			2. 컴파일 시점에서는 인식 x
			3. 런타임 시점에서 discount condition의 isSatisfedBy 오퍼레이션이 실행되는지 알 수 있다
			→메시지 수신했을 때 실제로 실행되는 함수를 메서드
			![[Pasted image 20240810033838.png]]


			
5. **Self-Descriptiveness**
	1. REST API는 요청 메세지만 보고도 쉽게 이해할수 있는 자체 표현 구조로 구성되어 있음
6. **Layered System**
	1. REST API의 서버는 다중 계층으로 구성 가능함
	2. 보안, 로드 밸런싱, 암호화 등을 위한 계층을 추가해 구조 변경이 가능
	3. Proxy, Gateway와 같은 네트워크 기반의 중간매체를 사용할 수 있게 해줌

#### MVC 패턴이란

디자인 패턴 중 하나로 소프트웨어를 Model, View, Controller 세가지 주요 컴포넌트로 나누어 구조화하는 방법

MVC는 주로 UI를 개발하는데 사용되며 각 컴포넌트가 각자의 영갛ㄹ을 수행하며 시스템을 보다 모듈화하고 확장 가능하게 만듦

![[Pasted image 20240810034830.png]]

**MODEL**
- 어플리케이션의 데이터와 비즈니스 로직을 담당
- 데이터를 저장하고 조작하는 역할을 수행
- 데이터 변경을 감지하고 변경 시  VIEW 및 CONTROLLER에 알림 보냄

**VIEW**
- 사용자에게 정보를 표시하고 입력을 받는 역할 수행
- 모델의 데이터를 시각적으로 표현하거나 사용자 인터페이스 요소를 생성
- 모델의 변경을 감지하여 자동으로 업데이트 되도록 구현
- SPRING MVC에는 HTML 페이지 출력, PDF/EXCEL 문서 출력, XML/JSON 포맷 변환 등 다양한 VIEW 기술이 포함되어 있음

**CONTROLLER**
- 사용자의 입력을 받아 모델에 명령을 전달하거나, 모델의 상태를 변경
- 사용자의 액션에 따라 모델을 업데이트하고, 그에 따라 뷰를 갱신
- 모델과 뷰 사이의 중간 역할을 수행하여 둘간의 직접적인 상호 작용을 방지 

#### SPRING MVC 구조 

![[Pasted image 20240810035126.png]]

**DispatchServlet**
- Front Controller의 역할을 수행하며 Request를 각각의 Controller에게 위임
- 가장 앞 단에서 클라이언트의 요청을 처리하는 Controller로써 **요청부터 응답까지 전반적인 처리 과정을 통제**

**HandlerMapping**
- 요청을 직접 처리할 컨트롤러를 탐색
- 구체적인 Mapping은 xml파일이나 java config 관련 어노테이션 등을 통해 처리할 수 있음


 **HandlerAdapter**
- 매핑된 컨트롤러의 실행을 요청

**Controller(Handler)**
- DispatcherServlet이 전달해준 HTTP 요청을 처리하고 결과를 Model에 저장
    - 직접 요청을 처리하며, 처리 결과를 반환
    - 결과가 반환되면 HandlerAdapter가 ModelAndView 객체로 변환되며, 여기에는 View Name과 같이 응답을 통해 보여줄 View에 대한 정보와 관련된 데이터가 포함

**ModelAndView**
- ModelAndView는 Controller에 의해 반환된 Model과 View가 Wrapping된 객체

**View Resolver**
- View Name을 확인한 후, 실제 컨트롤러로부터 받은 로직 처리 결과를 반영할 View 파일(jsp)을 탐색

**View**
- 로직 처리 결과를 반영한 최종 화면을 생성한다.

#### Spring MVC VS RESTful API

우리가 주로 개발하는 방식 프론트 / 백 협업 방식은 MVC 패턴에 부합하는가?

**Spring MVC**
![[Pasted image 20240810040419.png]]
클라이언트의 요청이 들어오면 ViewResolver를 통해 클라이언트에게 text/html , jsp 타입 혹은 파일의 경로 타입의 view 응답을 보냄

**RESTful API**
![[Pasted image 20240810040512.png]]
클라이언트의 요청이 들어오면 MessageConverter를 통해 application/json이나 text/plain등 알맞은 형태로 리턴( HTTP Response )
REST API는 HTTP 프로토콜 상에서 클라이언트가 서버를 호출하여 데이터를 받는 방식을 쉽게 정리한 표준화된 방식으로 @RestController 어노테이션을 통해 쉽게 구현 가능

MVC는 DispatcherServlet을 걸쳐 view를 응답하지만, RESTful Api는 DispatcherServlet을 거치지 않고 json 형식의 데이터를 응답

유승한피셜 :
우리가 주로 이용하는 협업 방식에서 서버와 프론트는 하나의 애플리케이션이 아니며 서버만 분리해서 봤을 때 MODEL과 VIEW를 사용하지 않고 CONTROLLER가 클라이언트 요청에 따라 데이터를 반환해주기만 하면 됨. 즉 MVC프레임워크를 이용하지만 MVC 구조라고 부르기에 부족함이 있음.

관련된 논의 : 
https://okky.kr/questions/1408882
https://www.inflearn.com/community/questions/1263068/mvc%EC%99%80-api%EC%9D%98-%EC%B0%A8%EC%9D%B4%EC%A0%90


## API GATEWAY

#### 특징
- 규모에 상관없이 API 생성, 유지 관리, 모니터링과 보호를 할 수 있게 해주는 서비스
- Client에서 Server로 통신할 때 API 들의 대문 역할을 한다고 볼 수 있음
- API Gateway를 사용하면 실시간 양방향 통신 애플리케이션이 가능하도록 하는 RESTful API 및 WebSocket API를 작성할 수 있음
- API Gateway는 트래픽 관리, CORS 지원, 권한 부여 및 액세스 제어, 제한, 모니터링 및 API 버전 관리 등 최대 수십만 개의 동시 API 호출을 수신 및 처리하는 데 관계된 모든 작업을 처리

#### 가격
![[Pasted image 20240810043044.png]]


#### API 유형
![[Pasted image 20240810043109.png]]


![[Pasted image 20240810043144.png]]

#### 실습

GET 메서드 API(책보다 간단!)
https://inpa.tistory.com/entry/AWS-%F0%9F%93%9A-API-Gateway-%EA%B0%9C%EB%85%90-%EA%B8%B0%EB%B3%B8-%EC%82%AC%EC%9A%A9%EB%B2%95-%EC%A0%95%EB%A6%AC




#### API GATEWAY PATTERN이란?

![[Pasted image 20240810044503.png]]
-  API Gateway Pattern 이란 마이크로 서비스로 나눠진 백엔드 서버들 앞에 하나의 API Gateway를 둠으로써 클라이언트는 API Gateway에 노출된 경로만 호출하고 요청된 라우트에 따라 적절한 서비스로 라우팅 시키고 response를 내려주는 것
- 소프트웨어 아키텍처에서 클라이언트와 여러 백엔드 서비스 간의 상호 작용을 관리하기 위한 디자인 패턴
- 클라이언트가 다양한 서비스에 접근할 때 일관된 인터페이스를 제공함으로써 시스템의 복잡성을 줄이고 관리 용이성을 높이는 것이 목표
- 실제 아키텍처에는 Private한 VPC구조로 인해 내부에 있는 서비스과 외부에 있는 게이트웨이가 소통하기 위해서는 Private Link, VPC Endpoint가 필요
- AWS PrivateLink 를 사용하면 AWS 네트워크 내에서 네트워크 트래픽을 유지하면서 AWS 서비스 및 다른 AWS고객이 호스팅하는 서비스에 접근 가능

> [!PrivateLink?]
> VPC와 서비스 간에 프라이빗 연결을 제공하는 기술
> https://seongduck.tistory.com/247

#### VPC links for REST APIs

![[Pasted image 20240810045602.png]]


#### MSA(MicroService Architecture)?

토스에서 Gateway를 쓰는 방식
https://toss.tech/article/slash23-server