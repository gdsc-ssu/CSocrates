## 참고자료
- https://codechacha.com/ko/singly-linked-list-java/
## Single Linked List란?
- Single Linked List란 데이터를 저장하기 위한 구조로, 데이터를 한 쪽으로만 탐색할 수 있도록 구성한 형태이다.
- 각 데이터가 저장된 객체를 `node`라고 지칭하고, 가장 첫 번째 node를 `head`라고 부른다.
- 한 쪽으로만 저장되고, 검색할 수 있기 때문에 검색 시간이 최대 `O(n)` {n은 노드의 개수} 이 소요된다.
## Array VS Linked List
- 우리가 흔하게 말하는 배열인 Array는 저장할 수 있는 데이터의 크기가 이미 지정된 상태로 만들어지는 자료구조이다.
- Linked List는 데이터 구조를 저장하는 단위인 node의 개수의 제한이 없는 형태이다.
- 데이터를 저장할 때 제한 없이 저장할 수 있고 삭제할 때 데이터를 빠르게 삭제할 수 있는 Linked List가 효율적이지만, 데이터를 탐색할 때에는 Array가 더 적은 시간이 소요된다.
## Double Linked List VS Single Linked List
- Single Linked List는 한 방향으로만 탐색이 가능하지만, Double Linked List는 양방향으로 탐색이 가능하다.
- Double Linked List는 node가 다음 node의 메모리 위치인 next 뿐만 아니라 이전 node의 메모리 위치인 prev도 저장하고 있다. 따라서 각 node의 크기가 Single Liked List보다 크다.
- 하지만 데이터를 삭제하는 방법에서 Single Linked List는 이전의 node를 기억하기 위한 포인터를 하나 더 저장하고 있어야하는 반면, Double Linked List는 다음, 이전 노드의 정보를 가져올 수 있음으로 추가적인 변수를 선언하지 않아도 된다.
## 예제
```c
struct node {
	int data;
	struct node *next;
};
```
현재 데이터가 들어가는 부분을 data 영역, 그리고 다음 node를 가리키는 포인터를 next로 선언한다.
data의 타입은 원하는 타입으로 지정한다.
마지막 node의 next 값은 NULL 혹은 HEAD의 메모리 주소로 설정한다.
## 과정
#### 추가
![[스크린샷 2024-02-16 오후 5.47.14.png]]
- 데이터를 추가하는 방법은 2가지가 있다.
	1. 리스트의 맨 마지막에 추가하기
	2. 리스트의 맨 앞에 추가하기
- 1번의 경우
	- 맨 마지막에 추가하는 경우에는 임시 포인터를 생성하여 마지막 노드까지 이동하고, 마지막 노드의 next 값을 새로운 노드로 만들어준다.
- 2번의 경우
	- 맨 앞에 추가하는 경우에는 새로운 노드를 생성하고, HEAD의 포인터를 새로운 노드로 가리키게 된다.
#### 검색
- 전체 노드를 선형적으로 탐색한다.
	- 다른 노드에 대한 정보는 next에 대한 값만 있기 때문에
- 마지막 노드까지 탐색하고, 만약 탐색 중에 정보가 일치하는 값이 있다면 해당 값을 출력한다.
#### 삭제
- 데이터를 삭제하는 방법은 다음과 같다.
1. 원하는 데이터를 찾는 current 포인터와 current가 가리키는 노드의 이전 노드를 가리키는 prev 포인터를 선언한다.
2. 원하는 노드를 current로 설정한다.
3. prev의 next 값을 current의 next 값으로 한다면, 다음 탐색부터는 current가 가리키는 데이터는 탐색할 수 없다.
4. current로 저장된 노드를 메모리 해제해준다.

![[스크린샷 2024-02-16 오후 5.48.33.png]]