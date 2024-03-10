### 링크드 큐란

**배열의 단점을 없애고자 링크드리스트를 활용해 큐를 구현해낸 것으로 FIFO가 지원되는 링크드리스트이다.** 링크드 큐의 특징은 곧 연결 리스트의 특징인데 배열을 통해 구현하는 큐와 달리 다음의 특징을 갖는다.

* 삭제가 쉽다.
* 메모리 동적 할당이 가능하다.
* 사용하는 만큼만 메모리를 사용한다. 

>[!info]
> **링크드리스트로 구현한 큐가 맞는 표현이다. 링크드 큐라는 특별한 자료구조가 있는 것은 아니다.**

___
### 링크드 큐 만들기

링크드 큐를 만들기 위해선 우선 링크드리스트를 생성해야 한다. C언어를 활용해 간단한 링크드리스트를 만들어보자. 리스트에 사용할 각 노드부터 우선적으로 정의하자.

```c
struct Node
{
    struct Node *next;
    int data;
};
```

해당 노드는 다음 노드와 데이터 값을 저장하는 노드이다. 이제 이 노드들을 연결해서 링크드리스트를 생성할 수 있게하는 추가 함수를 살펴보자. 
우리는 **큐를 만드는 것이 목적이기 때문에 enqueue 함수를 정의**한다. 해당 함수는 링크드리스트의 끝에 새로운 노드를 추가하고 연결하는 작업을 진행한다.

```c
void enque(int data)
{
	//신규노드 생성
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (isEmpty())
    {
        front = newNode;
        rear = newNode;
    }

    else //꼬리에 연결
    {
        rear->next = newNode;
        rear = rear->next;
    }
}
```

이제 큐에서 하나씩 노드를 삭제하는 deque 함수를 정의해보자. 큐에 가장 처음 들어온 노드부터 순차적으로 제거해나가면 된다. 다음과 같이 작성한다.

```c
int deque()
{
    if (isEmpty())
    {
        perror("Empty Queue");
        return 0;
    }
    struct Node *delNode = front;
    int data = front->data;
    front = front->next;
    free(delNode);
    return data;
}
```

이제 실행해보고 실제로 FIFO의 방식을 따르는지 확인해보자.
```c
int main()
{
    for (int i = 0; i < 5; i++)
    {
        enque(i);
    }
    printQueue();

    for (int i = 0; i < 5; i++)
    {
        printf("deque: %d\n", deque());
    }
}
```

실행해보면 결과는 아래와 같다. FIFO의 기능이 정상적으로 동작하는 것을 확인할 수 있다.

![[스크린샷 2024-02-16 오후 3.13.22.png]]
___
### 그냥 링크드리스트인데요?

맞다. 일반적으로 링크드리스트를 구현할때 이와 같은 형태로 구현을 하는 경우가 많기 때문에 통상적으로 enque, deque까지 묶어서 링크드리스트로 기억하는 경우가 있다.

하지만 ==**링크드리스트를 통해서 스택이나 다른 자료구조를 구축하는 것도 가능하다**==. 링크드리스트는 자료의 저장 방식을 다루는 자료구조이고 이를 어떻게 꺼내고 넣을 것인지를 결정하는 것은 큐 또는 스택이 결정한다. 



