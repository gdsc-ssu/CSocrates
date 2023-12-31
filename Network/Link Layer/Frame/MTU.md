Maximum Transmission Unit

DIX Ethernet에서는 1500 byte, 802.3 Ethernet에서는 1492 byte, ...

OSI 7 Layer에서 볼 때 데이터링크 계층에서는 자신이 속한 네트워크에 대한 MTU 값을 알아야 하며, 상위 프로토콜들에게 그 값을 알려주어야 한다.

MTU보다 높게 전송했을 때는 단편화가 일어난다.

왜 알려주어야 할까?
* MTU에 맞게 데이터를 조각내서 전송하면 오버헤드를 줄일 수 있고, 전송 시간을 최소화 할 수 있다. 
* 오류가 발생했을 때 손실되는 데이터 양을 최소화 할 수 있음. 
* 상위 계층과의 호환성 때문. 예를 들어 TCP 프로토콜은 MTU를 고려해서 데이터를 분할하고 재조립한다.
* 적절한 크기의 MTU는 네트워크의 성능을 최적화하는 데 중요하다.

