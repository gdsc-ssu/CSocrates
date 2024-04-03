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
