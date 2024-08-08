## 균형 이진 탐색 트리
- 노드의 입력과 삭제가 일어날 때 균형을 유지하도록 하는 트리
- 기본적으로 정렬된 상태를 유지하면서 연산을 효과적으로 수행하게 해준다.

### 나오게 된 이유
- 보통의 이진 탐색트리에서 새로운 노드가 삽입이 될 때, 부모의 노드보다 작은값은 왼쪽, 큰 값은 오른쪽으로 추가됨.
  -> 이렇게 추가하다가 자료가 많아질수록 트리의 높이가 커지기 때문에 최악의 경우 특정 노드를 탐색하는데 O(n)이 소요됨
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Balanced%20Binary%20Search%20Tree%20%28AVL%2C%20Red-Black%20Tree%29%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-02-23%20%EC%98%A4%ED%9B%84%204.16.07.png)
-> 이렇게 편향 이진 트리가 나올 경우 성능면에서 최악의 경우가 되어버림
-> 이러한 점을 피하기 위해서 균형 이진 트리가 나오게 됨.

## AVL 트리
- Adelson-Velskii Landis Tree
- 1962년에 Adelson-Velskii와 Landis에 의해 고안

### 특징
- 오른쪽 자식 트리의 높이 차이가 최대 1이 되도록 유지함으로써 균형 맞춤.
> 노드의 balance factor
> 임의의 노트 x에 대해서
> BF(x) = h(ISubtree(x)) - h(rSubtree(x))
- 트리의 모든 노드들의 BF(x)는 -1, 0, 1 중에 하나여야한다.
	-> 만약 만족하지 않을 경우 재배치에 들어간다.


### 균형이 깨지는 4가지 상황
1. RR
	- Right-Right, 특정 노드를 기준으로 오른쪽 오른쪽으로 편향된 경우
	- 왼쪽으로 한번 회전해서 해결

![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Balanced%20Binary%20Search%20Tree%20%28AVL%2C%20Red-Black%20Tree%29%20/%20Pasted%20image%2020240223173200.png)

2. LL
	- Left-Left 특정 노드를 기준으로 왼쪽 왼쪽으로 편향된 경우
	- 오른쪽으로 한번 회전해서 해결
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Balanced%20Binary%20Search%20Tree%20%28AVL%2C%20Red-Black%20Tree%29%20/%20Pasted%20image%2020240223173157.png)

3. LR
	- Left-Right 특정 노드를 기준으로 왼쪽 오른쪽으로 편향된 경우
	- RR회전 후 LL회전으로 해결

![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Balanced%20Binary%20Search%20Tree%20%28AVL%2C%20Red-Black%20Tree%29%20/%20Pasted%20image%2020240223173210.png)

4. RL
	- Right-Left 특정 노드를 기준으로 오른쪽 왼쪽으로 편향된 경우
	- LL회전 후 RR회전으로 해결 

![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Balanced%20Binary%20Search%20Tree%20%28AVL%2C%20Red-Black%20Tree%29%20/%20Pasted%20image%2020240223173214.png)

### 장점
- 삽입, 검색, 삭제의 최악의 케이스에서도 (BST의 선형 형태에서도) O(logN)이다.

### 단점
- 구현이 어렵다.
- 재균형을 잡는 시간이 든다.


## Red black tree
- 1978년 레오 귀바스와 로버트 세지윅이 만듦
- 자가 균형 이진 탐색 트리의 한 종류

![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Balanced%20Binary%20Search%20Tree%20%28AVL%2C%20Red-Black%20Tree%29%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-02-23%20%EC%98%A4%ED%9B%84%206.58.37.png)
### 특징
1. 모든 노드는 red 혹은 black이다
2. 루트 노드는 black이다
3. nil 노드라는것이 존재 (모든 nil 노드는 black이다)
	- nil 노드란 자녀가 없을 때 "**존재하지 않음을 의미하는 노드**"라는 의미로 표시
	- 값이 있는 노드와 ==동등하게== 취급
	-> 즉 Red Black Tree에서는 리프노드는 nil노드이다
4. red의 자녀들은 반드시 black이다 (red는 연속적으로 존재할 수 없다)
5. 임의의 노드에서 자손 nil 노드들까지 가는 경로들의 black 수는 같다 (자기 자신은 카운트에서 제외)
	- 또한 모든 자식노드의 색과 부모의 색을 바꾸더라도 만족한다
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Balanced%20Binary%20Search%20Tree%20%28AVL%2C%20Red-Black%20Tree%29%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-02-23%20%EC%98%A4%ED%9B%84%207.02.57.png)

> **black height**
> 노드 x에서 임의의 자손 nil 노드까지 내려가는 경로에서의 black 수

> 노드를 삽입할 시 그 노드는 red이다.
> 그 이유는 제일 까다로운 5번째 속성을 만족하기 위해서.

### 균형이 깨지는 상황
#### 삽입
 - 첫 노드 삽입 시 red 루트노드가 red
	-> 루트 노드를 black으로 바꿔준다.

