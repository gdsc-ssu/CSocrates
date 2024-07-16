
# OSI 7 Layer

국제 표준화 기구 (ISO), 국제 전신 자문 위원회 (International Telegraph and Telephone Consultative Committee)에 의해 따로 관리되고 있던 네트워킹 모델 정의 문서가 1983년에 병합됨.

Open Systems Interconnection

- Open System이란?
	- 어떠한 boundary를 기준으로 Surroundings에 대한 input과 output을 모두 제공하는 시스템.
		- 쉽게 말해, 외부에서의 입력과 출력이 자유롭게 이루어지는 시스템
	- Isolated System : input과 output을 제공하지 않는 시스템
	- Closed System : input과 output을 제한적으로 제공하는 시스템

https://standards.iso.org/ittf/PubliclyAvailableStandards/s020269_ISO_IEC_7498-1_1994(E).zip

위 문서는 1994년 출간된 7498-1 개정판. (7498-1은 파트 1을 의미하며, 파트 1은 The Basic Model, 파트 2는 Security Architecture, 파트 3은 Naming and addressing, 파트 4는 Management framework 라는 이름을 갖고 있다.)
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/OSI%207%20Layer%2C%20TCP%20IP%20Model%20/%20OSI7Layer.png)
(해당 문서에서 캡쳐한 OSI 7 Layer)

여담 : 문서가 생각보다 매우매우 복잡하다. 시스템간 OSI 7 레이어를 전부 정의해뒀는데 어지럽다. 위 그림은 문서 중반에 처음 등장한다.. 위에는 계층을 나눌 필요성에 대해 설명하고, 그 다음엔 어떤 레이어가 있는지 상세하게 설명한다.

### OSI 7 Layer의 목적 
프로토콜을 기능별로 나눈 것이다. 계층을 미리 정의하고 프로토콜을 알맞게 생성한 것이 아니라, 프로토콜을 분류하기 위해서 계층을 나눈 것이다. (그래서 대부분의 프로토콜이 계층에 알맞게 들어가 있다.)

사진을 보면 알겠지만, 프로토콜간 통신을 계층별로 나눠서 진행하겠다는 의지가 가득 담겨있다.

### 각 레이어는 뭘 할까? (ISO 7498-1)
- Application Layer
	- As the highest layer in the Reference Model of Open Systems Interconnection, the Application Layer provides the sole means for the application process to access the OSIE. Hence the Application Layer has no boundary with a higher layer.
	- 개방 시스템 상호 연결 참조 모델에서 최상위 계층인 응용 계층은 응용 프로세스가 OSI에 액세스하는 유일한 수단을 제공합니다. 따라서 응용 계층은 더 높은 계층과의 경계가 없습니다.
- Presentation Layer
	- The Presentation Layer provides for the representation of information that application-entities either communicate or refer to in their communication.
	- 프레젠테이션 계층은 응용 엔티티들이 통신하거나 그들의 통신에서 참조하는 정보의 표현을 제공합니다.
- Session Layer
	- The purpose of the Session Layer is to provide the means necessary for cooperating presentation-entities to organize and to synchronize their dialogue and to manage their data exchange. To do this, the Session Layer provides services to establish a session-connection between two presentation-entities, to support orderly data exchange interactions, and to release the connection in an orderly manner.
	- 세션 계층의 목적은 협력하는 프레젠테이션 엔티티가 대화를 조직화하고 동기화하며 데이터 교환을 관리하는 데 필요한 수단을 제공하는 것입니다. 이를 위해 세션 계층은 두 프레젠테이션 엔티티 간의 세션 연결을 설정하고 데이터 교환 상호작용을 지원하며 orderly한 방식으로 연결을 해제하는 서비스를 제공합니다.
- Transport Layer
	- The transport service provides transparent transfer of data between session-entities and relieves them from any concern with the detailed way in which reliable and cost-effective transfer of data is achieved.
	- 전송 서비스는 세션 엔티티 간의 데이터를 투명하게 전송하고, 데이터의 신뢰성과 비용 효율적 전송이 어떤 방식으로 이루어지는지에 대한 걱정을 덜어줍니다.
