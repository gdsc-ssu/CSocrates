
- CloudFront를 사용해 S3의 프라이빗 웹 콘텐츠를 제공하고자 한다.

## CloudFront란?
<aside>html, css, js 등의 정적 및 동적 웹 콘텐츠를 사용자에게 더 빨리 배포하도록 지원하는 서비스 → 즉 `CDN` 역할을 하는 서비스다.
</aside>

- `CDN`은 content delivery network의 약자로 네트워크 설계로 인해 발생하는 통신 지연을 줄이기 위한 것.
  - 물리적으로 거리가 멀면 멀수록 지연시간이 생길 수 밖에 없다.
  - 이럴 때 클라이언트와 서버 중간에 캐시 서버를 두어 속도를 높이는 것

![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/CloudFront%EB%A5%BC%20%EC%82%AC%EC%9A%A9%ED%95%B4%20S3%EC%97%90%EC%84%9C%20%EC%95%88%EC%A0%84%ED%95%98%EA%B2%8C%20%EC%9B%B9%20%EC%BD%98%ED%85%90%EC%B8%A0%20%EC%A0%9C%EA%B3%B5%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-06-10%2014.32.48.png)

- “엣지 로케이션”이라고 하는 aws 데이터 센터를 이용하여 전세계 네트워크를 통해 콘텐츠를 제공
  - 일반적인 웹 서버에서 이미지의 경우 url을 통해 제공되어짐
    - ex) https://example.com/sunsetphoto.png
  - 해당 이미지로 접속하게 되면 여러 네트워크의 복잡한 방식을 통해 라우팅 된다.
    → 클라우드 프론트의 경우 이런 라우팅 방식을 효과적으로 제어해 콘텐츠 배포 속도를 올린다.
    (최종 사용자에게 가장 가까운 네트워크를 사용해서 빠르게 데이터를 제공한다)

### CDN (Content Delivery Network) 이란?
- cdn은 content delivery network의 약자로 네트워크 설계로 인해 발생하는 통신 지연을 줄이기 위한 것.
    - 물리적으로 거리가 멀면 멀수록 지연시간이 생길 수 밖에 없다.
    - 이럴 때 클라이언트와 서버 중간에 캐시 서버를 두어 속도를 높이는 것

## Cloud Front 콘텐츠 제공 방법
1. 웹사이트 혹은 앱에서 객체(데이터)에 대한 요청을 보낸다.
2. DNS는 최적으로 요청을 처리할 수 있는 CloudFront POP(엣지 로케이션)로 라우팅 (일반적으로는 지연시간이 가장 짧은 곳)
3. CloudFront는 해당 캐시에 요청된 객체가 있는지 확인, 있으면 사용자에게 반환
    1. 없으면 해당 객체(데이터)의 오리진에서 데이터를 가져옴
    2. 오리진에서 첫 번째 바이트가 도착하는 순간부터 CloudFront가 객체를 사용자에게 전달하기 시작.
    3. CloudFront는 다음에 다른 사용자가 객체를 요청할 때 캐시에 해당 객체를 추가

- 또한 CloudFront는 캐시를 두단계로 나눠서 관리.

1. 전역 엣지 로케이션인 POP는 사용자에게 가장 가까운 위치.
2. 리전 엣지 캐시는 POP와 오리진 서버 사이에 위치, POP보다는 덜 사용되는 데이터들의 정보를 가지고 있다.

![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/CloudFront%EB%A5%BC%20%EC%82%AC%EC%9A%A9%ED%95%B4%20S3%EC%97%90%EC%84%9C%20%EC%95%88%EC%A0%84%ED%95%98%EA%B2%8C%20%EC%9B%B9%20%EC%BD%98%ED%85%90%EC%B8%A0%20%EC%A0%9C%EA%B3%B5%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-06-05%2013.42.47.png)

