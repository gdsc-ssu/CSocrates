#binary_tree #이진트리

> 각각의 노드가 최대 두 개의 자식 노드를 가지는 트리 자료 구조

![](https://velog.velcdn.com/images/dlgosla/post/0faeb483-bc6f-4a83-93fc-dad54ffeed7a/image.png)
공백(노드가 없는 비어 있는 트리)이거나 루트와 왼쪽 서브트리, 오른쪽 서브트리라고 하는 두 개의 분리된 이진 트리로 구성된 노드의 유한 집합

##### 이진 트리 특징

- 한 노드가 최대 두 개의 가지만 가짐(최대 차수가 2)
- 왼쪽 서브트리와 오른쪽 서브트리를 구별(왼쪽/오른쪽이 서로 다르면 다른 트리, 방향을 구분)
- 0개의 노드를 가질 수 있음

##### 이진 트리 성질

- 레벨 i에서의 최대 노드 수 → ==2^(i-1)== (i≥1) 
	- ex) i=4(레벨 4에서만의 최대 노드 수), 2^3=8개
- 깊이가 k인 이진 트리가 가질 수 있는 최대 노드 수 → ==2^k-1== (k≥1)
	- 깊이 : 높이의 최대 레벨
	- ex) 깊이 3에서의 최대 노드 수는 2^3-1 = 7개

---
##### 이진 트리 종류

- 포화 이진 트리(Full Binary Tree)
	- 모든 레벨에 노드가 포화 상태로 차있는 트리
	- 깊이가 k일때 최대 노드 개수인 2^k -1 (k≥0)의 노드를 갖는 이진 트리
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/binary%20tree%20/%20%ED%8F%AC%ED%99%94%20%EC%9D%B4%EC%A7%84%20%ED%8A%B8%EB%A6%AC.jpeg)

- 완전 이진 트리(Complete Binary Tree)
	- 깊이가 k이고 노드 수가 n인 이진트리
	- 각 노드들이 깊이가 k인 포화 이진 트리에서 1부터 n까지 번호를 붙인 노드와 1대 1로 일치
		→즉, 1번부터 n까지 차례대로(순서대로) 노드 번호가 채워져 있는 것

- 편향 이진 트리(Skewed Binary Tree)
	- 높이사 k일 때 k개의 노드를 가지면서 모든 노드가 왼쪽이나 오른쪽 중 한 방향으로만 서브 트리를 가지고 있는 트리
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/binary%20tree%20/%20%ED%8E%B8%ED%96%A5%20%EC%9D%B4%EC%A7%84%20%ED%8A%B8%EB%A6%AC.jpeg)


#### 이진 트리의 표현

##### 배열을 활용한 표현

- 1차원 배열에 노드를 저장
- 번호 할당 기법으로 노드에 1부터 n까지 번호가 할당되므로 1차원 배열에 노드를 저장할 수 있음
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/binary%20tree%20/%20%EC%9D%B4%EC%A7%84%20%ED%8A%B8%EB%A6%AC%20%EB%B0%B0%EC%97%B4%20%ED%99%9C%EC%9A%A9.jpeg)
- **1차원 배열에서의 인덱스(i (1≤ i ≤ n) ) 관계**
	<n개의 노드를 가진 완전 이진 트리>
	
	- i ≠ 1이면 parent(i)는 ==|i/2|==의 위치에 있음
	- 2i ≤ n 이면 leftChild(i)는 ==2i==의 위치에 있음
	- 2i + 1 ≤ n이면 rightChild(i)는 ==2i + 1==의 위치에 있음

> 위 방법은 대부분의 경우 사용되지 않은 공간은 많을지 몰라도 어떤 이진 트리도 모두 나타낼 수 있음

![600](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/binary%20tree%20/%20%EC%9D%B4%EC%A7%84%20%ED%8A%B8%EB%A6%AC%20%EB%B0%B0%EC%97%B4%20%ED%99%9C%EC%9A%A9%20%EC%98%88%EC%8B%9C.jpeg)
*배열 표현 방법은 완전 이진 트리에 대해서는 상당히 좋지만, 다른 이진 트리에 대해서는 낭비가 매우 심함*

##### 연결 자료구조를 이용한 이진 트리의 표현

연결 자료구조를 사용한 이진트리의 표현은 배열 표현의 순차 표현의 부적절함(즉, 트리의 중간에 노드를 삽입하거나 제거하게 되면 노드의 레벨의 변경에 따라 많은 노드의 위치가 변해야하는 점)을 해결 가능함

![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/binary%20tree%20/%20%EC%97%B0%EA%B2%B0%20%EC%9E%90%EB%A3%8C%EA%B5%AC%EC%A1%B0%EB%A5%BC%20%EC%9D%B4%EC%9A%A9%ED%95%9C%20%EC%9D%B4%EC%A7%84%20%ED%8A%B8%EB%A6%AC%20%ED%91%9C%ED%98%84%20%EB%85%B8%EB%93%9C.jpeg)
*이러한 노드 구조에서는 노드의 부모를 알기 어렵다는 단점이 있지만 응용에 적합함*

![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/binary%20tree%20/%20%EC%97%B0%EA%B2%B0%20%EC%9E%90%EB%A3%8C%EA%B5%AC%EC%A1%B0%EB%A5%BC%20%EC%9D%B4%EC%9A%A9%ED%95%9C%20%EC%9D%B4%EC%A7%84%20%ED%8A%B8%EB%A6%AC%20%EC%98%88%EC%8B%9C.jpeg)


##### 이진 트리 용도

- 수식 트리
- 허프만 코딩 트리
- ==이진 검색 트리==
- 우선 순위 큐

#### 참고
(https://yoongrammer.tistory.com/69)