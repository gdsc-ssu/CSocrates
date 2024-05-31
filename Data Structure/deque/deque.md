## Deque (덱)
- Doubly-ended Queue
- 양쪽 끝에서 추가, 삭제가 가능한 선형 구조 형태의 자료구조
- 스택과 큐의 장점을 모아서 만들어진 자료구조
- 다양한 프로그래밍 언어에서 라이브러리로 구현되어 있음

> 선형 구조(Linear Structure)
> - 데이터를 저장하기 위한 기본적인 형태로 데이터가 **일렬로 나열**되어 있을 뿐만 아니라 데이터 간에 순서가 있고 논리적으로 이어져 있는 구조를 의미
![[Pasted image 20240202121115.png]]


### 동작흐름
![[Pasted image 20240202120723.png]]
- 입력과 출력이 양방향 가능
	- 데이터 입력 순서와 상관없이 출력 순서 조절 가능
- 큐의 선입선출과 스택의 후입선출의 개념을 복합적으로 사용할 수 있다.
	- 스택과 큐의 장점을 모아서 만들어진 자료구조
- Enqueue(추가) 및 Dequeue(삭제) 실행 속도는 O(1)



### 큐, 스택, 덱의 차이
| **분류** | **큐(Queue)** | **스택(Stack)** | **덱(Deque)** |
| ---- | ---- | ---- | ---- |
| **정의** | 먼저 들어온 데이터가 먼저 나가는(First-In-First-Out) 자료구조 | 마지막에 들어온 데이터가 먼저 나가는(Last-In-First-Out) 자료구조 | 양쪽 끝에서 삽입과 삭제가 가능한 자료구조 |
| **삽입/삭제** | 삽입은 enqueue, 삭제는 dequeue | 삽입은 push, 삭제는 pop | addFirst, addLast, removeFirst, removeLast |
| **활용 예시** | 대기열, 버퍼(Buffer) 등 | 함수 호출(call stack), 수식 계산 등 | 양방향 큐(Double-Ended Queue), 회문(Palindrome) 판별, 최대값/최소값 검색 |
| **장점** | 데이터의 순서가 중요한 작업에 적합 | 구현이 쉽고, 메모리 관리가 용이 | 양쪽 끝에서의 삽입과 삭제가 가능 |
| **단점** | 큐의 크기가 고정되어 있으면 데이터가 가득 차면 더 이상 삽입이 불가능 | 데이터 접근이 어렵고, 중간에 있는 데이터에 접근하려면 맨 위의 데이터부터 차례로 꺼내야 함 | 메모리 사용량이 큼. 구현이 어렵다. |

### 마크다운으로 작성된 `deque` 사용법 및 예시

#### `deque` 생성
``` python
from collections import deque  # 빈 deque 생성 
dq = deque()  # 초기 값이 있는 deque 생성 
dq = deque([1, 2, 3])
```

#### `deque`에 아이템 추가
- `append(x)`: `deque`의 오른쪽 끝에 아이템 `x`를 추가
```python
dq.append(4)  # deque([1, 2, 3, 4])
```

- `appendleft(x)`: `deque`의 왼쪽 끝에 아이템 `x`를 추가
```python
dq.appendleft(0)  # deque([0, 1, 2, 3, 4])
```

#### `deque`에서 아이템 제거하기
- `pop()`: `deque`의 오른쪽 끝 아이템을 제거하고 반환
```python
dq.pop()  # deque([0, 1, 2, 3])
```

- `popleft()`: `deque`의 왼쪽 끝 아이템을 제거하고 반환
```python
dq.popleft()  # deque([1, 2, 3])
```

#### `deque`의 다른 유용한 메소드들
- `extend(iterable)`: `iterable`의 아이템들을 `deque`의 오른쪽 끝에 추가
```python
dq.extend([4, 5])  # deque([1, 2, 3, 4, 5])
```

- `extendleft(iterable)`: `iterable`의 아이템들을 `deque`의 왼쪽 끝에 추가
	- 주의할 점은 추가되는 순서가 `iterable`의 역순
```python
dq.extendleft([0, -1])  # deque([0, 1, 2, 3, 4, 5])
```

- `rotate(n)`: `deque`를 `n`만큼 회전시킨다. `n`이 양수면 오른쪽으로, 음수면 왼쪽으로 회전
```python
dq.rotate(1)  # deque([5, 0, 1, 2, 3, 4]) 
dq.rotate(-1)  # deque([0, 1, 2, 3, 4, 5])
```

- `clear()`: `deque`에서 모든 아이템을 제거
```python
dq.clear()  # deque([])
```

- `maxlen` 옵션을 설정하여 크기를 제한할 수 있다.
	- 메모리를 효율적으로 사용하게 도와준다.
```python
dq = deque(maxlen=3) 
dq.extend([1, 2, 3])
dq.append(4)  
# deque([2, 3, 4])
```


### 덱의 사용예시
1. Palindrome 검사
   - `deque`의 양 끝에서 문자를 제거하며 서로 비교
   - 모든 쌍이 동일하면, 해당 문자열은 회문이다.
```python
from collections import deque

def is_palindrome(s):
    dq = deque(s)
    while len(dq) > 1:
        if dq.popleft() != dq.pop():
            return False
    return True

# 회문 예시
print(is_palindrome("radar"))  # True

# 회문이 아닌 예시
print(is_palindrome("python"))  # False
```

2. 최근 사용 항목 추적
- 웹 브라우저 탭이나 최근 문서와 같은 최근 사용 항목을 추적할 때 `deque`의 `maxlen` 속성을 사용하여 최대 항목 수를 제한 가능
```python
from collections import deque

# 최근 5개의 사용 항목을 추적하는 deque
recent_items = deque(maxlen=5)

def access_item(item):
    if item in recent_items:
        recent_items.remove(item)
    recent_items.append(item)
    print(f"현재 항목: {list(recent_items)}")

access_item("Item 1")
access_item("Item 2")
access_item("Item 3")
access_item("Item 4")
access_item("Item 5")
# "Item 6"을 추가하면 "Item 1"이 제거
access_item("Item 6")

```

3. 슬라이딩 윈도우 알고리즘
- 배열이나 리스트에서 주어진 크기의 윈도우를 슬라이드하면서, 윈도우 내의 최대값 또는 최소값을 찾는 알고리즘
```python
from collections import deque

def max_sliding_window(nums, k):
    dq = deque()  # 인덱스를 저장
    result = []
    
    for i, num in enumerate(nums):
        # 새 요소가 이전의 최대값보다 크면 왼쪽에서 제거
        while dq and nums[dq[-1]] < num:
            dq.pop()
        dq.append(i)
        
        # 윈도우의 첫 번째 요소가 dq의 첫 번째 요소와 같은지 확인
        if dq[0] == i - k:
            dq.popleft()
        
        # 윈도우의 크기가 k가 되면, 최대값을 결과에 추가
        if i >= k - 1:
            result.append(nums[dq[0]])
    
    return result

# 예제 실행
nums = [1, 3, -1, -3, 5, 3, 6, 7]
k = 3
print(max_sliding_window(nums, k))  # [3, 3, 5, 5, 6, 7]
```


### 기타
#### 파이썬에서의 덱과 리스트의 차이
- 덱의 경우에는 양쪽 끝의 요소를 제거하는 것 모두 O(1), 
- 하지만 리스트의 경우에는 제일 앞부분을 제거하면 뒤에있는 원소들을 앞으로 땡겨오는 작업을 하므로 O(n)이다.
![[스크린샷 2024-02-02 오후 12.27.22.png]]