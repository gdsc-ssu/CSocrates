---

---
#AWS #DynamoDB

### DynamoDB란?

DynamoDB는 NoSQL(Not Only SQL) 데이터베이스

---

### SQL? NoSQL?

#### SQL 

SQL을 사용하면 RDBMS에서 데이터를 저장, 수정, 삭제 및 검색 할 수 있음

- **RDB(Relational Database)**  관계형 데이타 모델에 기초를 둔 데이터 베이스
	관계형 데이타 모델이란 데이타를 구성하는데 필요한 방법 중 하나로 모든 데이타를 2차원의 테이블 형태로 표현
- **RDBMS**(Relational DataBase Management System)란 관계형 데이터베이스 관리 시스템으로, 모든 데이터를 2차원 테이블 형태로 표현하는 데이터베이스

SQL은 RDBMS에서 사용되는 언어로 국제표준화기구에서 표준 SQL을 정하지만 사용하는 DBMS 제품마다 기능에 차이가 있기 때문에, 제품마다 사용되는 언어의 이름이 조금씩 다름
(MySQL: SQL,SQL 서버: T-SQL, Oracle: PL/SQL)

#### NoSQL

관계형 DB의 반대, **스키마도 없고, 관계도 없음**

NoSQL은 관계형 데이터베이스처럼 행과 열이 존재하는 테이블 형태가 아니기에  데이터 모델을 어떻게 설계하느냐에 따라 데이터베이스의 포멧이 달라지는데 이는 크게 세 가지로 나눌 수있음

- 문서 데이터 베이스
	- 주로 JSON 형태의 문서를 보관. 문서는 필드와 값으로 구성되어 있으며 문자열, 숫자, 배열 등 다양한 데이터 타입을 허용
- Key-Value 데이터 베이스
	- 문서 데이터베이스와 비슷하나 구조가 훨씬 간단하며, 마찬가지로 Key-Value 형태의 JSON 데이터를 보관
- 그래프 데이터 베이스
	- 노드와 엣지를 사용하여 데이터를 보관
![300](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/DynamoDB%20/%20Pasted%20image%2020240802165312.png)

#### NoSQL 도입

NoSQL에 탄생하기 전까지, 데이터베이스 시스템은 RDBMS(관계형 데이터베이스) 세상이었음
스토리지 비용이 비쌌던 시절, 정규화를 통해 중복 데이터를 최대한 줄이는 것이 중요했고, 관계형 데이터베이스는 그것을 수행하기에 최적의 도구였음

즉, **관계형 데이터베이스의 목적은 효율적인 스토리지의 사용**임

그러나, 최근들어 스토리지의 비용이 점차 저렴해지고, 대규모의 연산을 빠르게 처리해내는게 중요해짐에 따라, 데이터가 중복되도 좋으니, 데이터베이스도 빠르게 처리하는 것이 중요한 시대가 되었음

**스토리지를 희생하더라도, 성능을 최대한 끌어올리자, 그래서 NoSQL이 나온 것**

---

### DynamoDB 개념

그래서 DynamoDB는 어떻게 생겼을까?

![500](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/DynamoDB%20/%20Pasted%20image%2020240802165639.png)

아이템 : {’ customer_id ’ : 644, ’age ’ : 26, ’visit ’ : True} -> 행
특징 : {’age’ : [26, 31]} -> 열

테이블을 JSON 형태로 표현하면 다음과 같음
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/DynamoDB%20/%20Pasted%20image%2020240802181148.png)

---

### DynamoDB 특징

-  DynamoDB는 HTTP 통신을 한다. 해서, 다른 DB Resource들이 TCP Connection 기반인데 비해, 비연결지향(Connectionless)함
- AWS Lambda와 DynamoDB를 같이 쓰면 좋음 
	- 앞서 언급한 것과 같이 NoSQL의 탄생 목적 자체가 트래픽이 많아져 연산의 속도를 극대화 시켜야 하는 상황
	  그러한 상황에선 scale-in/out 능력이 중요한데, Lambda도 그 목적에 부합하는 컴퓨팅 리소스이기 때문(반대로, scale-in/out 능력이 중요한 RDBMS와는 잘 맞지 않음)