## 사용 사례
- s3 + cloudFront로 정적 웹 콘텐츠 (html, css, js)의 전송속도를 높일 수 있다.
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/CloudFront%EB%A5%BC%20%EC%82%AC%EC%9A%A9%ED%95%B4%20S3%EC%97%90%EC%84%9C%20%EC%95%88%EC%A0%84%ED%95%98%EA%B2%8C%20%EC%9B%B9%20%EC%BD%98%ED%85%90%EC%B8%A0%20%EC%A0%9C%EA%B3%B5%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-06-10%2013.35.31.png)
- 미디어를 스트리밍하기 위한 몇 가지 옵션을 제공한다
    - 온디맨드 비디오 : hls, mpeg dash 등과 같은 일반적인 포맷으로 디바이스에 상관없이 스트리밍 가능
    - 라이브 스트리밍 : 엣지에 미디어 조각을 캐싱하여 해당 소작을 올바른 순서로 전송하는 manifast 파일에 대한 여러 요청을 결합함으로써 오리진 서버의 부하를 줄일 수 있음.
- https로도 구성 가능 (보안)
- 엣지에서 서버리스 코드를 실행하면 지연 시간을 최소화하면서 다양한 방식으로 최종 사용자에 대한 콘텐츠와 환경을 사용자 지정할 수 있다.
    - 예를 들어 오리진 서버가 유지보수를 위해 다운된 경우 최종 사용자에게 일반 HTTP 오류 메시지를 표시하는 대신 사용자 지정 오류 메시지를 표시할 수 있다.
- Lambda@Edge를 사용하면 서명된 URL 또는 서명된 쿠키를 사용하는 것 이외에, 자체 사용자 지정 오리진에서 프라이빗 콘텐츠를 제공하도록 CloudFront 배포를 구성할 수 있다.
## 정책
- 3가지의 정책 설정 가능
1. 캐시 정책 (Cache Control)
	- TTL 및 Cache Key 정책 
	- \기본적으로 클라우드프론트는 URL만을 사용하여 캐시를 구분하지만, 필요한 경우 쿠키, 헤더, 쿼리 스트링 등을 포함하여 더 세부적으로 캐시를 설정할 수 있다
2. 원본 요청 정책 (Origin Request)
    - 원본 서버에 콘텐츠를 요청할 때 어떤 쿠키, 헤더, 쿼리 스트링을 포함할지 결정
3. 응답 헤더 정책
    - 사용자에게 콘텐츠를 반환할 때 포함할 HTTP 응답 헤더를 정

### Client가 S3에 직접 접근하지 않고 CloudFront를 통해 접근할 때의 이점
- 콘텐츠 캐싱을 통한 s3 부하 감소
- Edge Location을 통한 응답속도 향상
- 콘텐츠 보안 유지
  - DDos도 방어하기 좋음, DDoS 공격은 호스팅 서버에 과부하를 주어 작동하기 때문에 CDN은 지리적으로 분산되어 있고 사용자와 더 가까운 여러 서버에서 부하를 균등하게 공유함으로써 도움이 된다.

### OAI (Origin Access Identity)
- aws에서 s3의 컨텐츠를 CloudFront를 사용해서만 볼 수 있도록 제한하는 방식
- s3의 url로 바로 접근하는 것이 아닌 CDN을 통해서 접근 하는 것.
- 이렇게 하는 이유는 s3로 직접 접속을 하면 캐싱을 못해 속도에서 마이너스가 될 수도 있고, 국가별 라우팅, 인증 등이 CloudFront에 구현되어 있다면 유저가 s3로 직접 접속하면 안되기 때문에.
⇒ 결국 효율성과 보안을 위해서 이렇게 사용하는 것.

- 방법은 간단하다. S3의 퍼블릭접근을 막은 후 CloudFront만을 사용해서 접근할 수 있게 만들면 된다.

## 실습
- github 관련 코드입니다.
https://github.com/AWSCookbook/Security/tree/main/110-Serving-Web-Content-Securely-from-S3-with-CloudFront

