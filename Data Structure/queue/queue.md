#자료구조 #queue #선입선출 #선형큐 #원형큐 #우선순위큐 

---
#### 큐(queue) 란?

**==선형 구조==의 형태이며 데이터를 일시적으로 쌓아두기 위한 자료구조 중 하나로 ==선입선출(FIFO, First-In-First-Out)==의 특성을 의미**

메모리 안 데이터들을 더욱 효율적으로 다루기 위해 만들어진 데이터 참조 방식

![300](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/queue%20/%20Data_Queue.svg.png)

##### 선형구조

데이터를 저장하기 위한 기본적인 형태로 데이터가 **'일렬로 나열'** 되어 있을 뿐만 아니라 데이터 간에 순서가 있고 논리적으로 이어져 있는 구조를 의미
ex. 배열, 리스트
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/queue%20/%20%EC%9E%90%EB%A3%8C%EA%B5%AC%EC%A1%B0.png)

##### 선입선출

자료구조에서 사용되는 용어로 **'가장 먼저 추가된 데이터가 가장 먼저 삭제'** 되는 구조를 의미
![400](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/queue%20/%20%EC%84%A0%EC%9E%85%EC%84%A0%EC%B6%9C.png)
##### queue 동작 과정

front와 rear 포인터 기준으로 동작

- 큐에 데이터를 삽입하는 연산==(enqueue)==
	1. 데이터를 삽입할 때는 먼저 **rear**가 가리키고 있는 위치에 데이터를 저장(큐의 요소 중 제일 마지막 부분을 의미)
	2. **rear**의 위치는 다음 데이터가 **삽입될 위치로 이동**
- 큐에 데이터를 삭제하는 연산==(dequeue)==
	1. 데이터가 추출할 때는 먼저 **front**가 가리키고 있는 위치에 데이터를 추출(큐 내의 요소 중 가장 첫 번째 부분을 의미)
	2. **front**의 위치는 다음 데이터가 **추출될 위치로 이동**
- 큐에 가장 앞에 있는 데이터를 확인하는 연산==(peek)==
- 큐가 비어있는지 확인하는 연산==(isEmpty)==

#### 장점

- 동적으로 메모리 할당 가능
- 데이터 입출력 속도가 빠르다
- 순차적으로 되어 있어서 입력 순서에 따라 처리할 때 유용

#### 단점

- 중간에 위치한 데이터에 접근하기 어려움
- 한 번에 하나의 데이터만 처리 가능

---
#### queue의 다른 형태

1. 선형 큐
	- 기본적인 큐의 형태
	- 막대 모양으로 된 큐로, 크기가 제한되어 있고 빈 공간을 사용하려면 모든 자료를 꺼내거나 자료를 한칸 씩 옮겨야 한다는 단점
2. 원형 큐
	- 선형 큐의 문제점을 보완
	- 배열의 마지막 인덱스에서 다음 인덱스로 넘어갈 때 **(index+1) % 배열의 사이즈** 를 이용하여 Out Of Bounds Exception이 일어나지 않고 인덱스 0으로 순환되는 구조
![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/queue%20/%20%EC%9B%90%ED%98%95%ED%81%90.png)
3. 우선순위 큐
	- 우선순위 큐(Priority Queue)는 들어가는 순서에 관계없이 큐에서 dequque 될 때, 우선순위에 맞게 나감
	- 예를들어 A,B,C가 있을 때, A가 우선순위가 1, B가 3, C가 2면 C, B, A순으로 넣어도 A, C, B순으로 나옴
	- 배열과 연결리스트 기반으로 구현하면 성능이 저하되므로, 일반적으로 힙을 이용하여 많이 구현
		- 힙으로 구현하면 삽입/삭제 시간은 O(logN)
		- 힙은 자식-부모 노트간의 크기 비교로 구현할 수 있음

---
#### 구현 예시

![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/queue%20/%20queue.png)
##### 선형큐(C++)
```c++
#include <iostream>
#include <queue>
using namespace std;

int main(){

	//큐 선언
	queue<int> q;

	//큐에 1~5삽입
	for(int i = 1; i<=5; i++){
		q.push(i);
	}

	//큐 사이즈 리턴
	cout << q.size() << endl;

	//맨 앞 뒤 원소 확인
	int front = q.front();
	//int rear = q.back();
	cout << front << " " << endl;

	//맨 앞 원소 삭제(1)
	q.pop();

	//큐의 전체원소 출력하기
	while (!q.empty()) {
		cout << q.front() << " ";
		q.pop();
	}

	return 0;

}
```

삽입 : O(1)
삭제 : O(1)
Search : O(n)

##### 원형 큐(C++)
```c++
#include <iostream>
using namespace std;

#define MAX_SIZE 5

class CircularQueue {
private:
    int front, rear;
    int arr[MAX_SIZE];

public:
    CircularQueue() {
        front = rear = -1;
    }

    bool isFull() {
        return (front == 0 && rear == MAX_SIZE - 1) || (rear == front - 1);
    }

    bool isEmpty() {
        return front == -1;
    }

    void enqueue(int value) {
        if (isFull()) {
            cout << "큐가 꽉 찼습니다. 데이터를 추가할 수 없습니다." << endl;
            return;
        }

        if (front == -1) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % MAX_SIZE;
        }

        arr[rear] = value;
        cout << value << "을(를) 큐에 추가했습니다." << endl;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "큐가 비어있습니다. 데이터를 제거할 수 없습니다." << endl;
            return;
        }

        cout << arr[front] << "을(를) 큐에서 제거했습니다." << endl;

        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % MAX_SIZE;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "큐가 비어있습니다." << endl;
            return;
        }

        cout << "큐 요소: ";
        int i = front;
        do {
            cout << arr[i] << " ";
            i = (i + 1) % MAX_SIZE;
        } while (i != (rear + 1) % MAX_SIZE);
        cout << endl;
    }
};

int main() {
    CircularQueue queue;

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    queue.enqueue(5);
    queue.enqueue(6);  // 큐가 꽉 차 있음

    queue.display();

    queue.dequeue();
    queue.dequeue();

    queue.display();

    return 0;
}
```

##### 우선순위 큐
```c++
#include <iostream>

#include <queue>

using namespace std;

  

int main() {

priority_queue<int, vector<int>, greater<int> > q;

q.push(4);

q.push(9);

q.push(1);

q.push(7);

q.push(10);

q.push(2);

q.push(3);

while (!q.empty()) {

cout << q.top() << " ";

q.pop();

}

return 0;

}
```

##### 백준 문제 예시
https://www.acmicpc.net/problem/2164
```c++
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);

	queue<int> Q;
	int N;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		Q.push(i);
	}

	while (Q.size() != 1) {
    	Q.pop();
		Q.push(Q.front());
		Q.pop();
	}

	cout << Q.front() << endl;

	

	return 0;
}
```

#### 사용 예시

![](https://sunnnyimg.s3.ap-northeast-2.amazonaws.com/queue%20/%20%EC%82%AC%EC%9A%A9%EC%98%88%EC%8B%9C.png)

#### 참고자료
C++ 자료구조론 - ELLIS HOROWITZ
https://adjh54.tistory.com/135#2.%20%ED%81%90(Queue)%20%EC%82%AC%EC%9A%A9%20%EC%98%88%EC%8B%9C-1
https://sanghyu.tistory.com/83
https://velog.io/@misun9283/Queue

