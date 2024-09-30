### 서론

**큐의 문제점**
-> 데이터 삽입 / 삭제 시 데이터들을 앞 혹은 뒤로 당겨주는 과정이 필요하다. ==불필요한 시간 낭비==
- 큐의 문제점을 해결하고자 메모리를 효율적으로 활용할 수 있는 circular queue가 등장 했다. 
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Circular%20queue%20/%20queue.png)
**Circular Queue의 개념**
- 시작점과 끝점이 연결된 원형 구조를 가지고 있어, 배열의 끝에 도달하면 다시 배열의 시작점으로 돌아가는 특징을 가진다. 
- 큐가 가득 차 있지 않은 상태에서도 빈 공간을 효율적으로 재활용할 수 있게 한다. 
- FIFO 방식을 따른다. 

### Circular Queue 활용 예

1. **프로세스 스케줄링**
	- os에서는 여러 프로세스가 CPU 자원을 공정하게 사용할 수 있도록 관리해야 한다 
	- 프로세스가 순차적으로 Circular Queue에 추가되며 CPU는 Queue의 앞 부분에 있는 프로세스부터 차례대로 처리한다. 
	- ==Round Robin== : 프로세스가 도착한 순서대로 프로세스를 dispatch하고 정해진 time quantum 만큼의 시간동안 CPU를 사용한다. 할당된 시간에 완료되지 못한 프로세스는 다시 Queue에 들어가게 된다. 
2. **네트워크 버퍼**
	- 데이터 패킷을 처리할 때 사용된다. 
	- 네트워크 트래픽이 많을 때 Cirqular Queue를 사용하여 패킷을 임시로 사용하고 네트워크 장비가 처리할 수 있을 때까지 기다리게 한다. 
3. **실시간 데이터 처리**
	- 데이터를 지연 없이 처리해야 한다. 
	- 데이터가 생성되면 Queue에 추가되고 시스템은 Queue의 앞 부분부터 차례로 처리한다.
	- 데이터 처리에 있어서 순서를 보장하며 처리 대기 시간을 최소화하는데 도우미 된다. 

**정리**
- 고정된 메모리 공간 내에서 데이터의 순환적인 처리를 가능하게 한다. 
- 시스템 리소스의 공정한 분배와 실시간 데이터 처리 요구 사항을 충족시키는데 기여한다. 

### Circular Queue의 주요 연산

- **Enqueue(삽입)** : `rear` 위치에 데이터를 추가하고 `rear`를 다음 위치로 업데이트한다. 
- **Dequeue(삭제)** : `front`위치의 데이터를 제거하고, `front`를 다음 위치로 업데이트한다. 
- **Peek** : `front` 위치의 데이터를 반환하지만 , 제거하지는 않는다. 
- **isEmpty & isFull** : 큐가 비어 있는지 가득 차 있는지 확인한다. 

##### 코드
```python
class CircularQueue:
    def __init__(self, size):
        self.size = size
        self.queue = [None] * size
        self.front = self.rear = -1

    def enqueue(self, item):
	    #queue가 가득 찾는지 확인한다. 
        if ((self.rear + 1) % self.size == self.front):
            print("The circular queue is full")
            
        #queue가 비어있는지 확인한다. 
        elif (self.front == -1):
            self.front = 0
            self.rear = 0
            self.queue[self.rear] = item
        else:
            self.rear = (self.rear + 1) % self.size
            self.queue[self.rear] = item
        print(f"Enqueued: {item}")

    def dequeue(self):
	    #queue가 비어있는지 확인
        if (self.front == -1):
            print("The circular queue is empty")
		#큐에 단 하나의 요소만 있는 경우 
        elif (self.front == self.rear):
            temp = self.queue[self.front]
            self.front = -1
            self.rear = -1
            return temp
        else:
            temp = self.queue[self.front]
            self.front = (self.front + 1) % self.size
            return temp

    def is_empty(self):
        return self.front == -1

    def is_full(self):
        return (self.rear + 1) % self.size == self.front

    def display(self):
        if(self.front == -1):
            print("The circular queue is empty")

        elif (self.rear >= self.front):
            print("Circular Queue elements are:", end=" ")
            for i in range(self.front, self.rear + 1):
                print(self.queue[i], end=" ")
            print()

        else:
            print("Circular Queue elements are:", end=" ")
            for i in range(self.front, self.size):
                print(self.queue[i], end=" ")
            for i in range(0, self.rear + 1):
                print(self.queue[i], end=" ")
            print()

# 사용 예시
cq = CircularQueue(5)
cq.enqueue(1)
cq.enqueue(2)
cq.enqueue(3)
cq.display()  # 큐의 요소들을 보여준다. 
item = cq.dequeue()
print(f"Dequeued: {item}")
cq.display()  # dequeue 연산 후의 queue의 모습을 보여준다. 


```


### Circular Queue의 장단점

- 장점
	1. 공간 효율성 
	2. 데이터 순환 처리 용이 
	
- 단점
	1. 고정된 크기
	2. 동시성 문제
	3. 복잡한 인덱스 관리



### 추가
###### 멀티 스레딩 환경에서 Circular Queue 사용하기 
- 생산자와 소비자 패턴 구현에 사용된다. 
- 여러 생산자가 데이터를 큐에 추가하고, 여러 소비자가 데이터를 큐에서 제거하는 상황에서, Circular queue는 데이터의 순차적 처리를 보장하며 동시성 문제를 해결할 수 있다. 

 ###### 코드
 ```C
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define QUEUE_SIZE 5
int queue[QUEUE_SIZE];
int front = 0, rear = 0;

# 상호 배제를 보장하기 위한 뮤텍스이다. 큐에 대한 접근을 동기화하여 동시에 여러 스레드가 데이터를 변경하는 것을 방지한다. 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
#조건 변수로 큐가 가득차거나 비었을 때 스레드를 대기시키거나 깨우는데 사용 된다. 
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* producer(void* arg) {
    for (int i = 0; i < 10; ++i) {
        pthread_mutex_lock(&mutex);
        while ((rear + 1) % QUEUE_SIZE == front) {
            # queue가 가득차면 wait함수를 호출해서 대기한다. 
            pthread_cond_wait(&cond, &mutex);
        }
        // produce하는 과정 
        queue[rear] = i;
        printf("Produced: %d\n", i);
        rear = (rear + 1) % QUEUE_SIZE;

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(1); 
    }
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    for (int i = 0; i < 10; ++i) {
        pthread_mutex_lock(&mutex);
        while (front == rear) {
            // queue가 비어있을 경우 찰 떄까지 대기한다. 
            pthread_cond_wait(&cond, &mutex);
        }
        // Consume
        int item = queue[front];
        printf("Consumed: %d\n", item);
        front = (front + 1) % QUEUE_SIZE;

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(2); // Simulate work
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, producer, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);

	#메인 쓰레드가 두 작업 스레드의 실해이 끝날 때까지 기다리게 한다. 
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}

```

실행화면
![](https://csocrates-s3.s3.ap-northeast-2.amazonaws.com/Circular%20queue%20/%20execute.png)
