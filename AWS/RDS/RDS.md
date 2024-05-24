# RDS란?
- Relational Database Service - 관계형 데이터베이스 서비스
[**데이터베이스란?**](https://www.oracle.com/kr/database/what-is-database/)
- 데이터베이스는 구조화된 정보 또는 데이터의 조직화된 모음으로서 일반적으로 컴퓨터 시스템에 전자적으로 저장됩니다.
- 결국 정보가 저장된 데이터 모음.
- 그렇다면 스프레드 시트랑 뭐가 다를까? 스프레드 시트에도 함수로 데이터를 가져올 수 있는데?
>[!info]
>스프레드시트 vs 데이터베이스
>- 데이터 저장 및 조작
>- 데이터에 액세스 할 수 있는 사람
>- 저장할 수 있는 데이터 양
>
>적은 수의 사람이나 복잡한 데이터 조작이 없는 경우에는 스프레드 시트가 적합하지만, 방대한 양의 정보를 저장하고 복잡한 로직을 처리하기 간편하다.

RDS란 "관계형 데이터베이스"라는 것
NoSQL과 같은 관계형 데이터베이스가 아닌 경우에는 DynamoDB와 같은 데이터베이스를 사용해야한다.
#### 관계형 데이터베이스
왜 관계형이라는 표현을 할까?
왜냐하면 데이터베이스 안에 각각의 객체들이 관계를 맺고 있기 때문이다.
가장 쉽게 비슷하게 생각할 수 있는건 엑셀과 함수이다.
하나의 테이블 안에 각 속성들을 Column으로 설정되고, Row마다 데이터를 넣을 수있다.
데이터베이스에서 사용하는 용어를 정리해보자.
- Database
	- 데이터베이스
	- 하나 혹은 여러 개의 테이블을 생성하고 관리하는 공간
- Table
	- Row, Column으로 이루어진 공간
- Row
	- 하나의 데이터를 의미
- Column
	- 특정한 값을 담고 있고, 하나의 필드에는 한 개의 데이터가 존재
#### OLTP vs OLAP
**OLTP**
데이터가 데이터베이스에 삽입되자마자 바로 쿼리하고 사용될 때, 작은 규모의 데이터를 불러올 때 사용되는 시스템
실시간 데이터를 데이터베이스에 보관하고 꺼내서 프로세싱하는 경우
예를 들어 하나의 테이블에 서브셋 데이터를 갖고오는 경우
**OLAP**
다차원 데이터 분석을 할 때 유용
큰 데이터를 한 번에 불러오고 실시간이 아니라, 이미 저장된 데이터를 기반으로 히스토리컬 데이터를 불러올 때 사용
트랜잭션 프로세싱이 사용되지 않는다.
# 데이터베이스 백업
컴퓨터를 사용하다가 저장되지 않는 파일이 날라간다면 어떨까? 바로 재앙 발생이다.
데이터를 저장하는 데이터베이스도 마찬가지이다!
#### 자동 백업
자동 백업 (automated backup)은 1~35일의 보유기간 내에 특정 시간으로 데이터베이스 상태를 복원할 수 있다.
이를 가능하게 하기위해서는 스냅샷과 트랜잭션 로그가 필요하다.
AB는 정보를 s3 버킷에 저장한다.
하지만 RDB 크기에 따라서 s3 무료 저장공간이 달라지게 된다.
단점으로는 백업이 이루어지는 동안 입출력 지연이 발생한다. 그리고 RDS 인스턴스 삭제하면 자동 백업도 삭제된다.
#### 데이터베이스 스냅샷
데이터베이스 스냅샷 (database snapshot)이란 데이터베이스 인스턴스를 통째로 복사한다.
인스턴스 안에는 스토리지 볼륨 정보, 파일의 크기, 스냅샷이 만들어진 시간 등 다양한 정보를 담고 있다.
```sh
# 데이터베이스 상태 확인하기
aws rds describe-db-instances --db-instance-identifier mydbinstance
```
![[스크린샷 2024-05-24 오후 11.10.48.png]]
스냅샷은 개발자가 수동으로 생성해야하고, 원본 RDS를 삭제해도 스냅샷은 존재하여 삭제된 인스턴스를 되살릴 수 있다.
#### 백업을 어떻게 하는데?
백업을 만들면 새로운 데이터베이스 인스턴스를 만든다.

# 다중 가용 영역과 읽기 전용 복사
#### 다중 가용 영역
다중 가용 영역 (multi availability zone)은 가용 영역은 여러 개가 있다는 뜻이다.
데이터베이스에서 이벤트(쓰기, 읽기 등)가 발생하면 원래 데이터베이스 인스턴스에 업데이트 하는 동시에 존재하는 가용 영역에 복제본이 만들어진다.
복제본 생성에 실패하는 경우 다른 안정 가용 영역을 찾아서 복제를 수행한다.
이를 통해서 `재해 복구`(disaster recovery)를 구현할 수 있다.
#### 읽기 전용
읽기 전용 복사본 (read replica)는 데이터를 "읽기 위한" 데이터베이스 복제본이다.
따라서 읽기 이외의 작업은 수행할 수 없다.
왜 읽기 전용 데이터베이스를 복사할까?
데이터베이스의 대부분 요청은 읽기 요청이기 때문이다.

읽기 전용으로 만들 수 있는 복제본의 한계는 최대 5개이다. - MySQL는 5개이다. 최대 15개까지 가능함.
[Amazon RDS for MySQL, MariaDB 및 PostgreSQL에서는 DB 인스턴스당 최대 15개의 읽기 전용 복제본을 추가할 수 있습니다. Amazon RDS for Oracle 및 SQL Server에서는 DB 인스턴스당 최대 5개의 읽기 전용 복제본을 추가할 수 있습니다.](https://aws.amazon.com/ko/rds/features/read-replicas/)
# 캐시
엘라스틱 캐시 (ElasticCache)는 RDS에서 운영은 아니지만, RDS 성능 개선을 위해 알아두면 좋다.
데이터베이스보다 훨씬 빠르다.
엘라스틱 캐시는 클라우드 내에서 인메모리를 만들어서 요청이 들어오면 캐시에 저장된 데이터를 불러온다.
데이터베이스와 캐시의 정합서을 맞추는 것은 굉장히 중요하다.
#### 맴캐시드
맴캐시드 (memcached)는 오픈소스임, 분산 메모리 캐싱 시스템이다.
메모리 사용량에 있어서 문자열 자료형을 처리하는데 주로 사용한다. 즉 텍스트 기반 데이터를 다룰 때 사용하면 좋다.
장점은 오토스케일링과 같이 크고 줄어드는게 가능하다.
#### 레디스
레디스(redis)는 복합한 데이터 타입(리스트, 해시 테이블 등)을 메모리에 저장할 수 있다.
정렬을 해야하거나 실시간으로 업데이트 되는 '리더보드 데이터'를 사용할 때 레디스는 좋은 선택이 된다.
또한 다양한 애플리케이션 (데이터베이스, Amazon SNS Messaging System)에서 사용되고, 다중 가용 영역을 포함한다.

# 실습
[CLI 명령들](https://docs.aws.amazon.com/ko_kr/cli/latest/userguide/cli_rds_code_examples.html)
```sh
aws rds create-db-instance \
    --db-instance-identifier test-mysql-instance \
    --db-instance-class db.t3.micro \
    --engine mysql \
    --master-username admin \
    --master-user-password secret99 \
    --allocated-storage 20
```
![[스크린샷 2024-05-24 오후 9.49.32.png]]
RDS가 만들어지게된다.
>[!info]
>  * --db-instance-identifier
> 	 * db 이름
>  * --db-instance-class
> 	 * db 성능
>  * --engine
> 	 * 어떤 db엔진을 사용할 것인지?
> 		 * MySQL, Postgresql
>  * --master-username
> 	 * admin 계정 이름
>  * --master-user-password
> 	 * admin 계정 비밀번호
>  * --allocated-storage
> 	 * storage 용량
> 	 * GiB 단위


# 참고
- [AWS RDS 예상 비용 계산법](https://www.ibm.com/docs/ko/tarm/8.12.3?topic=rds-estimated-demand-costs-aws-database-servers)
- [RDS Read Replicas와 RDS Multi AZ](https://velog.io/@alsry922/RDS-Read-Replicas%EC%99%80-RDS-Multi-AZ)