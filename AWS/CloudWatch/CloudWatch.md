### CloudWatch란?

**모니터링 및 관찰 기능 서비스**
	AWS에는 수 많은 리소스가 존재하는데, CloudWatch는 리소스 사용 및 이벤트 등을 실시간으로 모니터링함 

		※ 이벤트란 일련의 사 건을 의미하며 예를 들면 S3 버컷에 파일을 업로드 (puT), 혹은 수정 (UPDATE)할 때 ‘이벤트가 발생했다’고 표현할 수 있음. 뿐만 아니라 암호화되지 않은 파일을 업로드할 때 접근 거부 에러 메시지가 뜨는 상황 역시 이벤트라 할 수 있음

![[Pasted image 20240629105506.png|400]]

**Public 서비스**
	인터넷을 통해 접근하거나 Interface Endpoint로 접근 가능

![[Pasted image 20240629110036.png|500]]
![[Pasted image 20240629113721.png|500]]

**로그, 지표, 이벤트 등의 운영데이터를 수집하여 시각화 및 처리**
	경보 생성을 통해 자동화된 대응 가능


### CloudWatch 모니터링 종류

**기본 모니터링**
- 기본 모니터링(basicmonitoring)은 무료이며 5분 간격으로 최소한의 데이터를 수집하고 사용자에게 이벤트 발생 여부를 알려줌
- 주로 CPU 시용량, 디스크 사용량, 네트워크 r/o 처리량 관련 상황을 체크할때 시용되는 모니터링 종류
- AWS 리소스 사용시 ELB와 RDS를 제외하고 디폴트로 기본 모니터링 종류가 사용

**상세 모니터링**
- 상세 모니터링(detailed monitoring)은 무료가 아니지만 1분 간격으로 매우 자세한 데이터를 수집함
- 대부분의 리소스는 기본 모니터링에서 상세 모니터링으로 변경 가능하나, ELB와 RDS는 상세 모니터링 옵션이 디폴트로 선택되어 있으며 이 둘은 기본모니터링 기능을 사용 할 수 없음


### 주요 기능

![[Pasted image 20240629124325.png|500]]

- 지표 수집
	- 시간 순서별 데이터 요소의 집합
	- AWS 서비스/어플리케이션의 퍼포먼스를 모니터링하기 위해 지표 생성
		- ex) EC2 CPU, 네트워트, Disk IO
	- CloudWatch Agent/API를 통해 커스텀 지표 생성 가능
		- ex) EC2 메모리 사용량

- 경보
	- 수집된 지표에 따라서 알림 생성 가능

- 로그 수집 및 관리
	- Lambda, EC2, Route53, ECS등 여러 AWS 서비스의 로그를 수집
	- 수집된 로그를 Kinesis, S3등 다른 서비스/계정으로 전달 가능
	- 자체적으로 확인하거나 쿼리도 가능
		- CloudWatch상에서 수집된 로그를 직접 보거나 검색 가능하고, CloudWatch 인사이트 서비스를 통해서 대화형으로 쿼리 가능

- 대시보드
	- 수집한 로그/지표를 기반으로 대시보드 구성
	- 외부 리소스를 활용해서 커스텀 대시보드 구성 가능
		- S3 객체 표시, HTML 커스텀 그래프 표시

### CloudWatch 지표

지표에 대해 더 자세히 설명해보자면...

- 시간 순서대로 정리된 데이터의 집합 
	- 다수의 '데이터 포인트'로 구성
- AWS의 대부분의 서비스는 기본적으로 지표를 제공함
- 커스텀 지표 생성 가능
	- 유저가 직접 원하는 데이터 포인트를 생성해 CloudWatch로 전달하여 생성함
- 리전 단위
- 15개월 이후 사라짐
	- 지속적으로 새로운 데이터가 들어오면 15개월 이전의 데이터는 사라짐

**그럼 이 지표들은 무엇으로 구성되있나?**

