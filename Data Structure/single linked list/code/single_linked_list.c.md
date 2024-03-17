
```c
#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

struct node *head = NULL;

void insert(int data) {
	struct node *newNode = (struct node *)malloc(sizeof(struct node));
	newNode->data = data;
	newNode->next = head;
	head = newNode;
}

void delete(int data) {
	struct node *temp = head;
	struct node *prev = NULL;
	
	while (temp != NULL) {
		if (temp->data == data) {
			if (prev == NULL) {
				head = temp->next;
			} else {
				prev->next = temp->next;
			}
			free(temp);
			printf("Data %d deleted\n", data);
			return;
		}
		prev = temp;
		temp = temp->next;
	}
	printf("Data not found\n");
}

void find(int data) {
	struct node *temp = head;
	while (temp != NULL) {
		if (temp->data == data) {
			printf("Data found\n");
			return;
		}
		temp = temp->next;
	}
	printf("Data not found\n");
}

void display() {
	struct node *temp = head;
	while (temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}  

int main() {
	insert(10);
	insert(20);
	insert(30);
	insert(40);
	insert(50);
	display();
	delete(30);
	display();
	find(20);
	find(30);
	return 0;
}
```
