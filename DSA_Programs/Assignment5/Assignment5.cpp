#include <iostream>

static const int MAXSIZE = 30;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node() {
        data = 0;
        left = right = nullptr;
    }

    Node(int data) {
        this->data = data;
        left = right = nullptr;
    }
};

class Queue {

private:
    int rear, front, size;
    Node* array[MAXSIZE];

public:

    Queue() {
        rear = -1;
        size = front = 0;
    }

    void enqueue(Node* address) {
        size++;
        rear = (rear + 1) % MAXSIZE;
        array[rear] = address;
    }

    Node* dequeue() {
        size--;
        Node* tmp = array[front];
        front = (front + 1) % MAXSIZE;
        return tmp;
    }

    int len() {
        return size;
    }
};


class BST {
private:
    Node* mainRoot;

    Node* insertHelper(Node* root, Node* nodeToBeInserted) {

        if (!root) return nodeToBeInserted;

        else {
            Node* current = root;
            Node* previous = nullptr;
            while (current) {
                if (current->data >= nodeToBeInserted->data) {
                    previous = current;
                    current = current->left;
                }
                else {
                    previous = current;
                    current = current->right;
                }
            }
            (previous->data >= nodeToBeInserted->data ? previous->left : previous->right) = nodeToBeInserted;
            return root;
        }
    }

    Node* searchHelper(Node* root, int data) {
        if (root->data == data) return nullptr;
        else {
            Node* current = root;
            Node* previous = nullptr;
            while (current) {
                if (current->data == data) return previous;
                else if (current->data > data) {
                    previous = current;
                    current = current->left;
                } else {
                    previous = current;
                    current = current->right;
                }
            }
            return nullptr;
        }
    }

    Node* delRoot(Node* root) {
        if (!root) return nullptr;
        Node* leftSubtree = root->left;
        Node* rightSubtree = root->right;
        delete root;
        if (leftSubtree) {
            if (rightSubtree) {
                return insertHelper(rightSubtree, leftSubtree);
            }
            else return leftSubtree;
        }
        else return rightSubtree;
    }

    void inorderHelper(Node* root) {
        if (!root) return;
        inorderHelper(root->left);
        std::cout << root->data << "\t";
        inorderHelper(root->right);
    }

    void preorderHelper(Node* root) {
        if (!root) return;
        std::cout << root->data << "\t";
        preorderHelper(root->left);
        preorderHelper(root->right);
    }

    void postorderHelper(Node* root) {
        if (!root) return;
        postorderHelper(root->left);
        postorderHelper(root->right);
        std::cout << root->data << "\t";
    }

    void delTree(Node* root) {
        if (!root) return;
        else {
            delTree(root->left);
            delTree(root->right);
            delete root;
        }
    }

    int depthHelper(Node* root) {
        if (!root) return 0;
        return 1 + std::max(depthHelper(root->left), depthHelper(root->right));
    }

    void mirrorHelper(Node* root) {
        if (!root) return;
        mirrorHelper(root->left);
        mirrorHelper(root->right);
        std::swap(root->left, root->right);
    }

    Node* copyHelper(Node* root) {
        if (!root) return nullptr;
        else {
            Node* newhead = new Node(root->data);
            newhead->left = copyHelper(root->left);
            newhead->right = copyHelper(root->right);
            return newhead;
        }
    }

public:

    BST() {
        mainRoot = nullptr;
    }

    ~BST() {
        delTree(mainRoot);
    }

    void insert(int data) {
        Node* node = new Node(data);
        mainRoot = insertHelper(mainRoot, node);
    }

    bool search(int data) {
        if (!mainRoot) return false;
        else if (mainRoot->data == data) return true;
        else return searchHelper(mainRoot, data) != nullptr;
    }

    void del(int data) {
        if (!mainRoot) return;
        if (mainRoot->data == data) mainRoot = delRoot(mainRoot);
        else {
            Node* previous = searchHelper(mainRoot, data);
            if (!previous) return;
            if (previous->right && previous->right->data == data) previous->right = delRoot(previous->right);
            else previous->left = delRoot(previous->left);
        }
    }

    void inorder() {
        if (!mainRoot) std::cout << "Empty Tree" << std::endl;
        else {
            std::cout << "Inorder:   ";
            inorderHelper(mainRoot);
        }
        std::cout << "\n";
    }

    void preorder() {
        if (!mainRoot) std::cout << "Empty Tree" << std::endl;
        else {
            std::cout << "Preorder:   ";
            preorderHelper(mainRoot);
        }
        std::cout << "\n";
    }

    void postorder() {
        if (!mainRoot) std::cout << "Empty Tree" << std::endl;
        else {
            std::cout << "Postorder:   ";
            postorderHelper(mainRoot);
        }
        std::cout << "\n";
    }

    void bfs() {
        if (!mainRoot) {
            std::cout << "Empty Tree" << std::endl;
            return;
        }
        std::cout << "Level-Order Traversal" << std::endl;
        Queue queue;
        queue.enqueue(mainRoot);
        int level = 0;
        Node* tmp;
        while (queue.len() != 0) {
            std::cout << "Level " << level++ << ": ";
            int length = queue.len();
            for (int i = 0; i < length; i++) {
                tmp = queue.dequeue();
                if(tmp->left) queue.enqueue(tmp->left);
                if (tmp->right) queue.enqueue(tmp->right);
                std::cout << tmp->data << "\t";
            }
            std::cout << "\n";
        }
    }

    void leafNodes() {
        if (!mainRoot) {
            std::cout << "Empty Tree" << std::endl;
            return;
        }
        std::cout << "Leaf Nodes" << std::endl;
        Queue queue;
        queue.enqueue(mainRoot);
        int count = 0;
        Node* tmp;
        while (queue.len() != 0) {
            int length = queue.len();
            for (int i = 0; i < length; i++) {
                tmp = queue.dequeue();
                if(tmp->left) queue.enqueue(tmp->left);
                if (tmp->right) queue.enqueue(tmp->right);
                if (!tmp->left && !tmp->right) {
                    std::cout << tmp->data << "\t";
                }
            }
        }
        std::cout << "\n";
    }

    BST* copy() {
        BST* bstcopy = new BST();
        bstcopy->setmainRoot(copyHelper(mainRoot));
        return bstcopy;
    }

    int depth() {
        return depthHelper(mainRoot);
    }

    void mirror() {
        mirrorHelper(mainRoot);
    }

    void setmainRoot(Node* mainRoot) {
        this->mainRoot = mainRoot;
    }

};

int main() {
    BST bst;
    bst.insert(10);
    bst.insert(15);
    bst.insert(5);
    bst.insert(1);
    bst.insert(20);
    bst.insert(7);
    bst.insert(13);
    bst.inorder();
    bst.preorder();
    bst.postorder();
    std::cout << "Depth: " << bst.depth() << std::endl;
    bst.bfs();
    bst.leafNodes();
}