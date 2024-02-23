#binary_search_tree #이진탐색트리

> 탐색을 위한 이진탐색(binary search)과 연결리스트(linked list)를 결합한 자료구조의 일종

	이진탐색의 경우 탐색에 소요되는 계산복잡성은 𝑂(log𝑛)으로 빠르지만 자료 입력, 삭제가 불가능.
	연결리스트의 경우 자료 입력, 삭제에 필요한 계산복잡성은 𝑂(1)로 효율적이지만 
	탐색하는 데에는 𝑂(𝑛)의 계산복잡성이 발생. 두 마리 토끼를 잡아보자는 것이 이진탐색트리의 목적!

##### 특징

- 왼쪽 노드에는 부모보다 작은 값이 저장
- 오른쪽 노드에는 부모와 같거나 큰 값이 저장
- 모든 노드는 중복 값을 가지지 않음
- 왼쪽 서브 트리와 오른쪽 서브 트리도 이진 탐색 트리임
- 이진 탐색 트리의 시간 복잡도는 ==**O(log n)**==으로 더 효율적


![[이진 탐색 트리 예시.gif]]

---
##### 이진 탐색 트리의  삽입/탐색

```c++
#include <iostream>
using namespace std;

// 이진 탐색 트리의 노드를 나타내는 구조체 정의
struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int k){
    key = k;
    left = nullptr;
    right = nullptr;
	}
};

// 이진 탐색 트리에 새로운 노드 삽입 함수
Node* insert(Node* root, int key) {
    if (root == nullptr) {
        return new Node(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }

    return root;
}

// 이진 탐색 트리에서 특정 Key를 찾는 함수
Node* search(Node* root, int key) {
    if (root == nullptr || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

int main() {
    Node* root = nullptr;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    int keyToSearch = 60;
    Node* result = search(root, keyToSearch);
    if (result != nullptr) {
        cout << "Key " << keyToSearch << " found in the tree." << endl;
    } else {
        cout << "Key " << keyToSearch << " not found in the tree." << endl;
    }

    return 0;
}

```

![[탐색 연산 예.jpeg|500]]

##### 이진 탐색 트리에서의 삭제

- 단말 노드의 삭제
	- ==부모의 자식 필드에 0을 삽입==. 삭제된 노드 반환
	![[단말 노드의 삭제.jpeg]]

- 하나의 자식을 가진 비리프 노드의 삭제
	- 삭제된 노드의 자식을 삭제된 노드 자리에 위치
	![[하나의 자식을 가진 비리프 노드의 삭제.jpeg]]

- 두 개의 자식을 가진 비리프 노드의 삭제
	- 삭제된 원소를 왼쪽 서브트리에서 가장 큰 원소 또는 오른쪽 서브트리에서 가장 작은 원소로 대체
	![[두개의 자식을 가진 비리프 노드의 삭제.jpeg|500]]


```c++
Node* deleteNode(Node* root, int key) { 
	if (root == nullptr) {
		return root; 
	} 
	if (key < root->key) { 
		root->left = deleteNode(root->left, key); 
	} 
	else if (key > root->key) { 
	root->right = deleteNode(root->right, key); 
	} 
	else { // 삭제할 노드를 찾은 경우 
	
		// Case 1: 자식 노드가 없거나 하나인 경우 
		if (root->left == nullptr) {
			Node* temp = root->right; 
			delete root; 
			return temp; 
		} 
		else if (root->right == nullptr) {
			Node* temp = root->left; 
			delete root; 
			return temp; 
		} 
		
		// Case 2: 자식 노드가 둘 다 있는 경우 
		Node* temp = root->right; 
		while (temp->left != nullptr) { 
			temp = temp->left; 
		} 
	
		root->key = temp->key; 
		root->right = deleteNode(root->right, temp->key);
	} 
	return root; 
}
```

---

##### 장점

- 배열을 사용하여 탐색할 때 보다 시간 복잡도가 줄어듦(O(log n)) -> ==데이터 검색 속도 빨라짐==
	![[시간복잡도.webp|500]]
- 동적으로 데이터 집합 크기가 바뀌고 순서가 바뀌어도 문제 없음
##### 한계점

이진 탐색 트리 핵심 연산인 탐색, 삽입, 삭제의 계산 복잡성은 모두 𝑂(ℎ)으로 트리의 높이에 의해 수행시간이 결정되는 구조. 

이때, 트리가 다음과 같은 경우 문제가 발생
![[이진 탐색 트리 한계점 예시.png]]
위 경우는 노드 수는 적은데 높이가 5나 되버림
결과적으로 이진 탐색 트리의 계산 복잡성은 ==𝑂(𝑛)==이 되는데 이는 ==탐색 속도가 𝑂(log𝑛)으로 빠른 이진탐색==을 계승했다고 보기 어려움

 → 트리의 입력, 삭제 단계에 트리 전체의 균형을 맞추는 이진탐색트리의 일종인 **AVL Tree**가 제안

##### 참고
(https://ratsgo.github.io/data%20structure&algorithm/2017/10/22/bst/)
(https://medium.com/@yejinh/%EB%8D%B0%EC%9D%B4%ED%84%B0-%EA%B5%AC%EC%A1%B0-binary-search-tree-985f677cf37)