- Network Layer
	- The Network Layer provides the functional and procedural means for connectionless-mode or connection-mode transmission among transport-entities and, therefore, provides to the transport-entities independence of routing and relay considerations.
	- 네트워크 계층은 전송 엔티티 간의 연결 지향 혹은 비연결 지향 전송을 위한 기능적 및 절차적 수단을 제공하며, 따라서 전송 엔티티에게 경로 설정 및 중계 고려 사항에서 독립성을 제공합니다.
- Data Link Layer
	- The Data Link Layer provides functional and procedural means for connectionless-mode among network-entities, and for connection-mode for the establishment, maintenance, and release of data-link-connections among network-entities and for the transfer of data-link-service-data-units. A data-link-connection is built upon one or several physical-connections.
	- 데이터 링크 계층은 네트워크 엔티티 간의 비연결 지향 모드 및 연결 지향 모드를 위한 기능적 및 절차적 수단을 제공하며, 네트워크 엔티티 간의 데이터 링크 연결 설정, 유지 및 해제 및 데이터 링크 서비스 데이터 유닛의 전송을 위한 것입니다. 데이터 링크 연결은 하나 이상의 물리적 연결에 기반을 둡니다.
- Physical Layer
	- The Physical Layer provides the mechanical, electrical, functional, and procedural means to activate, maintain, and deactivate physical-connections for bit transmission between data-link-entities. A physical-connection may involve intermediate open systems, each relaying bit transmission within the Physical Layer. Physical Layer entities are interconnected by means of a physical medium.
	- 물리 계층은 데이터 링크 엔티티 간의 비트 전송을 위해 물리적 연결을 활성화, 유지 및 비활성화하기 위한 기계적, 전기적, 기능적 및 절차적 수단을 제공합니다. 물리적 연결은 중간 개방 시스템을 포함할 수 있으며, 각각이 물리 계층 내에서 비트 전송을 중계할 수 있습니다. 물리 계층 엔티티들은 물리적 매체를 통해 연결됩니다.

# TCP/IP Model (4,5계층)
인터넷 프로토콜 스위트(슈트) : Internet Protocol Suite는 인터넷에서 컴퓨터들이 서로 정보를 주고받는 데 쓰이는 프로토콜의 모음. 이 중 TCP와 IP가 가장 많이 쓰이기 때문에 TCP/IP 프로토콜 슈트라고 불린다.

ARPANET을 개발했던 미국 방위고등연구계획국이 만들었다. 1960년대 말에 연구되었고, RFC1122번으로 등재된 것은 1989년이다. 참고로 1969년에는 아폴로 11호가 달 착륙에 성공했다. (진짜 어케했누?)

