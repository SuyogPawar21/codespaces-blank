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

class TreeNode {
    public:
        char data;
        TreeNode* left;
        TreeNode* right;

        TreeNode(char data) {
            this->data = data;
            left = right = nullptr;
        }

        TreeNode(char data, TreeNode* left, TreeNode* right) {
            this->data = data;
            this->left = left;
            this->right = right;
        }
};

class ExpressionTree {
    private:
        TreeNode* mainRoot;

        void inorderHelper(TreeNode* root) {
            if (!root) return;
            inorderHelper(root->left);
            std::cout << root->data << "\t";
            inorderHelper(root->right);
        }

        void preorderHelper(TreeNode* root) {
            if (!root) return;
            std::cout << root->data << "\t";
            preorderHelper(root->left);
            preorderHelper(root->right);
        }

        void postorderHelper(TreeNode* root) {
            if (!root) return;
            postorderHelper(root->left);
            postorderHelper(root->right);
            std::cout << root->data << "\t";
        }

    public:
        ExpressionTree(TreeNode* root) {
            mainRoot = root;
        }

        void inorder() {
            if (!mainRoot) {
                std::cout << "Empty Tree" << std::endl;
            }
            else {
                std::cout << "Inorder: ";
                inorderHelper(mainRoot);
                std::cout << "\n";
            }
        }
        
        void inorderNR() {
            if (!mainRoot) return;
            else {
                std::cout << "Inorder: ";
                Stack<TreeNode*> stack;
                TreeNode* temp = mainRoot;
                while (temp || stack.isEmpty() != true) {
                    while (temp) {
                        stack.push(temp);
                        temp = temp->left;
                    }
                    temp = stack.pop();
                    std::cout << temp->data << "\t";
                    temp = temp->right;
                }
                std::cout << "\n";
            }
        }


        void preorder() {
            if (!mainRoot) std::cout << "Empty Tree" << std::endl;
            else {
                std::cout << "Preorder:   ";
                preorderHelper(mainRoot);
                std::cout << "\n";
            }
        }

        void preorderNR() {
            if (!mainRoot) std::cout << "Empty Tree" << std::endl;
            else {
                std::cout << "Preorder: ";
                Stack<TreeNode*> stack;
                TreeNode* temp = nullptr;
                stack.push(mainRoot);
                while (stack.isEmpty() != true) {
                    temp = stack.pop();
                    std::cout << temp->data << "\t";
                    if (temp->right) {
                        stack.push(temp->right);
                    }
                    if (temp->left) {
                        stack.push(temp->left);
                    }
                }
                std::cout << "\n";
            }
        }

        void postorder() {
            if (!mainRoot) std::cout << "Empty Tree" << std::endl;
            else {
                std::cout << "Postorder:   ";
                postorderHelper(mainRoot);
                std::cout << "\n";
            }
        }

        void postorderNR() {
            if (!mainRoot) std::cout << "Empty Tree" << std::endl;
            else {
                std::cout << "Postorder: ";
                Stack<TreeNode*> stack1, stack2;
                TreeNode* temp = nullptr;
                stack1.push(mainRoot);
                stack2.push(mainRoot);
                while (stack1.isEmpty() != true) {
                    temp = stack1.pop();
                    if (temp->right) {
                        stack1.push(temp->right);
                        stack2.push(temp->right);
                    }
                    if (temp->left) {
                        stack1.push(temp->left);
                        stack2.push(temp->left);
                    }
                }
                while (stack2.isEmpty() != true) {
                    std::cout << stack2.pop()->data << "\t";
                }
                std::cout << "\n";
            }
        }
};

class ExpressionTreeConstructor {
    private:
        Stack<TreeNode*>* stack;

    public:
        ExpressionTreeConstructor() {
            stack = new Stack<TreeNode*>();
        }

        ~ExpressionTreeConstructor() {
            delete stack;
        }

        ExpressionTree* construct(char expression[], bool isPrefix) {
            int length = std::strlen(expression);
            if (isPrefix == true) {
                std::reverse(expression, expression+length);
            }
            char token;
            TreeNode* operand1;
            TreeNode* operand2;
            for (int i = 0; i < length; i++) {
                token = expression[i];
                if (isalpha(token) != 0) {
                    stack->push(new TreeNode(token));
                }
                else {
                    if (isPrefix == true) {
                        operand2 = stack->pop();
                        operand1 = stack->pop();
                    }
                    else {
                        operand1 = stack->pop();
                        operand2 = stack->pop();
                    }
                    stack->push(new TreeNode(token, operand2, operand1));
                }
            }
            return new ExpressionTree(stack->pop());
        }


};


int main() {
    ExpressionTreeConstructor e;
    char postfix[MAXSIZEOFEXPRESSION];
    char prefix[MAXSIZEOFEXPRESSION];

    std::cout << "Postfix: ";
    std::cin >> postfix;
    ExpressionTree* postfixTree = e.construct(postfix, false);
    postfixTree->inorder();
    postfixTree->preorder();
    postfixTree->postorder();

    std::cout << "Prefix: ";
    std::cin >> prefix;
    ExpressionTree* prefixTree = e.construct(prefix, true);
    prefixTree->inorderNR();
    prefixTree->preorderNR();
    prefixTree->postorderNR();
}