- Key를 제외한 테이블의 속성들은 미리 정의 될 필요가 없음. 유연하게 뭐든 들어갈 수 있음


---

### DynamoDB 장점

- NoSQL 데이터베이스는 쿼리 속도(특히 읽기 속도)가 매우 삐름
	- NoSQL은 테이블 비정규화 과정을 기본적으로 거치는데, 테이블 비정규 화는 쓰기 퍼포먼스를 낮추는 대신 읽기 퍼포먼스를 극대화하는 것이 핵심
	- 비정규화된 테이블은 이미 중복 데이터를 포함하고 있기 때문에 다른 태이블과 합치는 과정(join)이 필요 없음
![500](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/DynamoDB%20/%20Pasted%20image%2020240802181440.png)

- 오토스케일링 가능
	- 데이터베이스를 만들 때 크기가 정해지는데 오토스케일링 기능이 활성화된다면 들어오는 데이터 크기에 따라 태이블 크기가 자동으로 변경됨
	- EC2 인스턴스와 마찬가지로 DynamoDB 역시 데이터의 처리량에 따라 성능을 늘렸다 줄였다 함
	- 이를 통해 불필요한 자원을 줄여 비용을 대폭 절약할 수 있음

- NoSQL이기 때문에 테이블 생성 시 스키마를 정의할 필요가 없음
	- 스키마에는 데이터 베이스의 전반적인 구조 및 데이터 개체, 속성등의 정보 포함
		- 하나 혹은 여러 개의 테이블이 존재할 수 있으며 다른 스키마와 어떤 관계에 놓여있는지에 대한 무결성 제약 조건을 정의할 수 있음
	- 테이블 생성 시 기본키를 제외한 어떤 것도 미리 정의되지 않기에 개제와 속성을 미리 알 필요가 없음. JSON 형태의 데 이터가 들어오면 그대로 스키마와 테이블이 생성되며 데이터 타입이 자동으로 정의됨

- DynamoDB는 SSD스토리지를 사용하기 때문에 데이터를 읽고 쓰는 데 속도가 빠름

---

### DynamoDB 기본키

#### 파티션키

테이블에 있는 데이터를 파티션으로 나누고 분리시키는 데 사용되는 키
실제로 데이터가 들어가는 장소(장소란 DynamoDB 안에서 해시 함수를 실행시켜 반환되는 주솟값)를 정해줌

![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/DynamoDB%20/%20Pasted%20image%2020240802182313.png)
고려사항
- 주로 높은 카디널리티(중복된 데이커가 많이 않은 것)가 파티션 키로 사용됨
	- ex. 아이디필드가 주로 사용됨

#### 복합키

여러 개의 키를 합쳐놨다는 뜻이며 위에서 살펴본 파티션키와 정렬키(*정렬키는 파티션키로 데이터가 다른 장소로 분리된 다음 그 안에서 정렬키에 의해 데이터가 정렬될 때 사용되는 기준점*)를 합쳐 놓은 것

![500](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/DynamoDB%20/%20Pasted%20image%2020240802182716.png)


**DynamoDB 기본키는 파티션키 혹은 복합키 둘중 하나를 반드시 선택**해야하며 **정렬키만 기본키로 지정할 수 없음**
정렬키는 시간별로 데이터를 정렬하여 원하는 시간대에 포함되어 있는 데이터만 쿼리해서 가져올 때 시용되며 따라서 시간 정보가 들어있는 열이 주로 선택됨

---

### DynamoDB 데이터 접근 관리

DynamoDB에 있는 테이블과 데이터는 AWS 사용자 모두에게 공개될 수 있지만 특정 부서와 유저에게만 필요한 테이블을 쿼리할 수 있는 권한을 부여할 수도 있음