위키 : The Internet protocol suite predates the [OSI model](https://en.wikipedia.org/wiki/OSI_model "OSI model"), a more comprehensive reference framework for general networking systems.
번역 : OSI model보다 먼저 나왔다.
그래서 OSI 7 Layer에 비해 TCP/IP가 산업에서 훨씬 더 많이 사용된다.

![](https://upload.wikimedia.org/wikipedia/commons/d/d7/Application_Layer.png)


![](https://upload.wikimedia.org/wikipedia/commons/thumb/c/c4/IP_stack_connections.svg/350px-IP_stack_connections.svg.png)

https://datatracker.ietf.org/doc/html/rfc1122#page-8
위 문서에 4개의 레이어에 대한 설명이 있다. (rfc 1122)

### 각 레이어는 뭘 할까? (rfc1122)

- Application Layer
	- The application layer is the top layer of the Internet protocol suite. The Internet suite does not further subdivide the application layer, although some of the Internet application layer protocols do contain some internal sub-layering. The application layer of the Internet suite essentially combines the functions of the top two layers—Presentation and Application—of the OSI reference model.
	- 응용 계층은 인터넷 프로토콜 스위트의 최상위 계층입니다. 인터넷 스위트는 응용 계층을 더 이상 세분화하지 않지만, 일부 인터넷 응용 계층 프로토콜에는 내부 하위 계층이 포함되어 있습니다. 인터넷 스위트의 응용 계층은 본질적으로 OSI 참조 모델의 상위 두 계층인 프레젠테이션과 응용 계층의 기능을 결합합니다.
- Transport Layer
	- The transport layer provides end-to-end communication services for applications. There are two primary transport layer protocols at present:
	- 전송 계층은 애플리케이션을 위한 종단간 통신 서비스를 제공합니다. 현재 주로 사용되는 두 가지 전송 계층 프로토콜은 다음과 같습니다:
		- Transmission Control Protocol (TCP)
		- User Datagram Protocol (UDP)
	- TCP is a reliable connection-oriented transport service that provides end-to-end reliability, resequencing, and flow control. UDP is a connectionless ('datagram') transport service.
	- TCP는 종단간 신뢰성, 재순서화 및 흐름 제어를 제공하는 신뢰성 있는 연결 지향 전송 서비스입니다. UDP는 비연결형('데이터그램') 전송 서비스입니다.
- Internet Layer
	- All Internet transport protocols use the Internet Protocol (IP) to carry data from the source host to the destination host. IP is a connectionless or datagram internetwork service, providing no end-to-end delivery guarantees. Thus, IP datagrams may arrive at the destination host damaged, duplicated, out of order, or not at all. The layers above IP are responsible for a reliable delivery service when it is required. The IP protocol includes provisions for addressing, type-of-service specification, fragmentation and reassembly, and security information.
	- 모든 인터넷 전송 프로토콜은 데이터를 소스 호스트에서 목적지 호스트로 전달하기 위해 인터넷 프로토콜 (IP)을 사용합니다. IP는 연결 없이 또는 데이터그램 형태의 인터네트워크 서비스로, 종단간 전송 보장을 제공하지 않습니다. 따라서 IP 데이터그램은 목적지 호스트에 손상되거나 중복되거나 순서가 뒤바뀌거나 아예 도착하지 않을 수 있습니다. IP 위의 계층은 필요한 경우 신뢰할 수 있는 전송 서비스를 담당합니다. IP 프로토콜에는 주소 지정, 서비스 유형 지정, 단편화 및 재조립, 그리고 보안 정보가 포함되어 있습니다.
- Link Layer
	- To communicate on its directly connected network, a host must implement the communication protocol used to interface with that network. We call this a link layer or media access layer protocol.
	- 직접 연결된 네트워크에서 통신하려면 호스트는 해당 네트워크와 인터페이스하는 통신 프로토콜을 구현해야 합니다. 이를 링크 계층 또는 미디어 접근 계층 프로토콜이라고 합니다.


# OSI 7 Layer과 TCP/IP Model은 뭐가 다를까?

|Arpanet Reference Model(RFC 871)|Internet Standard(RFC 1122)|Internet model(Cisco Academy)|TCP/IP 5-layer reference model(Kozierok, Comer)|TCP/IP 5-layer reference model(Tanenbaum)|TCP/IP protocol suite or Five-layer Internet model(Forouzan, Kurose)|TCP/IP model(Stallings)|OSI model(ISO/IEC 7498-1:1994)|
|---|---|---|---|---|---|---|---|
|Three layers|Four layers|Four layers|Four+one layers|Five layers|Five layers|Five layers|Seven layers|
|Application/ Process|Application|Application|Application|Application|Application|Application|Application|
||||||||Presentation|
||||||||Session|
|Host-to-host|Transport|Transport|Transport|Transport|Transport|Host-to-host or transport|Transport|
||Internet|Internetwork|Internet|Internet|Network|Internet|Network|
|Network interface|Link|Network interface|Data link (Network interface)|Data link|Data link|Network access|Data link|
|—|—|—|(Hardware)|Physical|Physical|Physical|Physical|

현재 표준은? TCP/IP protocol suite or Five-layer Internet model(Forouzan, Kurose)
Application -> Transport -> Network -> Data link -> Physical

4계층 시절엔 Network 계층이 아니라 Internet 계층이었는데 다시 개명했음.
### **reference**
https://ko.wikipedia.org/wiki/OSI_%EB%AA%A8%ED%98%95
https://ko.wikipedia.org/wiki/%EC%9D%B8%ED%84%B0%EB%84%B7_%ED%94%84%EB%A1%9C%ED%86%A0%EC%BD%9C_%EC%8A%A4%EC%9C%84%ED%8A%B8