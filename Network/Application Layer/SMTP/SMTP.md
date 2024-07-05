#전자메일 #SMTP

*Simple Mail Transfer Protocol(단순 전자우편 전송 프로토콜)*
**인터넷을 통해 이메일 메시지를 보내고 받는 데 사용 되는 통신 프로토콜**

### 인터넷 이메일 시스템 구조

![400](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/SMTP%20/%20%EC%9D%B8%ED%84%B0%EB%84%B7%20%EC%9D%B4%EB%A9%94%EC%9D%BC%20%EC%8B%9C%EC%8A%A4%ED%85%9C%20%EA%B5%AC%EC%A1%B0.jpeg)
user agent : 개인이 메일을 읽거나 쓸때 사용, 관리 기능 수행
mail server : 다수 사용자들의 메일 박스 관리, 메일 송/수신 제어

==메일 서버들 간에 통신을 지원하는 프로토콜이 SMTP==
*메일을 전송만 하지 다운로드하는 기능은 없다*

#### 동작 과정

![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/SMTP%20/%20%EB%8F%99%EC%9E%91%20%EA%B3%BC%EC%A0%95.jpeg)

	1️⃣ 송수신자 user agent에서 메일 작성 후 서버로 전송
	2️⃣ 송수신자 메일 서버의 출력 메세지 큐에 저장
	3️⃣ 수신자 메일 서버로 전송
	4️⃣ 전송 불가시 30분 단위로 재전송 시도, 정해진 기간 동안 전송 불가시 중단 및 송수신자에서 통보
	5️⃣ 수신자 메일 서버의 수신자 메일 박스에 저장
	6️⃣ 수신자 user agent에서 메일 서버의 메일 박스의 메일 읽기 및 관리

> 수신자가 user agent가 자신의 메일 박스에 있는 메세지를 가져갈때는 SMTP를 쓰는게 아니라 별도의 mail access protocol을 사용함
> 
> 수신자 user agent는 mail server와 다르게 항상 켜져있는 것이 아니기에 SMTP로 push방식을 사용하는 것이 아니라 다른 메일 프로토콜로 pull방식으로 받는다 (ex. POP, IMAP, HTTP)

---
### SMTP

-  클라이언트 - 서버 프로토콜
	- 응용 계층 구조는 클라이언트 - 서버 구조와 P2P구조가 있는데 SMTP는 클라이언트 - 서버
	- 클라이언트 : 송신 메일 서버 / user agent
	- 서버 : 수신 서버 메일 / 송신 메일 서버
	
-  TCP 사용
	- 신뢰 전송을 위함
	- 서버 포트 번호 : 25
		- *HTTP는 80
	
-  ASCII 텍스트 프로토콜
	- SMTP는 명령어나 메일 메세지 모두 단순 7비트 ASCII여야 함
	- SMTP가 약 1980년대쯤 나온 오래된 프로토콜로 과거에는 문자열이기 떄문에 ASCII가 단점이 되지 않았지만 오늘날 이미지, 오디오, 동영상 등 멀티미디어 시대기에 메일 메세지를 ASCII로 변환하고 전송하고 전송된 ASCII 메세지를 또 원래 메세지로 변환해야 함 ~~낡았다~~
	- 참고로 HTTP는 전송 전에 멀티미디어 데이터를 ASCII로 변환하지 않음


#### 프로토콜 동작 절차

![500](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/SMTP%20/%20%EB%8F%99%EC%9E%91%20%EC%A0%88%EC%B0%A8.png)

	1️⃣ 처음 TCP 연결 설정. 연결이 설정되면 서버와 클라이언트는 애플리케이션 계층 핸드쉐이크를 수행
	2️⃣ 클라이언트가 송신자와 수신자의 전자 메일 주소를 제공
	3️⃣ 연결 설정 이후 메세지 전송
	4️⃣ 메세지를 다 보냈다면 명령어로 닫음

메일 전송 부분을 더 자세하게 보자면...

