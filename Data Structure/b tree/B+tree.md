# 목차
- [[#b+tree란?]]
- [[#내부 연산]]
- [[#B-tree VS B+tree]]
- [[#참고사항]]
# b+tree란?
B+트리는 B-트리의 변형으로, 모든 값을 리프 노드에 저장하고, 내부 노드는 데이터 포인터(리프 노드를 가리키는 키)만을 저장한다. 
1. **모든 값은 리프 노드에 저장된다.**
	1. 이로 인해 검색, 삽입, 삭제 작업이 효율적으로 이루어질 수 있으며, 리프 노드들은 링크드리스트로 연결되어 있어 순차 접근이 용이하다.
2. **균형 트리 구조**
	1. B+트리는 모든 리프 노드가 같은 깊이를 가지는 균형 트리이다.
	2. 이는 모든 검색, 삽입, 삭제 작업이 일정한 시간 안에 이루어질 수 있음을 보장한다.
4. **분할 및 병합을 통한 동적 조정**
	1. 새로운 키가 삽입되거나 기존 키가 삭제될 때, B+트리는 자동으로 노드를 분할하거나 병합하여 트리의 균형을 유지한다.
	2. 이 과정에서 오버플로우나 언더플로우가 발생하면, 인접한 노드와의 재분배 또는 부모 노드와의 병합을 통해 처리한다.
5. **효율적인 범위 검색**
	1. 리프 노드가 연결 리스트로 구성되어 있기 때문에, 특정 범위의 데이터를 찾는 것이 매우 효율적입니다.
	2. 시작 키에 해당하는 리프 노드를 찾은 뒤, 연결된 리스트를 따라가며 필요한 모든 데이터를 순차적으로 접근할 수 있습니다.
DB index 같은 경우에 B-tree보다 B+tree 형태를 많이 사용한다. (leaf node에서 모든 데이터를 탐색할 수 있기 때문에)

#### 장단점
- 장점
	- **`효율적인 탐색`** : B+ 트리는 **균형 잡힌 트리**로서, 모든 리프 노드까지 도달하기 위한 경로의 길이가 동일합니다.(데이터 탐색 시간복잡도 O(log N))
	- **`범위탐색 유리`**: leaf 노드끼리 **연결 리스트**로 연결되어 있어서 범위 탐색에 매우 유리함
	- **`순차 액세스 성능`**: B+ 트리의 리프 노드는 **연결 리스트**로 구성되어 있으며, **`순차 액세스(Sequential Access)`**를 지원합니다.
- 단점
	- B-tree의 경우 최상 케이스에서는 루트에서 끝날 수 있지만, B+tree는 무조건 leaf 노드까지 내려가봐야 함
	- **`메모리 요구량`**: B+ 트리는 대부분의 중간 노드를 메모리에 유지해야 하므로, 메모리 요구량이 크다는 단점이 있습니다. 트리의 크기가 커질수록 메모리 사용량도 증가하므로, 메모리 제약이 있는 환경에서는 문제가 될 수 있습니다.
	- **`공간 사용 비효율성`**: B+ 트리는 각 노드마다 포인터와 키 값을 저장해야 합니다. 이로 인해 트리의 크기가 실제 데이터 크기보다 커지며, 디스크 공간의 낭비를 초래할 수 있습니다.
## 내부 연산

#### 삽입
-  **key의 수가 최대보다 적은 leaf node에 삽입하는 경우**
해당 node의 가장 앞이 아닌 곳에 삽입되는 경우는 단순히 삽입해 주면 된다.
> 하지만, leaf node의 가장 앞에 삽입되는 경우는, 해당 node를 가리키는 부모 node의 포인터의 오른쪽에 위치한 key를 K로 바꿔준다. 그리고 leaf node끼리 Linked list로 이어줘야 하므로 삽입된 key에 Linked list로 연결한다.

![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/B%2Btree%20/%20Pasted%20image%2020240309101737.png)

-  **key의 수가 최대인 leaf node에 삽입하는 경우**
key의 수가 최대이므로 삽입하는 경우 분할을 해주어야 한다. 만약 중간 node에서 분할이 일어나는 경우는 B-Tree와 동일하게 해주면 된다.
> leaf node에서 분할이 일어나는 경우는 중간 key를 부모 node로 올려주는데 이때, 오른쪽 node에 중간 key를 붙여 분할한다. 그리고 분할된 두 node를 Linked List로 연결해준다.

![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/B%2Btree%20/%20Pasted%20image%2020240309101925.png)
#### 삭제
- **삭제할 key가 leaf node의 가장 앞에 있지 않은 경우**
B-tree와 동일한 방식으로 삭제
- **삭제할 key가 leaf node의 가장 앞에 위치한 경우**
leaf node가 아닌 node에 key가 중복해서 존재한다. 따라서 해당 key를 노드보다 오른쪽에 있으면서 가장 작은 값으로 바꿔주어야 한다.
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/B%2Btree%20/%20Pasted%20image%2020240309102030.png)

#### 검색
구현하는 방식에 따라 다르겠지만, leaf 노드가 아닌 노드는 자신의 값이 자신의 오른쪽 자식의 가장 왼쪽 키 보다 크거나 같은 값으로 구성되어 있는 기준을 잘 보고 따라가면 된다.
단, 무조건 leaf 노드까지 도달해야 해당 값이 존재하는지 파악할 수 있기에 모든 값에 대해서 빠른 접근을 보장하지는 않는다.
예시) 14를 탐색하는 상황
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/B%2Btree%20/%20Pasted%20image%2020240309102304.png)
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/B%2Btree%20/%20Pasted%20image%2020240309102309.png)
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/B%2Btree%20/%20Pasted%20image%2020240309102332.png)

결과적으로 구조가 변경되는 것을 최소화하기 위해서 작동한다. (숫자가 변경되는건 작은 변화, 트리의 구조가 변경되는건 큰 변화이기 때문에)

---
## B-tree VS B+tree
가장 큰 차이점은 B+tree는 leaf 노드가 아닌 경우에는 leaf 노드로 가기 위한 경로를 안내할 뿐, 그것이 데이터를 저장하는 값이 아니라는 것입니다.
이러한 특징 때문에 업데이트가 발생할 시, non-leaf 노드들의 값이 쉽게 변화할 가능성이 있습니다.
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/B%2Btree%20/%20Pasted%20image%2020240309090824.png)

## 참고사항
#### Visualization
https://www.cs.usfca.edu/~galles/visualization/BPlusTree.html
#### 코드
https://github.com/Jeongseo21/Data_structure---B_tree/blob/main/%5BData%20structure%5D%20B%20tree/%5BData%20structure%5D%20B%20tree/B%2Btree.c#L41
#### 문헌
- https://velog.io/@kyeun95/%EC%9E%90%EB%A3%8C%EA%B5%AC%EC%A1%B0-B-Tree%EB%9E%80#b-tree%EC%9D%98-%EC%82%AD%EC%A0%9C-%EA%B3%BC%EC%A0%95