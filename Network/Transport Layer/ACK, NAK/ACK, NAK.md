### ACK
ACK란 Acknowledgement의 약자이다.
ACK는 데이터 수신측에서 패킷을 올바르게 받았다는 의미로, 다음으로 필요한 패킷의 번호 (받은 패킷의 번호 + 1)과 함께 보내진다.
ACK는 Packet Switching 방식에서 서비스 신뢰성에 도움을 주지만, 과도한 부하를 주게되어 망의 신뢰성이 높아질수록 사용하지 않는 경향이 있다. (단순한 수신 완료 처리를 위한 패킷으로 많은 네트워크를 유발하기 때문)

### NAK
NAK이란 Negative Acknowledgement의 약자이다.
받은 패킷에 오류가 있다거나, 다른 순서의 패킷을 받았다는 의미로, 문제가 있는 패킷 번호와 함께 보내진다.
주로 사용되지는 않는다.
왜냐하면 주로 Sender 쪽에서 Timer 혹은 순서 번호를 갖고 있어, 일정 시간이 지나도록 ACK가 오지 않으면 오류로 간주해서 해당 메시지를 재전송하도록 만들었기 때문이다.

### Reference
http://www.ktword.co.kr/test/view/view.php?m_temp1=774