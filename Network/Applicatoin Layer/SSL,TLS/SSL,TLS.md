## 개요
- [[#SSL(Secure Sockets Layer)]] 
- [[#TLS(Transport Layer Security)]]
- [[#왜 SSL을 사용해야 하는가?]]
- [[암호화 기법]]
- [[#SSL 인증서]]
- [[#SSL Handshake]]

### SSL(Secure Sockets Layer)
- ssl이란 "웹사이트의 ID를 인증하고 암호화된 연결을 생성하는 인터넷 보안 프로토콜"
- Netscape는 개발된 프로토콜로 SSL 1.0은 1995년 개발
	-> 하지만 1.0의 경우 많은 이슈가 있어 공개되지 않았고, 1996년에 2.0부터 공개되기 시작
- **개인정보 보호, 인증, 데이터 무결성을 보장**
- 클라이언트와 웹 서버 사이에서 동작

### TLS(Transport Layer Security)
- SSL과 거의 동일한 프로토콜
- 특정 회사(Netscape)에 의해 개발된 SSL을 인터넷 표준화 기구인 IETF (Internet Engineering Task Force)에서 표준화
- SSL 3.0 버전을 기반으로 TLS 1.0을 발표


- 윈도우에서 지원되는 SSL과 TLS
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/SSL%2CTLS%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202023-01-06%20%EC%98%A4%ED%9B%84%206.47.29.png)

> 현재는 모든 SSL은 지원하지 않고, TLS만 사용한다.

### 왜 SSL을 사용해야 하는가?
- ssl같은 보안을 적용하지 않고 그냥 데이터를 주고 받는다면 제 3자가 데이터를 쉽게 탈취할 수 있다.
#### SSL이 적용되지 않은 경우
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/SSL%2CTLS%20/%20plainText.png)
- ssl이 적용되지 않으면 위 그림에서 처럼 "High Value Information"라는 문자열이 그대로 전송
- 제 3자가 데이터를 탈취하기 쉽다.

#### SSL 적용된 경우
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/SSL%2CTLS%20/%20Pasted%20image%2020231229115752.png)
- ssl이 적용된 경우에는 데이터가 암호화되어서 보내진다.
- 제 3자가 탈취한다 해도 복호화하기 힘들기 때문에 상대적으로 안전해진다.

### 암호화 방식
- 사용하는 암호화 방식은 대칭키와 비대칭키를 혼합해서 사용한다.

### SSL 인증서
- SSL 인증서는 클라이언트와 서버간의 통신을 제3자가 보증해주는 전자화된 문서
- 보통 CA라고 불리는 공인된 기관에서 유료로 발급
- 인증서 내용
	1. 서비스의 정보 (인증서를 발급한 CA, 서비스의 도메인 등)
	2. 서버 측 공개키 (공개키의 내용, 공개키의 암호화 방법)

#### CA
- CA(Certificate authority) 혹은 Root Certificate 라고도 불림
- 민간기업 중 엄격한 심사를 통해서 선정된 SSL 인증서 발급 기업
- 이 CA는 기본적으로 브라우저에 내장되어 있다.
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/SSL%2CTLS%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202023-12-29%20%EC%98%A4%ED%9B%84%203.26.42.png)
 
- 맥의 경우 키체인에서 CA 인증서들을 확인할 수 있다.
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/SSL%2CTLS%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202023-12-29%20%EC%98%A4%ED%9B%84%203.25.04.png)

### SSL 인증서가 서비스를 보증하는 방법
1. 웹 브라우저가 서버에 접속할 때 서버는 제일 먼저 인증서를 제공
2. 브라우저는 이 인증서를 발급한 CA가 자신이 내장한 CA의 리스트에 있는지를 확인
3. 확인 결과 서버를 통해서 다운받은 인증서가 내장된 CA 리스트에 포함되어 있다면 해당 CA의 공개키를 이용해서 인증서를 복호화
=> 인증서를 복호화 할 수 있다는 것은 이 인증서가 CA의 비공개키에 의해서 암호화 된 것을 의미
=> 즉 안전하다.

### SSL Handshake
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/SSL%2CTLS%20/%20Pasted%20image%2020231229160000.png)
- 파란 부분은 tcp handshake
- 노란 부분이 ssl handshake

1. ClientHello
   - client측에서 서버에 연결을 요청한다. (인사?)
   - session id, ssl protocol version, [cipher suite](https://ko.wikipedia.org/wiki/%EC%95%94%ED%98%B8%ED%99%94_%EC%8A%A4%EC%9C%84%ED%8A%B8) 목록 등의 정보를 담아서 전송
2. ServerHello & Certificate, ServerHelloDone
   ServerHello
   - 1번에서 클라이언트에서 받은 인사(Client Hello 패킷)에 대해 서버가 응답
   - ssl protocol version, client suite중 하나 선택해서 응답
   Certificate, ServerHelloDone
   - Server 의 SSL 인증서 내용을 클라이언트에게 전송
3. client 에서 server 의 SSL 인증서 검증
   - 서버에서 받은 인증서 정보를 가지고 유효한 인증서인지 검증한다.
4. Client Key Exchange
   - 서버의 인증서 검증을 마친 후, 클라이언트는 서버와 통신하기 위한 대칭키를 생성한다.
   - 이 생성한 대칭키를 서버의 공개키를 사용해서 암호화 해서 서버에게 전송한다.
5. Server / Client SSL Handshake Finished
   - 서버가 암호화된 대칭키를 받아서 복호화에 성공하면 연결이 끝난다.




### 기타
#### 무료 인증서 발급 사이트 목록
**1. Let’s Encrypt** : https://letsencrypt.org/
**2. Comodo Free SSL** : https://www.gogetssl.com/domain-validation/comodo-free-ssl/
**3. CloudFlare One-Click SSL** : https://www.cloudflare.com/ssl/
**4. AWS Certificate Manager** : https://aws.amazon.com/ko/certificate-manager/


### Reference
https://hstory0208.tistory.com/entry/SSL-%EC%9D%B4%EB%9E%80-TLS-%EC%9D%B4%EB%9E%80
https://captcha.tistory.com/51
https://support.cafe24.com/hc/ko/articles/8469947344409-SSL%EC%9D%B4%EB%9E%80-%EB%AC%B4%EC%97%87%EC%9D%B8%EA%B0%80%EC%9A%94-
https://velog.io/@yjw8459/%EC%9B%B9-%EC%82%AC%EC%9D%B4%ED%8A%B8-%EB%B3%B4%EC%95%88-SSL%EC%9D%B4%EB%9E%80
https://12bme.tistory.com/80
https://arc.net/l/quote/gqzfvkyb