![|500](https://mblogthumb-phinf.pstatic.net/20110810_227/eqelizer_1312908510459_8kvr5N_png/080911_1648_04SMTPSimpl2.png?type=w420)

	1️⃣ MAIL FORM : 송신자 메일 주소 -> 250 ok 응답 받음
	2️⃣ RCPT To : 수신자 메일 주소 -> 250 ok 응답 받음
	3️⃣ DATA : 데이터 전송 시작 명령어
	4️⃣ 354 응답으로 데이터 input 시작
	5️⃣ '.'하나만 보내 메세지 전송이 끝났음을 알려줌 -> 250 ok 응답

	메세지들간을 구분하기 위해 보이진 않지만 메세지 끝에 아스키코드 제어문자인 <CF><LF>을 붙임

[ASCII는 MIME을 이용해서 변환됨](https://ko.wikipedia.org/wiki/MIME)

![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/SMTP%20/%20%EC%A0%84%EB%8B%AC%20%EA%B3%BC%EC%A0%95%20%EC%98%88.jpeg)

### 메세지 포켓

![500](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/SMTP%20/%20%EB%A9%94%EC%84%B8%EC%A7%80%20%ED%8F%AC%EC%BC%93.png)

### 명령어

![500](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/SMTP%20/%20%EB%AA%85%EB%A0%B9%EC%96%B4%20%EB%AA%A8%EC%9D%8C.png)
### 참고
https://blog.naver.com/eqelizer/20134840619
https://nordvpn.com/ko/blog/smtp-protocol/
James F. Kurose, Keith W. Ross '컴퓨터 네트워킹 하양식 접근 8판', 최종원 외 7인, 퍼스트북(2022) 
[컴퓨터 네트워크 제 9강 이메일과 SMTP](https://www.youtube.com/watch?v=maNnhEw4bzk)


### 추가
- SMTP vs HTTP
	- 둘 다 지속적 연결 상태
	- 둘 다 아스키 코드 기반, 상태 코드를 가짐
	- SMTP는 push로 클라이언트가 요청하지 않아도 서버가 메일 박스까지 정보를 전달하지만 
	   HTTP는 pull로 클라이언트가 요청해서 정보를 끌어옴
	- SMTP는 한 메세지 안에 여러 객체를 담지만
	   HTTP는 응답 메세지에 각 객체를 캡슐화 
	   
	==SMTP는 메일 서버에서 다른 메일 서버로 전자 메세지를 전송하고 HTTP는 웹 서버로 부터 브라우저로 파일이나 객체를 전송

- 그래서 왜 메일 서버간 통신에 HTTP를 안쓰는건지?
	- 위에서 설명했듯이 HTTP는 웹 서버로부터 브라우저로 객체를 전송하기 때문에 메일 서버간의 통신에서 사용할 수 없음 
	- 메일 서버 : gmail, naver 등은 각자의 메일 서버가 존재 
	   그래서 naver메일 주소 발송자가 메일을 보내면 이는 naver의 메일 서버로 이동하게 되고 naver메일 서버는 수신자의 도메인(gmail)을 확인하고 gmail 메일 서버로 SMTP를 이용해 메일을 전송해줌. 이로서 gmail메일 주소 수신자로 보낼 수 있음

---
**메일 전송에서 SMTP와 HTTP의 이용 차이를 완벽하게 이해하기 위해선 "이메일과 웹메일의 역사"를 알아야함**

- 전자 메일을 줄여 부르는 이메일은 전자 장치를 사용해 컴퓨터 네트워크를 거쳐 메세지를 전달하는 커뮤니케이션 방식. 즉, 위에 메일 전송 과정에서의 user agent는 이메일 클라이언트 소프트웨어(ex. Outlook)이 됨
- 웹메일은 웹 기반 이메일로 웹 브라우저를 사용해 엑세스 할 수 있는 이메일 서비스를 말함. 웹메일은 user agent가 웹 브라우저가 됨(ex. gmail)

	1970년 이전에는 같은 컴퓨터를 사용하는 경우에만 다른 사용자에게 메세지를 남길 수 있었다. 이후 톰리슨이라는 사람이 ARPANET 시스템에 연결된 서로 다른 컴퓨터간에 메세지를 보낼 수 있는 프로그램을 만들었는데, 다른 컴퓨터의 사용자를 구별하기 위해 현재까지 사용하는 @(at을 따서 만든거라고...)를 이용하였다. 이것이 이메일의 시작이고 1982년에 메일 서버에서 메세지를 주고 받는 방식을 표준화하기 위해서 SMTP가 도입되었다. 여기까지는 메일을 보내기 위해선 특정 소프트웨어 프로그램을 다운받아 사용했어야 했다. 그러다 1990년대 중반, 인터넷 연결을 통해 모든 컴퓨터에서 이메일에 액세스하는 아이디어가 주목을 받기 시작하였고 ISP는 웹메일 옵션을 서비스에 번들로 제공하기 시작하였다. 이후 현대에선 소프트웨어에서도, 웹 브라우저에서도 이메일을 보낼 수 있게 된 것이다.

	또한 현대에는 이메일의 의미가 전자메일과 웹메일 모두 포함되서 말하게 되었다

> ==정리하자면, "이메일"은 메일 소프트웨어(ex. outlook)에서 보내는 메일로 기본적인 메일 서버의 동작 구조로 작동하고, "웹메일"은 웹 브라우저에서 메일을 주고 받을 수 있게 만든 것으로 수신자가 메일을 보내고 받을때 HTTP를 사용하게 됨.

![](https://blog.kakaocdn.net/dn/bA2768/btru3Mli0mK/0kdxzhFmKQRf2UFBWXItzk/img.png)
	이메일의 동작 구조이고 웹메일(naver, gmail) 경우에는 메일 서버와의 통신 이외에는 HTTP를 사용한다

*사족으로 당연하지만 이메일로 메일을 받았다면 기기 자체에 다운이 된 것으로 오프라인 상태에서도 메일을 확인할 수 있지만, 웹메일 셧다운되면 메일 확인을 못함. 그 대신 웹 브라우저를 이용한다면 언제 어디서든 메일을 확인 할 수 있다는 장점이 있음.*

---
- gmail도 smtp 쓰나?
	위 설명을 바탕으로 알 수 있는데, gmail을 브라우저로 열어서 메일을 확인한다면 HTTP를 사용할 것이고, 따로 소프트웨어 프로그램 또는 웹 응용 프로그램인 outlook이나 gmail앱을 이용한다면 SMTP를 사용함.
	
---
- smtp로 첨부파일 어떻게 보내는지?
	8비트 이상의 코드를 사용하는 문자나 이진 파일들은 MIME(Multipurpose Internet Mail Extensions)포맷으로 변환되어 SMTP로 전송됨
	영어가 아닌 문자나 미디어 등의 첨부파일들이 해당

### 추가 참고
[메일 서버란?](https://www.cloudflare.com/ko-kr/learning/email-security/what-is-a-mail-server/)
[이메일(전자 메일) 이란?](https://www.cloudflare.com/ko-kr/learning/email-security/what-is-email/)
[웹메일](https://en.wikipedia.org/wiki/Webmail)
[이메일 발송 원리](https://it-eldorado.tistory.com/178)
[이메일의 역사](https://www.usebouncer.com/ko/%EC%9D%B4%EB%A9%94%EC%9D%BC%EC%9D%98-%EC%97%AD%EC%82%AC/)

