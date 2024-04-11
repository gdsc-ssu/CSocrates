
### 출처
* [정책 시뮬레이터](https://policysim.aws.amazon.com/home/index.jsp?#roles/bunnies)
* AWS 입문
___
### 개요
* [[#IAM이란?]]
* [[#IAM으로 무엇을 할 수 있을까?]]
* [[#IAM으로 무엇을 할 수 있을까?]]
* [[#IAM이 생성하고 관리하는 것]]
* [[#실습하기]]
___
### IAM이란?

IAM은 AWS 내부에서 권한과 정책에 대한 관리를 하는 메뉴이다. 누가 어디서 무엇을 어떻게 할 수 있다를 정의하는 영역이라 할 수 있다. IAM은 특정한 유저와 정책 및 역할을 생성해 리소스를 보호한다. 확인해야할 특별한 점으로 IAM은 리전에 따라 구분되지 않고 유니버셜하게 관리된다는 점이 존재한다.
___
### IAM으로 무엇을 할 수 있을까?

**IAM의 목적은 서비스 운영을 위해 필요한 최소한의 권한만을 부여해 시스템의 안정성을 높이는 것이다**. 유저의 권한을 잘못 설정할 경우 이로 인해 재앙이 발생할 수도 있기 때문이다.

특정 기업에서 근무하는 상황을 가정해보자. 인프라, SRE, DEV OPS와 같이 아키텍쳐를 주로 다뤄야하는 팀들이 있을 것이고 배포와 운영보단 개발에 치중된 개발팀도 존재할 것이다. 이때 권한을 잘못 설정해 개발 팀이 마음대로 배포 로직이나 아키텍쳐 구조를 상의 없이 변경할 수 있다고 해보자.

이 경우 기존의 배포 로직을 무단으로 수정하고 배포를 하거나 기존 프로세스를 무시하고 개발 팀이 독단적으로 모든 것을 관리할 수 있게 된다. 백업 본 생성 없이 무단 배포, 특정 설정이나 이슈 무시하고 강제 배포.. 혹은 아키텍쳐를 상의도 없이 바꿀 수 있다면.. 슬렉에 얼마가지 않아 산이 쌓이는 것을 확인할 수 있다.

DB를 건들이는 것도 무섭다. 이런 상황도 생각해보자 (경험담이다)

사수: 이거 디비 기본 키 값이랑 트리거가 안 먹는데 체크 한번 해주세요 @DBA

DBA: 저흰 건드린 적이 없습니다. 로그 찍어보니 직접 수정 하셨는데요.

나: 제가 바꾼건데 권한 어디까지 되는지 궁금해서 한번 해봤습니다. (진짜임 SELECT만 되는 줄 알았음)

**세상에는 이상한 사람이 정말 많기 때문에 리소스의 안전한 보호와 운영을 위해선 최소 권한 정책은 선택이 아닌 필수이다.**
___
### IAM이 생성하고 관리하는 것

IAM은 접근 권한 설정을 유저, 그룹, 역할, 정책 총 4가지의 카테고리를 활용해 관리한다.

![[스크린샷 2024-04-11 오전 11.54.17.png|500]]
* **유저**: 엑세스 키와 비밀 키를 가지고 AWS 리소스를 사용하는 객체를 말한다.
* **그룹**: 하나 혹은 여러 유저를 저장하고 있으며 권한을 개개인이 아닌 유저 집단에 적용할 수 있다.
* **역할**: 역할은 하나 혹은 다수의 정책을 포함할 수 있으며 유저에게 할당하는 것이 가능하다.
* **정책**: 정책은 실질적으로 허용하는 행동들을 정의하는 곳이다. DB 읽기, DB 쓰기와 같이 유저에게 허용된 행동 들이 여기서 정의된다.
___
### 실습하기

IAM을 활용해 유저를 한번 만들어보자. 오늘 만들고 싶은 유저는 다음과 같다.
퍼블릭 읽기가 가능한 S3에 유일하게 파일 수정, 추가, 삭제 권한을 갖고 있다.

우선 유저를 만들어보자.  AWS-CLI를 활용해 진행한다.  

```bash
aws iam create-user --user-name newjeansfan
```

유저를 생성하고 나면 아래와 흡사한 형태의 응답이 돌아온다.
```bash
{
    "User": {
        "UserName": "newjeansfan", 
        "Path": "/",
        "CreateDate": "2023-06-08T03:20:41.270Z",
        "UserId": "AIDAIOSFODNN7EXAMPLE",
        "Arn": "arn:aws:iam::123456789012:user/newjeansfan" #자원 식별 아이디
    }
}
```

이제 퍼블릭 읽기만 가능한 S3를 생성해보자.
```bash
aws s3 mb s3://newjeans-image
```

퍼블릭 엑세스 허용을 위해 차단 권한을 전부 제거하자.
```bash
aws s3api put-public-access-block --bucket newjeans-image --public-access-block-configuration "BlockPublicAcls=false,IgnorePublicAcls=false,BlockPublicPolicy=false,RestrictPublicBuckets=false"
```

파일을 하나 업로드하고 확인해보자.
```bash
aws s3 cp ~/Downloads/test.gif s3://newjeans-image/newjeans
```

뉴진스가 잘 나올듯 하지만.. 어라? 뉴진스가 잘 나올지 않는다. 이는 일반 유저 들에게 버킷 접근 권한을 할당해주지 않았기 때문에 발생하는 일로 버킷에 모든이가 접근 가능케 하는 권한을 부여해주면 된다.

```json
{
	"Version": "2012-10-17",
	"Statement": [
		{
			"Sid": "id-1",
			"Action": ["s3:GetObject"], #파일접근
			"Effect": "Allow",
			"Resource": "arn:aws:s3:::newjeans-image/*",
			"Principal": "*" #허용대상
		}
	]
}

```

``` bash
vi policy.json
#버킷에 정책 부여
aws s3api put-bucket-policy --bucket newjeans-image --policy file://policy.json

```

버킷에 정책까지 할당 해주면 이젠 뉴진스가 잘 보인다 야호!
![뉴진스](https://newjeans-image.s3.ap-northeast-2.amazonaws.com/newjeans)

이제 iam 작업을 진행하자. 나는 다른 뉴진스 팬에게도 버킷의 업로드 권한을 주고 싶다.
우선 s3 버킷의 업로드할 수 있는 정책을 생성하자. 아래는 버킷에 업로드 가능하게 하는 정책이다.
```json
#upload_poilicy_json
{
    "Version": "2012-10-17",
    "Statement": [
        {
            "Effect": "Allow",
            "Action": [
                "s3:PutObject" #파일업로드
            ],
            "Resource": "arn:aws:s3:::newjeans-image/*"
        }
    ]
}
```
 
 이제 해당 정책을 우리가 만든  뉴진스 팬이 사용할 수 있게하자.

```bash
aws iam put-user-policy --user-name newjeansfan -
icy-name PutImage --policy-document file://upload_policy.json
```

이제 뉴진스 팬으로 로그인을 해서 업로드를 진행해보면 업로드가 정상적으로 진행되는 것을 확인해볼 수 있다.

```bash
aws s3 cp ~/Downloads/test.gif s3://newjeans-image/newjeans --profile newjeansfan
```
