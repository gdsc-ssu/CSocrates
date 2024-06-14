

- aws를 사용하기 위해서 알아야할 정보들
- 제일 처음 aws를 사용하기 위해서 이해해야 되는 개념들이다.

![[스크린샷 2024-06-10 11.10.08.png]]

## VPC (Virtual Private Cloud)

- 직역하면 가상 사설 클라우드, 사용자가 만든 가상 네트워크.
- vpc는 하나의 리전에 생성할 수 있으며 여러 가용 영역 사용 가능.
- 각 가용영역에는 서브넷이 있고 서브넷에서 aws 리소스(ec2 등)를 사용할 수 있음.
- VPC를 사용하게 되면 논리적으로 격리된 가상 네트워크에서 AWS를 사용할 수 있다.

### 리전 (Region)

- aws에서 지리적 관점으로 영역을 구분하는 것을 리전이라고 한다.
    - 전세계적으로 33개의 리전이 존재.
    - 우리나라의 경우에는 “서울 리전”이 존재한다.
- 이렇게 물리적으로 호스팅 영역을 구분해놓았기 때문에, aws 사용자는 서비스 될 국가와 가장 가까운 리전을 선택하여 빠른 속도를 낼 수 있다.
    - 각 리전은 서로 완전히 독립적이다, 미국 버지니아 리전에 ec2를 만들어도, 서울 리전에서는 뜨지 않는다.

### 가용 영역 (Availability Zone)

- 리전에서 가용 영역이라는 더 작은 단위로 분리된다.
- aws 리전은 최소 2개 이상의 가용영역으로 구성되며, 각 가용 영역은 최소 1개 이상의 데이터 센터로 구성.
    - 전세계 105개의 가용영역 존재
    - 한국에서 총 4개의 가용영역이 존재
- 각각의 가용 영역은 같은 리전임에도 불구하고 지리적으로 멀리 떨어져있다.
    - 천재지변등의 물리적인 사고 발생 시 피해를 최소화하기 위해서

## 참고

VPC을 생성할 때 ClDR 블록을 신중하거| 선택해야 할 두 가지 이유가 있다.

1. CIDR블록을 한번 VPC와 연결하면 확장할 수는 있지만 수정할 수 없다. CIDR블록을 수정하려면 블록 및 그 안의 모든 리소스를 삭제하고 다시 만들어야 한다.
2. VPC를 피어링 또는 게이트웨이를 통해 다른 네트워크에 연결하는 경우 IP 범위가 겹치먼 문제가 발생할 수 있다.

## 실습

```bash
# vpc 생성
VPC_ID=$(aws ec2 create-vpc --cidr-block 10.10.0.0/16 \
    --tag-specifications 'ResourceType=vpc,Tags=[{Key=Name,Value=AWSCookbook201}]' \
    --output text --query Vpc.VpcId)

# 생성한 vpc 확인
aws ec2 describe-vpcs --vpc-ids $VPC_ID
```

![[스크린샷 2024-06-14 오후 6.25.04.png]]


## Reference

[[AWS] 가장쉽게 VPC 개념잡기](https://medium.com/harrythegreat/aws-%EA%B0%80%EC%9E%A5%EC%89%BD%EA%B2%8C-vpc-%EA%B0%9C%EB%85%90%EC%9E%A1%EA%B8%B0-71eef95a7098)

[온라인 AWS 아키텍처 다이어그램 도구](https://online.visual-paradigm.com/ko/diagrams/features/aws-architecture-diagram-tool/)