- **네임스페이스
	- CloudWatch 지표의 컨테이너
		- 지표는 네임스페이스 단위로 나눠짐
	- 지표의 출신 혹은 성격에 따라 논리적으로 묶은 단위
	- AWS에서 수집하는 기본적인 지표는 AWS/{서비스명} 형식
		- ex) AWS/EC2, AWS/RDS
	- 직접 지표를 만들고 싶은 경우에는...
		- 네임스페이스는 필수로 명시해야함 : 디폴트값 없음

- **지표 이름
	- 지표의 고유 이름
		- 무엇에 관한 지표인지를 나타냄
		- 필수임

- **데이터 포인트
	- 지표를 구성하는 시간-값 데이터 단위
		- 초단위 까지 구성됨
	- UTC 구성 권장
	- **데이터 포인트의 Resolution
		- 데이터가 얼마나 '자주' 수집되는지는 나타내는 개념
			- 기본적으로 60초 단위
			- high resolution 모드에서는 1초 단위로 수집 가능
	- **데이터 포인트의 기간
		- 데이터가 얼마만큼의 '시간 기준'으로 묶여서 보여지는지에 관한 개념
		- 초단위로 묶어서 보여줄 수 있음
			- 최소 1초에서 최대 86,400초(1일)까지 가능
		- 보관 기간
			- 60초 미만은 최대 3시간까지 보여질 수 있음
			- 60초는 15일
			- 300초는 63일
			- 1시간은 455일(15개월)
			- 이 보관 기간은 사라지는 시간이 아님
				- 작은 단위의 보관 기간은 큰 단위로 계속 합쳐짐
					- 1분 단위는 15일 동안만 확인 가능, 이루 15일이 지나면 5분 단위로만 확인 가능함
					- 묶을 수 있는 데이터의 단위가 달라지는 것임
		- 주의 사항
			- 2주 이상 데이터가 업데이트 되지 않은 지표의 경우 콘솔에 보이지 않음
				- 모든 콘솔에서 사라지고 CLI로만 확인이 가능함
				
- **차원(Dimension)
	- 일종의 태그/카테고리
		- 키-벨류로 구성됨
		- 지표를 구분할때 사용
	- 최대 30개까지 할당 가능
	- ex) AWS/EC2 네임스페이스에 모든 EC2의 지표가 수집되는데 어떤 인스턴스에서 이 지표가 왔는지 구분할 필요가 있음. 이를 차원을 통해 구분
		- instanceID(키) Dimension를 통해 EC2 인스턴스 단위로 구분해서 확인
	- 조합 가능
		- ex) Dimension : (Server=prod, Domain=Seoul) or (Server=dev)
			- 서버가 prod이면서 도메인은 서울인 상태에서 발생된 지표이거나 서버가 dev인 지표
			- 이런식으로 조건을 걸어서 지표 확인 가능


![[Pasted image 20240629131935.png]]
(빨간 점이 데이터 포인트)


![[Pasted image 20240629132344.png]]
직접 커스텀 지표를 만든 경우 -> EC2 메모리 사용량을 알기 위한 지표

커스텀 지표도 기본 지표와 동일하게 데이터 포인트가 업데이트 됨
다른점은 커스텀 지표는 namespace가 사용자 마음대로라는 점, 그리고 여러가지 dimension을 넣을 수 있다는 점이 있음

### CloudWatch 경보

위 지표를 활용하는 대표적인 방법

**CloudWatch 경보는 CloudWatch 지표가 일정 시간 동안 지정된 값을 초과할 경우 작업을 수행함**
예를 들어 오전 9시까지 출근인데 야근으로 인해 새벽에 잠들었다고 하자. 이때 알람을 맞추지 않는다면 지각할게 뻔함
그러므로 오전 7시에 알람을 맞춰, 오전에 알람소리에 맞춰 일어나서 밥을 먹고 씻고 해서 오전 9시까지 출근을 함
여기서 오전 7시란 임의로 정해놓은 시간이고 기상 후 출근 과정을 '이벤트'라고 생각해보자
이렇게 한 사람의 일상은 알람이 울린 후 모두 일어난다는 걸 알 수 있음