사용자에게 테이블 생성과 접근 권한을 부여할 수 있으며, 특정 테이블과 특정 데이터에만 접근을 가능하게 해주는 IAM 역할도 존재함

ex. 아래는 전 세계 게이머 정보가 들어가있는 테이블이고 쿼리를 통해 현재 본인 기록을 확인하고 싶을때 
![400](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/DynamoDB%20/%20Pasted%20image%2020240802183000.png)

---

### 좋은 DB 디자인을 위한 인덱스

앞써 설명한 파티션키와 복합키를 올바르게 골랐다면 아무리 방대한 양의 데이터가 있어도 쿼리 속도는 빠르게 할 수 잇음

**그러나 여기서 쿼리 성능을 더 끌어올릴 수 있는 방법이 있는데, DynamoDB에는 인텍스(index)라는 개념이 존재**
인텍스란 데이터 쿼리 시 테이블 전체를 스캔하는 것이 아니라 선택한 특정 열을 기준으로 쿼리가 진행함

#### 로컬 보조 인덱스(LSI)

LSI는 DynamoDB 테이블 생성 시에만 정의가능하고 테이블을 만든 후 LSI는 변경 또는 삭제가 불기능함

파티션키를 사용해야 하지만 정렬키는 다른 것을 사용할 수 있음
즉, 똑같은 파티션키를 사용하더라도 정렬키가 다르기 때문에 전혀 다른 뷰를 생성할 수 있음
파티션키와 정렬키를 같이 사용하기 때문에 LSI는 앞서 배운 복합키를 사용한다고 말할 수 있음

##### 뷰?

테이블은 데이터가 들어가기 위해 만들어지는 컨테이너이며 실제로 데이터가 존재하는 곳
뷰는 테이블과 마찬가지로 행과 열이 있으며 테이블과 구조가 똑같으나 뷰는 테이블에서 파생된 것이며 데이터가 들어있지 않음
그래서 일반적으로 뷰에서 데이터 수정을 할 수 없음

테이블에서 데이터가 변경되면 뷰는 이를 인식하고 즉시 반영함
인텍스를 정의한다는 의미는 테이블에서 어떤 변화를 주는 것이 아니라 기존 테이블에서 새로운 뷰를 만드는 것임

![500](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/DynamoDB%20/%20Pasted%20image%2020240802183719.png)

#### 글로벌 보조 인덱스(GSI)

LSI와 달리 GSI는 테이블 생성 후에도 추가, 변경, 삭제가 가능함. 뿐만 아니라 파티션키와 정렬키를 원래 테이블과 다르게 정의할 수 있음. 정렬키는 필수가 아닌 선택사항
**따라서 완전히 다른 뷰를 만들 수 있음**

![500](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/DynamoDB%20/%20Pasted%20image%2020240802184234.png)

#### 그렇다면 두 인덱스는 언제 사용?

정렬키를 사용해 정렬된 데이터에서 하나의 파티션키가 들어있는 테이블을 주로 쿼리하는 상황이 발생할 경우 LSI를 권장
GSI에서 정렬키는 선택사항이기 때문에 정렬키의 중요성에 따라 LSI와 GSI의 선택이 갈릴 수 있음

---

### 데이터를 가져오는 방법(쿼리 vs 스캔)

#### 쿼리

쿼리는 테이블을 만들 때 정의한 기본키를 가지고 데이터를 가져오는 방법

![500](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/DynamoDB%20/%20Pasted%20image%2020240802184433.png)

만약 쿼리를 하고 반환되는 데이터 양이 너무 많다면 정렬키를 제공하고 추가로 필터링하여 원하는 데이터를 가져올 수 있음
거래 아이디 AAA로 가장 최근에 진행된 거래가 무엇인지 알고 싶다면 거래 시간을 정렬키로 설정하여 쿼리를 수행하면 됨

기본적으로 쿼리는 모든 열을 가져오는데 ‘ProjectionExpression’이라는 파라미터를 추가로 제공하여 우리가 원하는 열만 가져올 수도 있음

#### 스캔