1. 노드 삽입 후 double red 발생하였는데 (부모 노드의 형제 노드가 red 일때)  
    -> Recoloring 진행  
    삽입한 노드의 부모와 부모의 형제 노드를 black 으로 변경  
    부모의 부모 노드를 red로 변경, 부모의 부모 노드가 root 인지 double red인지에 따라 조정 진행
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Balanced%20Binary%20Search%20Tree%20%28AVL%2C%20Red-Black%20Tree%29%20/%20Pasted%20image%2020240223193154.png)

2. 노드 삽입 후 dobule red 발생(부모 노드의 형제 노드가 black 이거나 없을때)  
    -> Restructuring 진행  
    조정 대상 : 삽입한 노드, 부모 노드, 부모의 부모 노드  
    조정 대상 노드들을 오름차순 정렬  
    가운데 노드를 부모 노드로 선정하고 black으로 변경  
    나머지 두 노드를 자식 노드로 두고 red로 변경

![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Balanced%20Binary%20Search%20Tree%20%28AVL%2C%20Red-Black%20Tree%29%20/%20Pasted%20image%2020240223192557.png)

#### 삭제
- 삭제되는 색이 중요함.
	- 만약 삭제하려는 노드의 자식이 없거나 한 개일 경우 -> 삭제되는 노드의 색
	- 만약 삭제하려는 노드의 자식이 두 개일 경우 -> 삭제 후 대체되는 노드의 색
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Balanced%20Binary%20Search%20Tree%20%28AVL%2C%20Red-Black%20Tree%29%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-02-23%20%EC%98%A4%ED%9B%84%208.44.41.png)

-> 삭제되는 색이 빨간색이면? 어떠한 속성도 위반하지 않는다

1. 지워진 노드가 red 경우 
	- 아무일도 일어나지 않음

![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Balanced%20Binary%20Search%20Tree%20%28AVL%2C%20Red-Black%20Tree%29%20/%20Pasted%20image%2020240223203945.png)

##### 삭제되는 색이 검은색이라면?
- 거의 대부분 5번째 속성을 만족시키지 못한다.
> extra black 부여
> 속성을 다시 만족시키기 위해 삭제된 색의 위치를 대체한 노드에 extra black을 부여

![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Balanced%20Binary%20Search%20Tree%20%28AVL%2C%20Red-Black%20Tree%29%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-02-23%20%EC%98%A4%ED%9B%84%208.55.06.png)
-> 10을 지운 후
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Balanced%20Binary%20Search%20Tree%20%28AVL%2C%20Red-Black%20Tree%29%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-02-23%20%EC%98%A4%ED%9B%84%208.55.26.png)


2. 삭제 대상 노드가 black, 그 자리에 오는 노드가 black인 경우

2-1 이중 흑색 노드의 형제 노드가 black 이고, 형제의 양쪽 자식 모두 black인 경우
	- 형제 노드를 red로 변경  
	- 이중 흑색 노드의 검은색 1개를 부모 노드로 전달  
	- 부모가 root가 아닌 이중 흑색 노드가 되면 해당 case 반복 진행
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Balanced%20Binary%20Search%20Tree%20%28AVL%2C%20Red-Black%20Tree%29%20/%20Pasted%20image%2020240223204031.png)
	
2-2 이중 흑색 노드의 형제 노드가 red인 경우  
	- 형제 노드를 black으로 변경  
	- 부모 노드를 red로 변경  
	- 부모 노드를 기준으로 왼쪽으로 회전  
	- 그 다음 2번에 따라 반복 진행

![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Balanced%20Binary%20Search%20Tree%20%28AVL%2C%20Red-Black%20Tree%29%20/%20Pasted%20image%2020240223210358.png)

2-3 이중 흑색 노드의 형제 노드가 black이고, 오른쪽 자식이 red인 경우  
	- 부모 노드와 형제 노드의 오른쪽 자식 노드를 검은색으로 변경  
	- 부모 노드를 기준으로 왼쪽으로 회전

![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Balanced%20Binary%20Search%20Tree%20%28AVL%2C%20Red-Black%20Tree%29%20/%20Pasted%20image%2020240223210122.png)

2-4 이중 흑색 노드의 형제 노드가 black이고, 왼쪽 자식이 red인 경우  
	- 형제 노드를 red로 변경  
	- 형제 노드의 왼쪽 자식 노드를 black으로 변경  
	- 형제 노드를 기준으로 오른쪽으로 회전

![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Balanced%20Binary%20Search%20Tree%20%28AVL%2C%20Red-Black%20Tree%29%20/%20Pasted%20image%2020240224120424.png)


### AVL과 레드블랙트리의 차이
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Balanced%20Binary%20Search%20Tree%20%28AVL%2C%20Red-Black%20Tree%29%20/%20%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202024-02-23%20%EC%98%A4%ED%9B%84%208.37.48.png)

### red-black tree에 대한 설명영상
https://www.youtube.com/watch?v=2MdsebfJOyM