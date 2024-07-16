csma/Collision Detection
- 데이터를 전송하다 collision이 발생하면 멈춘 이후에 랜덤한 시간 이후에 다시 보내기 시작함.
	- 기본적으로 {0,1,...2^n-1} 중 하나의 수 x 전송매채에서 512 비트를 보내는데 걸리는 시간 (랜덤 백오프)

- 유선 이더넷 LAN 에서 사용. (유선링크의 경우 충돌을 확인할 수 있기 때문에)

#### 동작 원리
- 매체가 비어 있으면 노드에서 바로 전송 시작
- 만약 충돌을 발견했을 경우 랜덤 백오프 시간동안 기다렸다가 전송

![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/CSMA-CD%20/%20images-inyong_pang-post-5ee92b7b-a5bf-4383-a19a-bf4afc5b6b83-image%201.png)
