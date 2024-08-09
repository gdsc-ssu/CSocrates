
# Disjoint Set (Union Find)
#### 개념
- 공통 원소가 없는 여러 개의 집합을 효율적으로 관리하기 위한 자료구조이다. 
- 두 원소가 같은 집합에 속하는지 판별하거나, 두 집합을 하나로 합치는 연산을 빠르게 수행할 때 사용한다. 

#### 기본 연산

3가지의 연산이 있다. 
1. **MakeSet(x)** : 원소 x만을 포함하는 새로운 집합을 생성한다. 초기에는 각 원소가 자신만을 포함하는 집합의 대표로 설정이 된다. 
2. **Find(x)** : 원소 x가 속한 집합의 대표를 찾는다. 
	- 대표를 왜 찾아? -> 대표가 집합을 식별하는데 사용되기 때문
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Disjoint%20Set%20/%20Pasted%20image%2020240306164804.png)
		
3. **Union(x, y)**: 두 원소 x와 y가 포함된 집합을 합친다. 
	1. 두 집합의 대표를 찾는다. 
	2. 한 대표를 다른 대표에 연결하여 두 집합을 하나로 합치는 과정을 포함한다. 
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Disjoint%20Set%20/%20Pasted%20image%2020240306165121.png)

#### 최적화 기법
- 위 그림처럼 Union을 하는 과정에서 선형 트리가 생겨버릴 수도 있다. 
- Union과 Find 연산의 성능은 ==트리의 높이에 의존==하기 때문에 트리의 높이를 최소화 해야한다. 

**경로 압축(Path Compression)**
Find 연산을 수행하면서 만나는 모든 노드가 직접 대표를 가리키도록 만든다. 
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Disjoint%20Set%20/%20Pasted%20image%2020240306165652.png)

**랭크 기반 합치기(Union by Rank)**
- 두 트리를 합칠 때, 더 낮은 랭크를 가진 트리를 더 높은 랭크를 가진 트리 밑에 붙인다. 
- 트리의 높이나 사이즈를 저장할 rank 배열 사용
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Disjoint%20Set%20/%20Pasted%20image%2020240306165955.png)

**크기 기반 합치기(Union by Size)**
- 랭크 대신 트리의 노드 수(크기)를 기준으로 Union을 수행한다. 
- 더 작은 트리를 더 큰 트리 밑에 붙여 전체 트리의 구조를 가능한 평평하게 유지하는 데 초점을 맞춘다. 


Path Compression + Union by Rank 
```python
class DisjointSet:
    def __init__(self, size):
        self.parent = list(range(size))
        self.rank = [0] * size

    def find(self, x):
        if self.parent[x] != x:
            # 경로 압축(Path Compression)을 사용하여 트리의 높이 최소화
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        rootX = self.find(x)
        rootY = self.find(y)

        if rootX != rootY:
            if self.rank[rootX] > self.rank[rootY]:
                self.parent[rootY] = rootX
            elif self.rank[rootX] < self.rank[rootY]:
                self.parent[rootX] = rootY
            else:
                # 두 트리의 랭크가 같을 경우 하나를 선택하고 랭크를 1 증가
                self.parent[rootY] = rootX
                self.rank[rootX] += 1

# 사용 예시
if __name__ == "__main__":
    # 5개의 원소가 있는 디스조인트 셋 생성
    ds = DisjointSet(5)

    # 몇 가지 합치기 연산 수행
    ds.union(0, 1)
    ds.union(1, 2)
    ds.union(3, 4)

    # 원소가 같은 집합에 속하는지 확인
    print(ds.find(0) == ds.find(2))  # True, 0과 2는 같은 집합에 속함
    print(ds.find(0) == ds.find(3))  # False, 0과 3은 다른 집합에 속함

```

#### 사용 사례

- **네트워크 연결 확인**: 네트워크 내에서 두 노드가 서로 연결되어 있는지 여부를 판단하는 데 사용할 수 있습니다. 두 노드가 같은 집합에 속해 있으면 연결되어 있다고 간주할 수 있습니다.

-  **최소 신장 트리 생성**: 크루스칼 알고리즘과 같은 최소 신장 트리(MST) 알고리즘에서 사용됩니다. 간선을 가중치의 오름차순으로 추가하면서 사이클을 형성하지 않는 간선만을 선택하여 MST를 구성합니다.

- **사이클 감지**: 그래프 내에서 사이클을 감지하는 데 사용됩니다. 무방향 그래프에서 간선을 하나씩 추가하면서 두 노드가 이미 같은 집합에 속해 있는지 확인합니다. 같은 집합에 속한다면, 그 간선을 추가하면 사이클이 형성됩니다.



<hr>
#### 참조
https://yoongrammer.tistory.com/102


