class Node:
    def __init__(self, key, left=None, right=None):
        self.key = key
        self.height = 0
        self.left = left
        self.right = right

class AVLTree:
    def __init__(self):
        self.head = None

    def height(self, node):
        if node is None:
            return -1
        return node.height

    def rightRotate(self, node):
        lNode = node.left
        node.left = lNode.right
        lNode.right = node
        node.height = max(self.height(node.left), self.height(node.right)) + 1
        lNode.height = max(self.height(lNode.left), self.height(lNode.right)) + 1
        return lNode

    def leftRotate(self, node):
        rNode = node.right
        node.right = rNode.left
        rNode.left = node
        node.height = max(self.height(node.left), self.height(node.right)) + 1
        rNode.height = max(self.height(rNode.left), self.height(rNode.right)) + 1
        return rNode

    def lrRotate(self, node):
        node.left = self.leftRotate(node.left)
        return self.rightRotate(node)

    def rlRotate(self, node):
        node.right = self.rightRotate(node.right)
        return self.leftRotate(node)

    def getBalance(self, node):
        if node is None:
            return 0
        return self.height(node.left) - self.height(node.right)

    def insert(self, key):
        self.head = self._insert(self.head, key)

    def _insert(self, node, key):
        if node is None:
            return Node(key)
        if key < node.key:
            node.left = self._insert(node.left, key)
        else:
            node.right = self._insert(node.right, key)

        node.height = max(self.height(node.left), self.height(node.right)) + 1
        balance = self.getBalance(node)

        # LL Case
        if balance > 1 and key < node.left.key:
            return self.rightRotate(node)
        # RR Case
        if balance < -1 and key > node.right.key:
            return self.leftRotate(node)
        # LR Case
        if balance > 1 and key > node.left.key:
            return self.lrRotate(node)
        # RL Case
        if balance < -1 and key < node.right.key:
            return self.rlRotate(node)

        return node

    def levelOrder(self, node):
        if not node:
            return
        queue = []
        queue.append(node)
        while queue:
            current = queue.pop(0)
            print(current.key, end=' ')
            if current.left:
                queue.append(current.left)
            if current.right:
                queue.append(current.right)
        print()

avl = AVLTree()

avl.insert(30); avl.insert(20); avl.insert(10)
avl.levelOrder(avl.head)  # LL

avl.insert(40); avl.insert(50)
avl.levelOrder(avl.head)  # RR

avl.insert(5); avl.insert(7)
avl.levelOrder(avl.head)  # LR

avl.insert(60)
avl.insert(55)
avl.levelOrder(avl.head)  # RL