```bash
## S3 버킷 생성
# 'my-unique-04150415' 이름의 S3 버킷을 'ap-northeast-2' 리전(서울)에 생성
aws s3api create-bucket --bucket my-unique-04150415 --region ap-northeast-2 --create-bucket-configuration LocationConstraint=ap-northeast-2

## 파일 업로드
# 'index.html' 파일을 생성한 S3 버킷의 루트에 업로드
aws s3 cp index.html s3://my-unique-04150415/

## 퍼블릭 접근 차단
# S3 버킷의 퍼블릭 접근을 차단
aws s3api put-public-access-block \
     --bucket my-unique-04150415 \
     --public-access-block-configuration BlockPublicAcls=true,IgnorePublicAcls=true,BlockPublicPolicy=true,RestrictPublicBuckets=true

## OAI 생성
# CloudFront Origin Access Identity (OAI)를 생성하고, 그 ID를 'OAI' 변수에 저장
OAI=$(aws cloudfront create-cloud-front-origin-access-identity \
    --cloud-front-origin-access-identity-config CallerReference="awscookbook",Comment="AWSCookbook OAI" \
    --query 'CloudFrontOriginAccessIdentity.Id' --output text)

## 배포 템플릿 수정
# CloudFront 배포 설정 템플릿 파일 'distribution-template.json'에서 'CLOUDFRONT_OAI'와 'S3_BUCKET_NAME'을 실제 값으로 대체하여 'distribution.json' 파일로 저장
sed -e "s/CLOUDFRONT_OAI/${OAI}/g" \
    -e "s/S3_BUCKET_NAME/my-unique-04150415/g" \
    distribution-template.json > distribution.json

## CloudFront 배포 생성
# 수정된 'distribution.json' 파일을 사용하여 CloudFront 배포를 생성하고, 그 ID를 'DISTRIBUTION_ID' 변수에 저장
DISTRIBUTION_ID=$(aws cloudfront create-distribution \
    --distribution-config file://distribution.json \
    --query 'Distribution.Id' --output text)

## 배포 상태 확인
# 생성된 CloudFront 배포의 상태를 확인
aws cloudfront get-distribution --id $DISTRIBUTION_ID \
    --output text --query 'Distribution.Status'

## 버킷 정책 템플릿 수정
# 버킷 정책 템플릿 파일 'bucket-policy-template.json'에서 'CLOUDFRONT_OAI'와 'S3_BUCKET_NAME'을 실제 값으로 대체하여 'bucket-policy.json' 파일로 저장
sed -e "s/CLOUDFRONT_OAI/${OAI}/g" \
    -e "s/S3_BUCKET_NAME/my-unique-04150415/g" \
    bucket-policy-template.json > bucket-policy.json

## 버킷 정책 적용
# 수정된 'bucket-policy.json' 파일을 사용하여 S3 버킷에 정책을 적용
aws s3api put-bucket-policy --bucket my-unique-04150415 \
    --policy file://bucket-policy.json

## CloudFront 도메인 이름 가져오기
# 생성된 CloudFront 배포의 도메인 이름을 가져와 'DOMAIN_NAME' 변수에 저장
DOMAIN_NAME=$(aws cloudfront get-distribution --id $DISTRIBUTION_ID \
    --query 'Distribution.DomainName' --output text)

# 접속해보기
curl https://$DOMAIN_NAME/index.html
```

## 기타
#### 왜 CDN을 사용하면 DDos가 줄어드는가?
- DDoS 공격은 호스팅 서버에 과부하를 주어 작동하기 때문에 CDN은 지리적으로 분산되어 있고 사용자와 더 가까운 여러 서버에서 부하를 균등하게 공유함으로써 도움이 된다.
- 이렇게 하면 한 서버가 다운되더라도 계속 작동하는 서버가 존재한다
- 또한 인증서 관리와 자동 인증서 생성 및 갱신을 제공하여 보안을 지킨다.

#### 캐시 기능으로 인해 원본이 업데이트가 안될 수 있다.
  - 이럴때에는 “무효화 기능(invalidation)”을 통해 수정된 파일이 캐시로 바로 반영하도록 설정할 수 있다.
    → TTL이 지나기 전에 강제로 캐시 삭제하는 것, 추가적인 비용이 발생한다 (1000건 무료, 그 뒤는 요청 하나당 5~6원)

## Reference

[[AWS] S3와 CloudFront 연동하기](https://velog.io/@rungoat/AWS-S3%EC%99%80-CloudFront-%EC%97%B0%EB%8F%99%ED%95%98%EA%B8%B0)
https://docs.aws.amazon.com/AmazonCloudFront/latest/DeveloperGuide/Introduction.html