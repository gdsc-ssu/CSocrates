
트리에서,
항상 부모 노드가 모든 자식 노드보다 크면 "Max Heap"
항상 부모 노드가 모든 자식 노드보다 작으면 "Min Heap"

# Pop

```mermaid
graph TD;
    9-->7;
    9-->6;
    7-->1;
    7-->2;
    6-->3;
    6-->4;

```
```mermaid
graph TD;
    X-->7;
    X-->6;
    7-->1;
    7-->2;
    6-->3;
    6-->4;

```

```mermaid
graph TD;
    4-->7;
    4-->6;
    7-->1;
    7-->2;
    6-->3;

```
```mermaid
graph TD;
    7-->4;
    7-->6;
    4-->1;
    4-->2;
    6-->3;

```


# push (10)

```mermaid
graph TD;
    7-->4;
    7-->6;
    4-->1;
    4-->2;
    6-->3;
	6-->10;
```

```mermaid
graph TD;
    7-->4;
    7-->10;
    4-->1;
    4-->2;
    10-->3;
	10-->6;
```

```mermaid
graph TD;
    10-->4;
    10-->7;
    4-->1;
    4-->2;
    7-->3;
	7-->6;
```

삽입 : $log(N)$
삭제 : $log(N)$
정렬 : $Nlog(N)$

# 사용 방법

```c++
#include <queue>
#include <iostream>
using namespace std;
struct comp {
	bool operator()(int a, int b){
		return a>b;
	}
}
int main(){
	priority_queue<int> pq; // default : max heap
	priority_queue<int, vector<int>, greater<int>> mpq; // min heap
	priority_queue<int, vector<int>, comp> mpq2; // min heap

	pq.push(10);
	pq.pop();
	cout << pq.top() << '\n';
}
```