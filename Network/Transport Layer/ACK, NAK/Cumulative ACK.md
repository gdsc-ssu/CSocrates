### 의미
Cumulative : 누적하는

직역하자면 "누적 ACK"이다.
이전에 전송받은 프레임의 ACK를 전달받지 못하더라도, 새롭게 받은 ACK가 이를 포함한다면 이전 패킷의 처리가 정상적으로 되었다고 판단하는 것이다.
Go-Back-N 방식에서 사용된다.

### Reference
https://ws-pace.tistory.com/172