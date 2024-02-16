#include <stdio.h>
#include <stdlib.h>

struct Node
{
    struct Node *next;
    int data;
};

struct Node *front = NULL;
struct Node *rear = NULL;

int isEmpty()
{
    if (front == NULL)
        return 1;
    else
        return 0;
}

void enque(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (isEmpty())
    {
        front = newNode;
        rear = newNode;
    }

    else
    {
        rear->next = newNode;
        rear = rear->next;
    }
}

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

void printQueue()
{
    struct Node *cur = front;
    printf("Queue data\n");
    while (cur != NULL)
    {
        printf("%d  ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

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
