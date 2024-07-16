
## Kruskal

#### 개념
- 그래프의 최소 신장 트리(Minimum Spanning Tree, MST)를 찾는 대표적인 알고리즘
- 그래프 내의 모든 정점들을 가장 적은 비용으로 연결한다. 
- **모든 정점을 포함하고 사이클이 없는** 연결 선을 그렸을 때, **가중치의 합이 최소**가 되는 상황을 구하고 싶을 때 사용한다. 
- 가중치가 최소인 정점부터 MST에 포함시키기 때문에 그리디한 방식으로 볼 수 있다. 


![[Kruskal 1.gif]]

#### 원리
- **간선 정렬** 
	- 그래프의 모든 간선을 가중치에 따라 오름차순으로 정렬한다. 
- **초기화**
	- 모든 정점을 포함하는 디스조인트 셋(서로소 집합)을 초기화한다. 
	- 초기 단계에서는 각 저점이 자신만을 포함하는 집합이다. 
- **간선 선택 및 사이클 검사**
	- 정렬된 간선 리스트에서 순차적으로 간선을 선택한다. 
	- 선택한 간선이 현재 MST 후보에서 사이클을 형성하는지 Disjoin Set을 이용하여 확인한다. 
	- 사이클을 형성하지 않는다면 해당 간선을 MST 후보에 추가하고 두 정점을 포함하는 정점들을 합치기 위해 Disjoint Set의 union 연산을 수행한다. 
- **종료 조건**
	- 모든 정점이 연결되었을 때, 즉 MST 후보의 간선 수가 정점의 수보다 하나 적을 때 알고리즘을 종료한다. 

```python
class DisjointSet:
    def __init__(self, size):
        self.parent = [i for i in range(size)]
        self.rank = [0] * size

    def find(self, x):
        if self.parent[x] != x:
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
                self.parent[rootY] = rootX
                self.rank[rootX] += 1

def kruskal(graph, vertices):
    result = []  # 결과 리스트, 최소 신장 트리를 구성하는 간선들을 저장
    i, e = 0, 0  # i: 정렬된 간선의 인덱스, e: 결과 리스트에 추가된 간선의 수

    # 간선을 가중치에 따라 오름차순으로 정렬
    graph = sorted(graph, key=lambda item: item[2])

    ds = DisjointSet(vertices)

    while e < vertices - 1:
        u, v, w = graph[i]
        i = i + 1
        x = ds.find(u)
        y = ds.find(v)

        # 사이클이 형성되지 않는 경우에만 결과 리스트에 추가
        if x != y:
            e = e + 1
            result.append((u, v, w))
            ds.union(x, y)

    return result

# 그래프 데이터: (출발 정점, 도착 정점, 가중치)
graph = [(0, 1, 10), (0, 2, 6), (0, 3, 5), (1, 3, 15), (2, 3, 4)]
vertices = 4  # 정점의 수

# 크루스칼 알고리즘 실행
mst = kruskal(graph, vertices)
print("Minimum Spanning Tree:")
for u, v, weight in mst:
    print(f"{u} - {v}: {weight}")


```


#### 특징
- **시간 복잡도**
	- 크루스칼의 시간 복잡도는 주로 간선을 정렬하는 데서 결정이 된다. 
	-   O(ElogE)이다. E는 간선의 수이다. 
	- Union(), Find는 모두 상수시간에 가까운 시간 복잡도를 가진다. 
- **활용**
	- **네트워크 설계** : 네트워크의 모든 노드를 연결하면서도 전체 연결 비용을 최소화하고자 할 때 최소 신장 트리를 찾는다. 
	- **클러스터링** : 데이터 클러스터링에서 사용될 수 있다. 데이터 포인트 가늬 거리를 간선의 가중치로 간주하여 MST를 구성하고 가장 긴 간선을 제거함으로써 데이터를 의미 있는 클러스터로 분할할 수 있다. 




## MST(Minimum Spanning Tree, MST)

#### 개념
- 그래프의 모든 정점들을 최소의 비용으로 연결하는 부분 그래프를 의미한다. 
- 트리의 성질에 따라 정점의 수가 N일 때, N-1개의 간선을 가진다. 

#### Prim 알고리즘
- Kruskal과 더불어서 MST를 찾는데 많이 사용되는 알고리즘이다. 
- 시작 정점에서부터 출발하여, MST를 점진적으로 확장해 나간다. 
- 하나의 정점에서 인접한 간선들 중에서 가장 가중치가 낮은 간선을 선택하고 이 간선을 통해 연결되는 새로운 정점을 트리에 추가한다. 

![[Prim-animation.gif]]

#### 활용
- Kruskal에서 살펴보았던 활용 예와 같다. (Kruskal이 MST를 만드는 알고리즘이기 때문) 
- 최적화 솔류션을 찾는데 유용하다 "최소 비용으로"





<hr>
#### 참고
https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/
