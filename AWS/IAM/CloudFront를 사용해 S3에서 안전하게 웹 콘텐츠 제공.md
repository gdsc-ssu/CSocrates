## CloudFront를 사용해 S3에서 안전하게 웹 콘텐츠 제공

- CloudFront를 사용해 S3의 프라이빗 웹 콘텐츠를 제공하고자 한다.

## CloudFront란?

<aside> 💡 html, css, js 등의 정적 및 동적 웹 콘텐츠를 사용자에게 더 빨리 배포하도록 지원하는 서비스 → 즉 `CDN` 역할을 하는 서비스다.

</aside>

- `CDN`은 content delivery network의 약자로 네트워크 설계로 인해 발생하는 통신 지연을 줄이기 위한 것.
  - 물리적으로 거리가 멀면 멀수록 지연시간이 생길 수 밖에 없다.
  - 이럴 때 클라이언트와 서버 중간에 캐시 서버를 두어 속도를 높이는 것

![[스크린샷 2024-06-10 14.32.48.png]]

- “엣지 로케이션”이라고 하는 aws 데이터 센터를 이용하여 전세계 네트워크를 통해 콘텐츠를 제공
  - 일반적인 웹 서버에서 이미지의 경우 url을 통해 제공되어짐
    - ex) https://example.com/sunsetphoto.png
  - 해당 이미지로 접속하게 되면 여러 네트워크의 복잡한 방식을 통해 라우팅 된다.
    → 클라우드 프론트의 경우 이런 라우팅 방식을 효과적으로 제어해 콘텐츠 배포 속도를 올린다.
    (최종 사용자에게 가장 가까운 네트워크를 사용해서 빠르게 데이터를 제공한다)

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

- 왜 CDN을 사용하면 DDos가 줄어드는가? - DDoS 공격은 호스팅 서버에 과부하를 주어 작동하기 때문에 CDN은 지리적으로 분산되어 있고 사용자와 더 가까운 여러 서버에서 부하를 균등하게 공유함으로써 도움이 된다. - 이렇게 하면 한 서버가 다운되더라도 계속 작동하는 서버가 존재한다 - 또한 인증서 관리와 자동 인증서 생성 및 갱신을 제공하여 보안을 지킨다.
  ⇒ cdn 자체가 여러개의 캐시 서버를 두는 것이므로 오리진에 대한 부하를 효과적으로 줄일 수 있다.

- 캐시 기능으로 인해 원본이 업데이트가 안될 수 있다.
  - 이럴때에는 “무효화 기능(invalidation)”을 통해 수정된 파일이 캐시로 바로 반영하도록 설정할 수 있다.
    → TTL이 지나기 전에 강제로 캐시 삭제하는 것, 추가적인 비용이 발생한다 (1000건 무료, 그 뒤는 요청 하나당 5~6원)

## Reference

[[AWS] S3와 CloudFront 연동하기](https://velog.io/@rungoat/AWS-S3%EC%99%80-CloudFront-%EC%97%B0%EB%8F%99%ED%95%98%EA%B8%B0)
