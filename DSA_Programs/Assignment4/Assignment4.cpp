/**
 * @author SuyogPawar
**/


// Various header files
#include <iostream>
#include <cstring>
#include <algorithm>


// Constant defining the max size an expression can have.
static const int MAXSIZEOFEXPRESSION = 30;


// Generic Stack same as in Assignment2
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


// Class for Expression Tree's Nodes
class TreeNode {

    public:
        // 'data' stores a character
        // 'left' is a pointer to the left subtree of the node
        // 'right' is a pointer to the right rightree of the node
        char data;
        TreeNode* left;
        TreeNode* right;

        // This constructor initializes the node with the data and
        // sets the left and right pointers to nullptr.
        TreeNode(char data) {
            this->data = data;
            left = right = nullptr;
        }

        // Fully Parameterised Constructor
        TreeNode(char data, TreeNode* left, TreeNode* right) {
            this->data = data;
            this->left = left;
            this->right = right;
        }
};


// Class for Expression Tree
class ExpressionTree {

    private:
        // 'mainRoot' is the pointer to the root node of this expression tree.
        TreeNode* mainRoot;

        // This recursive method is used to print the tree in inorder.
        // It takes as parameter the root of the tree to print in inorder.
        void inorderHelper(TreeNode* root) {

            // If tree is empty then there is nothing to print so just return.
            if (root == nullptr) return;

            // Print the left subtree
            inorderHelper(root->left);

            // Print the root
            std::cout << root->data << "\t";

            // Print the right subtree
            inorderHelper(root->right);
        }

        // This recursive method is used to print the tree in preorder.
        // It takes as parameter the root of the tree to print in preorder.
        void preorderHelper(TreeNode* root) {

            // If tree is empty then there is nothing to print so just return.
            if (root == nullptr) return;

            // Print the root
            std::cout << root->data << "\t";

            // Print the left subtree
            preorderHelper(root->left);

            // Print the right subtree
            preorderHelper(root->right);
        }

        // This recursive method is used to print the tree in postorder.
        // It takes as parameter the root of the tree to print in postorder.
        void postorderHelper(TreeNode* root) {

            // If tree is empty then there is nothing to print so just return.
            if (root == nullptr) return;

            // Print the left subtree
            postorderHelper(root->left);

            // Print the right subtree
            postorderHelper(root->right);

            // Print the root
            std::cout << root->data << "\t";
        }

    public:

        // Parameterised Construtor
        ExpressionTree(TreeNode* root) {
            mainRoot = root;
        }

        // This method calls the 'inorderHelper' method with the 'mainRoot' as parameter.
        void inorder() {
            if (mainRoot == nullptr) {
                std::cout << "Empty Tree" << std::endl;
            }
            else {
                std::cout << "Inorder: ";
                inorderHelper(mainRoot);
                std::cout << "\n";
            }
        }
        
        // This method is used to print the tree in inorder without recursion.
        void inorderNR() {

            // If tree is empty then there is nothing to print so just return.
            if (mainRoot == nullptr) return;

            else {
                std::cout << "Inorder: ";

                // Initializing a stack which will hold pointers to 'TreeNode' class
                Stack<TreeNode*> stack;

                // Initializing temporary pointer to the value of mainRoot.
                TreeNode* temp = mainRoot;

                // Loop while temp is not nullptr or stack is not empty.
                while (temp != nullptr || stack.isEmpty() != true) {

                    // Follow the left node pointers and push them onto the stack till temp is not nullptr.
                    while (temp != nullptr) {
                        stack.push(temp);
                        temp = temp->left;
                    }

                    // Pop the top element and prints its data.
                    temp = stack.pop();
                    std::cout << temp->data << "\t";

                    // Then visit its right subtree.
                    temp = temp->right;
                }
                std::cout << "\n";
            }
        }

        // This method calls the 'preorderHelper' method with the 'mainRoot' as parameter.
        void preorder() {
            if (mainRoot == nullptr) std::cout << "Empty Tree" << std::endl;
            else {
                std::cout << "Preorder:   ";
                preorderHelper(mainRoot);
                std::cout << "\n";
            }
        }

