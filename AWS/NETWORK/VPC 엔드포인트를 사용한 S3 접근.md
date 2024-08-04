>[!info] 목차
> - [[#문제 설명]]
> - [[#문제 추가 설명]]
> - [[#해결 방법]]
> - [[#참고]]
> - [[#참고 레퍼런스]]
### 문제 설명
VPC 내 리소스 대역폭 비용을 낮게 유지하면서 보안을 위해 외부 인터넷을 사용하지 않고, 특정 S3 버킷에 접근해야한다.
### 문제 추가 설명
- 보안
	- 외부 인터넷을 사용하지 않고 s3 버킷에 접근할 수 있어야 함
	- private subnet에 있는 인스턴스에서 s3 버킷에 접근하려면 일반적인 경우, endpoint를 실제 s3의 엔드포인트로 설정하여 받아오게 되는데, private subnet이면 외부 인터넷 연결이 안되기 때문에 public subnet으로 바꿔줘야 접근할 수 있다.
- 비용
	- vpc 내 리소스에서 internet gateway를 사용하지 않고 s3 버킷으로 데이터 전송
	- vpc에서 s3 버킷에 접근할 때 트래픽은 internet gateway를 통과하게 되고, 다시 돌아오는 과정도 포함함 -> 외부 인터넷을 경유하게 됨으로 인터넷 데이터 비용 발생

### 해결 방법
VPC 엔드포인트를 활용하여 private subnet에 있는 인스턴스에서 private s3 버킷 혹은 public s3 버킷으로 접근할 수 있다.
> ![[Pasted image 20240804154437.png]]
> ![[Pasted image 20240804154502.png]]
> 출처 : 농심 tech 블로그

Gateway endpoint를 설정하면 routing table에 pl-id (prefix list id / 접두사 목록)가 생성되고, 해당 s3 endpoint는 vpc endpoint를 활용하여 접근하게 된다.
### 참고
- VPC 엔드포인트 자체는 무료이고, 관련된 서비스를 이용하는 이용료만 발생한다.
- S3 버킷에 대한 엑세스 제한을 위해서 엔드포인트 정책을 사용할 수 있는데, 계정이 소유한 버킷 뿐만 아니라 AWS 내 모든 S3 버킷에 대해서 적용이 가능하다.
```json
{
  "Version": "2012-10-17",
  "Statement": [
    {
      "Effect": "Allow",
      "Principal": "*",
      "Action": "s3:GetObject",
      "Resource": "arn:aws:s3:::your-bucket-name/*",
      "Condition": {
        "StringEquals": {
          "aws:sourceVpce": "vpce-xxxxxxxx"
        }
      }
    }
  ]
}
```
이렇게 만들면 해당 vpc에서만 버킷 접근이 가능하다.
- VPC 엔드포인트의 라우팅 테이블 항목이 기본 0.0.0.0/0 보다 구체적으로 설정되어 있음으로(pl-id값이 설정되어 있음으로), 해당 서비스로 바인딩 된 모든 트래픽은 public 인터넷 경로가 아니라 vpc 엔드포인트로 이동한다.

### 참고 레퍼런스
- [vpc endpoint란?](https://tech.cloud.nongshim.co.kr/2023/03/16/%EC%86%8C%EA%B0%9C-vpc-endpoint%EB%9E%80/)
- 
