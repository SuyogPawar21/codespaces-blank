#include <iostream>

template <class T> class Stack {

    class Node {

        public:
        T data;
        Node* next;

        Node(T data, Node* next) {
            this->data = data;
            this->next = next;
        }
        Node(T data) {
            this->data = data;
            next = nullptr;
        }

        ~Node() {
            std::cout << "Node Destroyed" << std::endl;
        }
    };

    private:
    Node* head;
    int size;
    
    void delLinkedList(Node* head) {
        if (!head) return;
        else {
            delLinkedList(head->next);
            delete head;
        }
    }

    public:
    Stack() {
        head = nullptr;
        size = 0;
    }

    bool isEmpty() {
        return size == 0 ;
    }

    void push(T data) {
        if (isEmpty() == true) {
            head = new Node(data);
        }
        else {
            Node* temp = new Node(data, head);
            head = temp;
        }
        size++;
    }

    T pop() {
        if (isEmpty() == true) {
            return NULL;
        }
        else {
            Node* temp = head;
            head = head->next;
            T value = temp->data;
            delete temp;
            size--;
            return value;
        }
    }

    int len() {
        return size;
    }

    ~Stack() {
        delLinkedList(head);
        std::cout << "Stack Destroyed" << std::endl;
    }
};



int main() {
    Stack<int> stack;
    std::cout << stack.isEmpty() << std::endl;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    std::cout << stack.isEmpty() << std::endl;
    std::cout << stack.len() << std::endl;
    std::cout << stack.pop() << std::endl;
    return 0;
}