보편적으로 기상후 씻고 조식을 하는 것은 거의 자동으로 일어나는 일임. 
CloudWatch 경보를 통해 이벤트를 발생시켜 개발자의 개입을 최소화하며 자동화 시스템을 구축할 수 있음

**경보의 세가지 상태**
- OK
	- CloudWatch에서 수집하는 매트리스가 개발자가 지정해놓은 임켓값에서 타당한 값으로 들어온다면 OK 상태가 뜸
	- 경보가 울릴 펼요 없는 '정상적인 상태'를 의미
- ALARM
	- OK 상태에서 임계값을 벗어난 상태
	- '알람 상태'를 의미
	- 여기서 개발자는 경보가 울렸을 경우 취할 수 있는 행동을 정의할 수 있음
- INSUFFICIENT_DATA
	- OK 혹은 ALARM으로 구분 지을 수 있을 만큼 충분한 데이터가 쌓이지 않거나 전달받지 못했을 경우
	- 예를 들어 IoT 기기에서 매초 데이터를 전달받아야 하는데 알 수 없는 방해 요인으로 데이터 전송 지연이 발생하여 CloudWatch는 데이터가 쌓이지 않고 있다고 판단하면 불충분 데이터라고 알려줌

**다양한 방법으로 대응 가능**
- SNS로 Lambda 실행, 이메일 전달 등
- 예시로 웹서버의 500에러가 일정수치 이상일때 슬랙 알림을 받아볼 수 있음

**지표의 Resolution에 따라 경보의 평가 주기 변동**
- high resolution이라면 60초 미만 주기로 평가 가능
- 이외에는 모두 60초의 배수 단위로 평가

![[Pasted image 20240629133303.png]]


### CloudWatch 사용 사례

- 사례 1 서버 과부하 문제 해결
	- 쇼핑앱을 하나 만들었고 매일 전세계에서 얼마나 많은 유저가 앱을 사용히는지 알아야한다고 할때, 특정 요일과 시간별로 나눠서 언제 유저가 많이 몰리는지 패턴을 분석 해야 함 
	- 만약 공휴일에 비정상적으로 유저가 많이 몰리면 서버 과부하 문제가 발생하며 수많은 트래핀으로 인해 병목 현상이 일어날 수 있음
	- 그러나 매일 개발자가 확인하는 것은 불가능
	- 따라서 CloudWatch를 통해 언제 얼마나 많은 사람이 엠에 접속했는지 로그와 매트리스를 통해 한눈에 확인할 수 있으며, 이를 기반으로 앱 사용 패턴을 파악하고 병목 현상 문제를 유연하게 대처할 수 있음
	
- 사례 2 비용 절감 효과
	- EC2 인스턴스에서 호스팅하고 있는 웹 서버의 상태를 점검하며 사용량에 따라 비용을 절감 하는 목표를 가지고 있다고 할때, 같은 비용을 지불하면서 AWS 리소스를 사용하게 된다면 낮과 밤시간에 필요한 서버의 성능이 달라지며 궁극적으로 금전적 손실이 발생
	- 트래픽이 거의 없는 밤에 서버의 성능을 자동으로 낮출 수 있다면 얼마나 좋을까?
	- CloudWatch 경보 기능을 활용하면 서버 트래픽이 특정 임계점에 도달했을 때 개발자에게 알람을알려주고, 성능을 자동으로 낮출수 있음


### CloudWatch 실습

**EC2 인스턴스의 CPU/메모리 시각화해서 확인하기

먼저 EC2에 적용할 역할 생성

![[Pasted image 20240629192437.png]]

그 후, EC2 생성

![[Pasted image 20240629193921.png]]

IAM 인스턴스 프로파일에 위에서 생성한 역할을 적용하면 됨

그 후, 이 EC2에 Cloudwatch Agent를 설정하고 AMI로 만들어서 대시보드로 보기 위한 작업을 진행해보자