        // This method is used to print the tree in preorder without recursion.
        void preorderNR() {

            // If tree is empty then there is nothing to print so just return.
            if (mainRoot == nullptr) std::cout << "Empty Tree" << std::endl;

            else {

                std::cout << "Preorder: ";

                // Initializing a stack which will hold pointers to 'TreeNode' class
                Stack<TreeNode*> stack;

                // Initializing temporary pointer to nullptr.
                TreeNode* temp = nullptr;

                // Pushing mainRoot onto the stack.
                stack.push(mainRoot);

                // Loop while stack is not empty
                while (stack.isEmpty() != true) {

                    // Pop the top element and print its data.
                    temp = stack.pop();
                    std::cout << temp->data << "\t";

                    // If its right subtree exists push it onto the stack.
                    if (temp->right) {
                        stack.push(temp->right);
                    }

                    // If its left subtree exists push it onto the stack
                    if (temp->left) {
                        stack.push(temp->left);
                    }
                }
                std::cout << "\n";
            }
        }

        // This method calls the 'postorderHelper' method with the 'mainRoot' as parameter.
        void postorder() {

            if (mainRoot == nullptr) std::cout << "Empty Tree" << std::endl;

            else {
                std::cout << "Postorder:   ";
                postorderHelper(mainRoot);
                std::cout << "\n";
            }
        }

        // This method is used to print the tree in postorder without recursion.
        void postorderNR() {

            // If tree is empty then there is nothing to print so just return.
            if (mainRoot == nullptr) std::cout << "Empty Tree" << std::endl;

            else {

                std::cout << "Postorder: ";

                // Initializing two stacks which will hold pointers to 'TreeNode' class.
                // stack1 will be used to traverse the tree.
                // stack2 will be used to print the tree.
                Stack<TreeNode*> stack1, stack2;

                // Initializing temporary pointer to nullptr.
                TreeNode* temp = nullptr;

                // Pushing mainRoot onto both the stacks
                stack1.push(mainRoot);
                stack2.push(mainRoot);

                // Loop while stack1 is not empty
                while (stack1.isEmpty() != true) {

                    temp = stack1.pop();

                    // If its right subtree exists push it onto both the stacks.
                    if (temp->right) {
                        stack1.push(temp->right);
                        stack2.push(temp->right);
                    }

                    // If its left subtree exists push it onto both the stacks.
                    if (temp->left) {
                        stack1.push(temp->left);
                        stack2.push(temp->left);
                    }
                }

                // After traversing the tree, print the tree in postorder.
                while (stack2.isEmpty() != true) {
                    std::cout << stack2.pop()->data << "\t";
                }
                std::cout << "\n";
            }
        }
};


// Utility Class which will contain methods for constructing expression tree from postfix and prefix. 
class ExpressionTreeConstructor {

    private:
        // Pointer to a stack which will hold pointers to 'TreeNode' class.
        Stack<TreeNode*>* stack;

    public:
        // Default Constructor
        // Creating the stack
        ExpressionTreeConstructor() {
            stack = new Stack<TreeNode*>();
        }

        // Destructor
        ~ExpressionTreeConstructor() {
            delete stack;
        }

        // This method is used to construct an expression tree from postfix or prefix.
        // 'isPrefix' specifies to the method if the expression is prefix or postfix.
        // This method returns a pointer to an object of 'ExpressionTree' class.
        ExpressionTree* construct(char expression[], bool isPrefix) {

            // Calculating the length of the expression.
            int length = std::strlen(expression);

            // If the given expression is prefix reverse it.
            if (isPrefix == true) {
                std::reverse(expression, expression + length);
            }

            // Declaring a few variables.
            char token;
            TreeNode* operand1;
            TreeNode* operand2;

            // Iterating over the exression
            for (int i = 0; i < length; i++) {

                // 'token' is our current character.
                token = expression[i];

                // Checking if the token is an alphabet.
                // If yes then push a node onto the stack
                // with the token as its data. 
                if (isalpha(token) != 0) {
                    stack->push(new TreeNode(token));
                }

                // If the token is not an alphabet then it has to be an operator.
                else {

                    // Pop two nodes from the stack(order depends on whether expression is prefix or postfix) 
                    // and assign them as the left-subtree and right-subtree of the operator node.
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