기본키를 사용하지 않고 테이블 안에 있는 모든 데이터를 불러옴
모든 데이터를 불러온 다음 필터를 따로 추가하여 원하는 데이터만 볼 수 있는 기능을 제공함. 스캔도 쿼리와 마찬가지로 Projection Expression 파라미터를 제공하기에 스캔을 통해 원하는 열만 볼 수 있음

![500](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/DynamoDB%20/%20Pasted%20image%2020240802184705.png)

스캔을 하면 테이블에서 한 번에 모든 데이터를 가져오는 것이 아니라 첫 1MB에 해당하는 데이터를 반환함
그다음 1MB에 해당하는 배치 데이터를 반환하는데 이것을 **순차적 스캔**이라고 함

작은 태이블을 스캔할 경우 첫 배치 데이터 크기가 1MB 미만이라면 한 번에 반환되지만 테이블의 크기가 100MB가 넘는다면 총 100번의 배치 데이터가 반환되며 그만큼 속도가 저하됨

![500](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/DynamoDB%20/%20Pasted%20image%2020240802184840.png)

스캔의 성능을 향상시키기 위해 스캔을 실행할 때 수많은 스캔 일꾼을 여러 군데 분산시켜 병행하는 기능을 활용
이를 **병렬 스캔**이라고 함

테이블 전체를 N등분한 후 스캔 일꾼을 N등분된 조각으로 보내 동시다발적으로 스캔을 진행함

#### 쿼리 VS 스캔

쿼리와 스캔은 쿼리는 초반에 테이블의 일부만 검색하여 데이터를 가져오는 반면, 스캔은 일단 테이블 전체를 한 번 살펴본 후 필터링 작업이 이루어진다는 차이점이 있음

따라서 방대한 양의 데이터가 있는 태이블을 시용할 시 쿼리가 스캔보다 훨씬 효율적임

시간이 지나면서 데이터가 테이블에 계속 쌓이고 테이블의 크기는 계속 늘어나는데 그럼 스캔을 사용할 필요가 전혀 없는 것일까?

AWS에서는 가급적이면 쿼리를 사용하라고 권장하지만 참고용이 존재하며, 아이디 필드가 없고, 기본키가 정의되어 있지 않고, 테이블의 크기가 크지 않다면 스캔을 사용해도 무방함

->  상품 고유코드를 담고 있는 테이블은 크기가 크지 않고 기본키도 없음. Lookup 테이블의 특징은 실시간으로 데이터가 자주 업데이트 되지 않고 데이터 중복이 없다는 점이 있음

![300](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/DynamoDB%20/%20Pasted%20image%2020240802185338.png)


---
### 참고

- https://alphahackerhan.tistory.com/39
- https://gyoogle.dev/blog/computer-science/data-base/SQL%20&%20NOSQL.html
- https://velog.io/@rik963/Database-RDBMS-%EA%B5%AC%EC%A1%B0%EC%99%80-%EC%84%A4%EA%B3%84
- https://velog.io/@park2348190/%EB%85%BC%EB%AC%B8%EB%B2%88%EC%97%AD-SQL-vs-NoSQL-A-Performance-Comparison

---

### 추가

##### 스캔의 실사용 예시

**1. 테이블의 특정 속성 값을 기반으로 데이터 검색**

- 예를 들어, 사용자의 주문 내역을 저장하는 테이블이 있다고 가정해 보면 이 테이블의 파티션 키는 `user_id`이고, 정렬 키는 `order_id`임. 하지만 특정 날짜에 이루어진 모든 주문을 검색하고 싶다면, 이 날짜는 파티션 키나 정렬 키가 아니기 때문에 쿼리로는 직접 검색할 수 없음

```python
import boto3

# DynamoDB 클라이언트 생성
dynamodb = boto3.resource('dynamodb')
table = dynamodb.Table('Orders')

# 스캔을 사용하여 특정 날짜의 주문을 검색
response = table.scan(
    FilterExpression="order_date = :order_date_value",
    ExpressionAttributeValues={":order_date_value": "2024-08-14"}
)

# 결과 출력
items = response['Items']
for item in items:
    print(item)

```

