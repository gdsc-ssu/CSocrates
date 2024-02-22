
사이클이 없는 그래프.
보통은 양방향 그래프를 의미하지만, 사이클이 없는 단방향 그래프도 트리라고 부를 수 있다.


계층 구조를 표현하는 거의 모든 곳에서 Tree를 사용한다고 생각하면 된다. 재귀적인 표현을 적용시키기 매우 유리한 환경이다.

# 용어 정리

노드 (node) : 데이터가 담길 수 있고, 다른 노드와 연결할 수 있는 구조.
엣지 (edge) : 노드의 연결 상태를 나타내는 정보.
루트 노드 (root) : 트리에서 최상위 계층을 의미하는 노드. 모든 노드는 루트 노드가 될 수 있다.
형제 노드, 조상 노드 등 : 노드끼리의 관계를 나타낸다. 
internal node : 내부 노드를 의미하며, 자식이 있는 노드를 의미한다.
external node : 리프 노드를 의미하며, 자식이 없는 노드를 의미한다.
트리의 높이 : 해당 트리의 루트 노드로부터 가장 먼 자식까지 가는 데 거치는 엣지의 개수.
트리의 차수 : degree라고 하며, 보통 자식의 개수를 의미한다.

# 어디에서 사용하나요?

계층 관계가 정의되어야 하는 모든 곳에서 사용할 수 있다.

* 파일 시스템
* Abstract Syntax Tree (AST)
* NLP
* DOM Tree
* 등등 엄청나게 많이 사용한다.

# 어떻게 구현하나요?

완전 이진트리 형태가 보장될 때, 배열을 활용할 수 있다.
부모 = 자식 / 2
왼쪽자식 = 부모 * 2
오른쪽자식 = 부모 * 2 + 1
루트 = 1

아래 예시는 세그먼트 트리의 연산 Update, Query의 예시

```c++
const int MN = 1000000;

ll seg[MN*4+1];

ll Update(int idx, ll val, int n=1, int l=1, int r=MN) {
    if(r<idx || idx<l) return seg[n];
    if(l==r) return seg[n] = val;
    int mid = (l+r)/2;
    return seg[n] = Update(idx, val, n*2, l, mid) + Update(idx, val, n*2+1, mid+1, r);
}

ll Query(int L, int R, int n=1, int l=1, int r=MN) {
    if(r<L || R<l) return 0;
    if(L<=l && r<=R) return seg[n];
    int mid = (l+r)/2;
    return Query(L, R, n*2, l, mid) + Query(L, R, n*2+1, mid+1, r);
}
```

가변적인 이진 트리의 구현은 링크드 리스트로 할 수 있다.

```c++
#include <iostream>
using namespace std;

class TreeNode {
public:
    int value;
    TreeNode *left, *right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class LinkedListTree {
private:
    TreeNode* root;

public:
    LinkedListTree() : root(nullptr) {}

    void createSampleTree() {
        root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
    }

    ~LinkedListTree() {}

    void printTree(TreeNode* node) {
        if (node == nullptr) return;
        cout << node->value << " ";
        printTree(node->left);
        printTree(node->right);
    }

    void printTree() {
        printTree(root);
        cout << endl;
    }
};

int main() {
    LinkedListTree tree;
    tree.createSampleTree();
    tree.printTree();
    return 0;
}

```

사실 그래프로 이어주는게 제일 편하다.

```c++
#include <iostream>
using namespace std;
const int MN = 100000;
vector<int> G[MN];

int main (){
	G[3].push_back(5);
	G[3].push_back(7);
}
```