System Manager -> 명령 실행에서 아래 명령을 실행함

![[Pasted image 20240629194155.png]]

이름과 인스턴스를 선택해줌

![[Pasted image 20240629194331.png]]

그 후 파라미터 생성

![[Pasted image 20240629194513.png]]

값란에 다음 코드 입력
```json
{

"agent": {

"metrics_collection_interval": 10,

"logfile": "/opt/aws/amazon-cloudwatch-agent/logs/amazon-cloudwatch-agent.log"

},

"metrics": {

"namespace": "CWAgent",

"metrics_collected": {

"cpu": {

"resources": ["*"],

"measurement": [

{

"name": "cpu_usage_idle",

"rename": "CPU_USAGE_IDLE",

"unit": "Percent"

},

{

"name": "cpu_usage_nice",

"unit": "Percent"

},

"cpu_usage_guest"

],

"totalcpu": **false**,

"metrics_collection_interval": 10,

"append_dimensions": {

"customized_dimension_key_1": "customized_dimension_value_1",

"customized_dimension_key_2": "customized_dimension_value_2"

}

},

"disk": {

"resources": ["/", "/tmp"],

"measurement": [

{

"name": "free",

"rename": "DISK_FREE",

"unit": "Gigabytes"

},

"total",

"used"

],

"ignore_file_system_types": ["sysfs", "devtmpfs"],

"metrics_collection_interval": 60,

"append_dimensions": {

"customized_dimension_key_3": "customized_dimension_value_3",

"customized_dimension_key_4": "customized_dimension_value_4"

}

},

"diskio": {

"resources": ["*"],

"measurement": ["reads", "writes", "read_time", "write_time", "io_time"],

"metrics_collection_interval": 60

},

"swap": {

"measurement": ["swap_used", "swap_free", "swap_used_percent"]

},

"mem": {

"measurement": ["mem_used", "mem_cached", "mem_total", "mem_used_percent"],

"metrics_collection_interval": 60

},

"net": {

"resources": ["eth0"],

"measurement": ["bytes_sent", "bytes_recv", "drop_in", "drop_out"]

},

"netstat": {

"measurement": ["tcp_established", "tcp_syn_sent", "tcp_close"],

"metrics_collection_interval": 60

},

"processes": {

"measurement": ["running", "sleeping", "dead"]

}

},

"append_dimensions": {

"ImageId": "${aws:ImageId}",

"InstanceId": "${aws:InstanceId}",

"InstanceType": "${aws:InstanceType}",

"AutoScalingGroupName": "${aws:AutoScalingGroupName}"

},

"aggregation_dimensions": [["ImageId"], ["InstanceId", "InstanceType"], ["d1"], []],

"force_flush_interval": 30

},

"logs": {

"logs_collected": {

"files": {

"collect_list": [

{

"file_path": "/opt/aws/amazon-cloudwatch-agent/logs/amazon-cloudwatch-agent.log",

"log_group_name": "MyEc2InstanceAgentLog.log",

"log_stream_name": "MyEc2InstanceAgentLog.log",

"timezone": "LOCAL"

}

]

}

},

"log_stream_name": "my_log_stream_name",

"force_flush_interval": 15

}

}

```

또 다른 명령 실행

![[Pasted image 20240629194718.png]]

![[Pasted image 20240629195214.png]]

configure location에 이전에 만들었던 파라미터 이름을 사용

여기서 CloudWatch -> EC2 리소스 상태를 가보면 리소스 상태를 확인할 수 있음

![[Pasted image 20240629195626.png]]

메모리 사용은 아직 확인할 수 없는데, 아직 CW Agent에서 메모리 값을 주지 않아서 그럼(5분마다 확인 가능)

EC2 부하 테스트를 위해 stress 툴을 설치해서 이미지와 템플릿을 연결하면...

![[Pasted image 20240629200339.png]]


### reference
https://www.youtube.com/watch?v=0vg9nxohKzo
AWS 입문