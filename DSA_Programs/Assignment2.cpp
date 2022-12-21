#include <iostream>
#include <cstring>
#include <algorithm>

static const int MAXSIZEOFEXPRESSION = 30;
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

    T top() {
        if (isEmpty() == true) {
            return NULL;
        }
        else return head->data;
    }

    int len() {
        return size;
    }

    ~Stack() {
        delLinkedList(head);
    }
};


class ExpressionsUtlilty {

    private:
    Stack<char>* stackChar;
    Stack<int>* stackInt;

    void reverseExpression(char expression[]) {
        int length = strlen(expression);
        for (int i = 0; i < length/2; i++) {
            std::swap(expression[i], expression[length-i-1]);
        }
        for (int i = 0; i < length; i++) {
            if (expression[i] == '(') expression[i] == ')';
            else if (expression[i] == ')') expression[i] == '(';
            else continue;
        }
    }

    int priority(char c) {
        if (c == '^') return 3;
        else if (c == '*' || c == '/') return 2;
        else if (c == '+' || c == '-') return 1;
        else return 0;
    }

    public:
    ExpressionsUtlilty() {
        stackChar = new Stack<char>();
        stackInt = new Stack<int>();
    }

    void infixToPostfix(char infix[], char postfix[]) {
        int positionInPostfix = 0;
        char token;
        for (int position = 0; infix[position] != '\0'; position++) {
            token = infix[position];
            if (isalpha(token) != 0) {
                postfix[positionInPostfix++] = token;
            }
            else if (token == '(') {
                stackChar->push(token);
            }
            else if (token == ')') {
                while (stackChar->top() != '(') {
                    postfix[positionInPostfix++] = stackChar->pop();
                }
                stackChar->pop();
            }
            else if (stackChar->isEmpty() == true || priority(token) > priority(stackChar->top())) {
                stackChar->push(token);
            }
            else {
                while (stackChar->isEmpty() == false && priority(token) <= priority(stackChar->top())) {
                    postfix[positionInPostfix++] = stackChar->pop();
                }
                stackChar->push(token);
            }
        }
        while (stackChar->isEmpty() == false) {
            postfix[positionInPostfix++] = stackChar->pop();
        }
        postfix[positionInPostfix++] = '\0';
    }

    void infixToPrefix(char infix[], char prefix[]) {
        reverseExpression(infix);
        infixToPostfix(infix, prefix);
        int length = strlen(prefix);
        std::reverse(prefix, prefix+length-1);
    }

    ~ExpressionsUtlilty() {
        delete stackChar;
        delete stackInt;
    }
};

int main() {
    ExpressionsUtlilty e;
    char infix[MAXSIZEOFEXPRESSION];
    char postfix[MAXSIZEOFEXPRESSION];
    char prefix[MAXSIZEOFEXPRESSION];
    std::cin >> infix;
    e.infixToPostfix(infix, postfix);
    std::cout << postfix << std::endl;
    e.infixToPrefix(infix, prefix);
    std::cout << prefix << std::endl;
    return 0;
}