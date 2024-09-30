### 문제 설명
- VPC의 서브넷에서 기존에 실행 중인 EC2 인스턴스가 인터넷을 통해 클라이언트와 통신해야한다.
### 해결 방안
- 인터넷 게이트웨이를 생성해 VPC에 연결한다. EC2 인스턴스의 서브넷에서 인터넷 게이트웨이로 트래픽을 보내는 경로를 추가한다. 마지막으로 그림과 같이 탄력적 IP 주소를 생성해 인스턴스와 연결한다.
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/%EC%9D%B8%ED%84%B0%EB%84%B7%20%EA%B2%8C%EC%9D%B4%ED%8A%B8%EC%9B%A8%EC%9D%B4%EB%A5%BC%20%EC%82%AC%EC%9A%A9%ED%95%B4%20VPC%EB%A5%BC%20%EC%9D%B8%ED%84%B0%EB%84%B7%EC%97%90%20%EC%97%B0%EA%B2%B0%20/%20Pasted%20image%2020240629192635.png)
**인터넷 게이트웨이가 필요한 이유**
- 라우터와 라우팅 테이블을 통해 데이터는 라우터로 향하게 되며 네트워크 요청은 각각 정의된 라우팅 테이블에 따라 작동.
- 이때 라우팅 테이블은 VPC 안의 네트워크 범위를 갖는 네트워크 요청은 로컬에서 찾음
- 하지만 네트워크 범위 외에 외부로 통하는 트래픽은 처리할 수 없기에 인터넷 게이트웨이 사용

**인터넷게이트웨이**
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/%EC%9D%B8%ED%84%B0%EB%84%B7%20%EA%B2%8C%EC%9D%B4%ED%8A%B8%EC%9B%A8%EC%9D%B4%EB%A5%BC%20%EC%82%AC%EC%9A%A9%ED%95%B4%20VPC%EB%A5%BC%20%EC%9D%B8%ED%84%B0%EB%84%B7%EC%97%90%20%EC%97%B0%EA%B2%B0%20/%20Pasted%20image%2020240629193607.png)
- VPC와 인터넷을 연결해주는 하나의 관문
- 서브넷 B의 라우팅테이블에서 0.0.0.0/0으로 정의되어 있으며, 이는 모든 트래픽에 대하여 IGA(인터넷게이트웨이) A로 향한다는 뜻
- 라우팅 테이블은 가장 먼저 목적지의 주소가 172.31.0.0/16에 매칭되는지를 확인한 후 매칭되지 않는다면 IGA A로 보냄
- 인터넷과 연결 된 서브넷을 퍼블릭 서브넷, 인터넷과 연결 되지 않은 서브넷을 프라이빗 서브넷이라고 칭함

1. **인터넷 게이트웨이를 생성한다.
```
INET_GATEWAY_ID=$(aws ec2 create-internet-gateway \
--tag-specifications \
'ResourceType=internet-gateway,Tags=[{Key=Name,Value=AWSCookbook202}]' \
--output text --query InternetGateway.InternetGatewayId)
```
- `INET_GATEWAY_ID=$(...)`: 명령의 출력을 `INET_GATEWAY_ID` 변수에 저장
- `aws ec2 create-internet-gateway`: 새로운 인터넷 게이트웨이를 생성하는 AWS CLI 명령
- `--tag-specifications 'ResourceType=internet-gateway,Tags=[{Key=Name,Value=AWSCookbook202}]'`: 생성된 인터넷 게이트웨이에 태그를 지정, `Key`는 `Name`, `Value`는 `AWSCookbook202`
- `--output text`: 출력 형식을 텍스트로 지정
- `--query InternetGateway.InternetGatewayId`: 출력에서 인터넷 게이트웨이 ID만 추출

2. **인터넷 게이트웨이를 가진 기존 VPC에 연결한다
```
aws ec2 attach-internet-gateway \
--internet-gateway-id $INET_GATEWAY_ID --vpc-id $VPC_ID
```
- `aws ec2 attach-internet-gateway`: 인터넷 게이트웨이를 VPC에 연결
- `--internet-gateway-id $INET_GATEWAY_ID`: 이전에 생성한 인터넷 게이트웨이의 ID를 지정, 변수 `$INET_GATEWAY_ID`에 저장된 값
- `--vpc-id $VPC_ID`: 인터넷 게이트웨이를 연결할 VPC의 ID를 지정

3. **VPC의 각 라우팅 테이블에서 기본 경로 대상을 인터넷 게이트웨이로 설정하는 경로를 생성한다
```
aws ec2 create-route --route-table-id $ROUTE_TABLE_ID_1 \
--destination-cidr-block 0.0.0.0/0 --gateway-id $INET_GATEWAY_ID
aws ec2 create-route --route-table-id $ROUTE_TABLE_ID_2 \ --destination-cidr-block 0.0.0.0/0 --gateway-id $INET_GATEWAY_ID
```
- `aws ec2 create-route`: 새로운 라우트를 생성
- `--route-table-id $ROUTE_TABLE_ID_1`: 첫 번째 라우트 테이블의 ID를 지정, 변수 `$ROUTE_TABLE_ID_1`에 저장된 값
- `--destination-cidr-block 0.0.0.0/0`: 기본 경로를 지정하여 모든 트래픽을 라우트
- `--gateway-id $INET_GATEWAY_ID`: 인터넷 게이트웨이의 ID를 지정, 변수 `$INET_GATEWAY_ID`에 저장된 값
4. **EIP(탄력적 ip 주소)를 생성한다
```
ALLOCATION_ID=$(aws ec2 allocate-address --domain vpc \
--output text --query AllocationId)
```
- `ALLOCATION_ID=$(...)`: 명령의 출력을 `ALLOCATION_ID` 변수에 저장
- `aws ec2 allocate-address`: 새로운 탄력적 IP 주소를 할당
- `--domain vpc`: 탄력적 IP 주소를 VPC에 할당하도록 지정
- `--output text`: 출력 형식을 텍스트로 지정
- `--query AllocationId`: 출력에서 탄력적 IP 주소의 할당 ID만 추출

5. **EIP를 기존 EC2 인스턴스와 연결한다
```
aws ec2 associate-address \
--instance-id $INSTANCE_ID --allocation-id $ALLOCATION_ID
```
- `aws ec2 associate-address`: 탄력적 IP 주소를 인스턴스에 연결
- `--instance-id $INSTANCE_ID`: 탄력적 IP 주소를 연결할 인스턴스의 ID를 지정
- `--allocation-id $ALLOCATION_ID`: 탄력적 IP 주소의 할당 ID를 지정