이 예시에서 `order_date` 필드가 특정 날짜(`2024-08-14`)와 일치하는 모든 주문을 검색함
스캔은 테이블의 모든 항목을 검색하고, 필터 조건을 적용하여 결과를 반환함

**2. 모든 항목에서 특정 속성이 없는 항목 찾기**

- 예를 들어, 사용자 프로필이 저장된 테이블이 있는데, 이 테이블에는 일부 사용자 프로필에 `email` 필드가 없을 수 있음 `email` 필드가 없는 모든 항목을 찾기 위해 스캔을 사용할 수 있음

```python
response = table.scan(
    FilterExpression="attribute_not_exists(email)"
)

items = response['Items']
for item in items:
    print(item)

```

이 예시에서는 `email` 필드가 없는 모든 항목을 검색함 `attribute_not_exists` 함수는 특정 속성이 없는 항목을 필터링하는 데 사용됨

**3. 모든 데이터를 가져와서 로컬에서 처리할 때**

- 테이블에 데이터가 많지 않거나, 특정 필드를 기반으로 통계나 보고서를 작성하려고 하는 경우 전체 데이터를 가져와서 로컬에서 처리할 수 있음

```python
response = table.scan()

items = response['Items']
for item in items:
    # 데이터 처리 (예: 특정 필드의 값 누적 등)
    print(item)

```

**4. 기타 복잡한 조건을 만족하는 데이터 검색**

- 특정 조건들이 조합된 복잡한 필터링을 적용해야 하는 경우, 여러 필드의 값을 결합하여 특정 조건에 맞는 데이터를 찾을 수 있음

```python
response = table.scan(
    FilterExpression="attribute_exists(phone) AND begins_with(name, :prefix)",
    ExpressionAttributeValues={":prefix": "John"}
)

items = response['Items']
for item in items:
    print(item)

```

이 예시에서는 `phone` 필드가 존재하고, `name` 필드가 "John"으로 시작하는 모든 항목을 검색함

(GPT 피셜)

##### 왜 LSI는 변경, 수정, 삭제가 안되는지?

LSI는 DynamoDB의 기본 테이블과 밀접하게 통합된 구조로 인해 생성 이후에는 변경, 수정, 삭제가 불가능함. 
이는 데이터 일관성, 성능, 안정성을 유지하기 위한 아키텍처적 설계 결정이며, 이러한 제약을 통해 DynamoDB는 대규모 데이터베이스에서도 신뢰할 수 있는 성능을 제공하게됨

##### SQL vs NOSQL 사용 예시

- **SQL**은 **정형화된 데이터**와 **복잡한 관계**를 효율적으로 관리하고, **정교한 쿼리**가 필요한 상황에서 유용함. 예를 들어, 전자상거래 시스템에서 주문, 고객, 제품 간의 복잡한 관계를 관리할 때 SQL이 적합함
- **NoSQL**은 **비정형 데이터**나 **대규모 데이터**를 빠르게 처리해야 하는 상황에서 유용함. 예를 들어, 소셜 미디어 플랫폼에서 유연한 데이터 구조와 빠른 성능이 필요할 때 NoSQL이 적합함

##### 진짜 NOSQL 빠른지?

퍼포먼스 비교 측면에서 SQl과 NOSQL을 비교해보면... 
실제로 측정하진 못했지만 위 [논문](https://www.cs.rochester.edu/courses/261/fall2017/termpaper/submissions/06/Paper.pdf)을 확인해 보면 명확한 퍼포먼스 비교가 가능함

![500](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/DynamoDB%20/%20Pasted%20image%2020240814162614.png)

가장 많이 사용하는 관계형 데이터베이스인 MySQL과 Key-value NoSQL인 BerkeleyDB, Document NoSQL인 MongoDB에 대하여 실험을 진행한 것으로 읽기 연산에는 NoSQL이 전반적으로 3배 이상 빠른것을 볼 수 있음

