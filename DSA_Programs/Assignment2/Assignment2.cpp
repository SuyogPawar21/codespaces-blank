/**
 * @author SuyogPawar
**/

// Various header files
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>


// This is a constant defining the max size an expression can have.
static const int MAXSIZEOFEXPRESSION = 30;


// Generic Stack ('T' can be anything int, float, char etc.)
template <class T> class Stack {

    // Node which will store data of type 'T' and pointer to the next Node.
    class Node {

        public:
            T data;
            Node* next;

            // Two Constructors
            Node(T data, Node* next) {
                this->data = data;
                this->next = next;
            }

            Node(T data) {
                this->data = data;
                this->next = nullptr;
            }
    };

    private:
        // 'head' is a pointer to the first Node in the linked list.
        Node* head;

        // 'size' stores the current size of the linked list. 
        int size;
        
        //  Recursive Method to delete all the Nodes of the linked list from memory.
        // This method is called when the destructor is called or when we use the 'delete' keyword. 
        void delLinkedList(Node* head) {

            // if the linked list is empty there is nothing to delete so just return;
            if (head == nullptr) return;

            else {
                // else if the linked list exists then before deleting the head pointer,
                // delete its next Node.
                delLinkedList(head->next);
                delete head;
            }
        }

    public:
        // Default Constructor.
        Stack() {
            head = nullptr;
            size = 0;
        }

        // This method returns true if size is equal to 0 else returns false;
        bool isEmpty() {
            return size == 0 ;
        }

        // This method pushes data of type 'T' onto the stack.
        void push(T data) {

            // If the linked list is empty then create a new Node with the data and
            // assign it to be the new head.
            if (isEmpty() == true) {
                head = new Node(data);
            }

            // Else create a new Node and let its 'next' pointer point 
            // to the current head and let it be the new head.
            // Also increment the value of size by 1.
            else {
                Node* temp = new Node(data, head);
                head = temp;
            }
            
            size++;
        }

        // This method removes an element from the stack and returns its value.
        T pop() {

            // If stack is empty there is nothing to remove and return, so return NULL.
            if (isEmpty() == true) {
                return NULL;
            }

            // Else assign the address of 'head' Node to 'temp' pointer
            // and let 'head' pointer point to next Node in the linked list.
            // Put the value of the 'temp' Node in a variable, delete 'temp'
            // Node, decrement size by 1 and return the value of 'temp' Node. 
            else {
                Node* temp = head;
                head = head->next;
                T value = temp->data;
                delete temp;
                size--;
                return value;
            }
        }

        // This method returns the value of the 'head' Node.
        T top() {

            // If stack is empty that means there is nothing to return, so return NULL.
            if (isEmpty() == true) {
                return NULL;
            }

            // Else return value of 'head' Node.
            else return head->data;
        }

        // This method returns the current size of the stack or linked list.
        int len() {
            return size;
        }

        // Destructor 
        ~Stack() {
            delLinkedList(head);
        }
};


// This class is a utility class which contains methods for expression conversion and evaluation.
class ExpressionsUtlilty {

    private:
        // Two stacks, one for chars, other for integers.
        // Note that these are only pointers and that the actual stacks
        // will be created at runtime i.e when the constructor of this class will be called.
        Stack<char>* stackChar;
        Stack<int>* stackInt;


        // This method reverses an expression and inverts the brackets after reversing if any.
        // For example- (A + B) ---> (B + A)
        void reverseExpression(char expression[]) {

            int length = strlen(expression);
            std::reverse(expression, expression+length);
            for (int i = 0; i < length; i++) {
                if (expression[i] == '(') {
                    expression[i] = ')';
                }
                else if (expression[i] == ')') {
                    expression[i] = '(';
                }
                else continue;
            }
        }

        // This method returns the priority of an character in the expression.
        int priority(char c) {
            if (c == '^') return 3;
            else if (c == '*' || c == '/') return 2;
            else if (c == '+' || c == '-') return 1;
            else return 0;
        }

    public:
        // Default Constructor
        ExpressionsUtlilty() {
            stackChar = new Stack<char>();
            stackInt = new Stack<int>();
        }

        // This method converts infix expression to postfix expression.
        void infixToPostfix(char infix[], char postfix[]) {

            // 'positionInPostFix' keeps track of the position at which we need to
            // insert the next character from the infix expression or stack.
            int positionInPostfix = 0;
            char token;

            // Iterating over the infix expression till the '\0' character.
            for (int position = 0; infix[position] != '\0'; position++) {
                
                // 'token' is our current character.
                token = infix[position];

                // Checking if the token is an alphabet using the 'isalpha(char c)' method
                // and putting it in the postfix expression if it is.
                // 'isalpha(char c)' returns any non-zero number if 'c' is an alphabet.
                // else it returns 0 if 'c' is not an alphabet.
                if (isalpha(token) != 0) {
                    postfix[positionInPostfix++] = token;
                }

                // If token is a opening bracket then push it onto the stack.
                else if (token == '(') {
                    stackChar->push(token);
                }

                // If token is a closing bracket then pop elements from the stack and
                // place them in the postfix expression till we get an '(' at the top
                // of the stack. Then pop the '(' as well.
                else if (token == ')') {
                    while (stackChar->top() != '(') {
                        postfix[positionInPostfix++] = stackChar->pop();
                    }
                    stackChar->pop();
                }

                // If the token is not an alphabet or closing/opening bracket then it must be a operator.
                // If the stack is empty then push the operator onto the stack.
                // OR if the operator has more priority than the operator/character at the top of the stack then
                // push the operator onto the stack. 
                else if (stackChar->isEmpty() == true || priority(token) > priority(stackChar->top())) {
                    stackChar->push(token);
                }

                // Else if the stack is not empty and the priority of the operator is less than or equal to
                // the priority of the operator at the top of the stack then pop the top element of 
                // the stack and place it in the postfix expression till either the stack is empty 
                // or the priority of the operator at the top is less than the current operator.
                // Then push the current operator onto the stack.
                 
                else {
                    while (stackChar->isEmpty() == false && priority(token) <= priority(stackChar->top())) {
                        postfix[positionInPostfix++] = stackChar->pop();
                    }
                    stackChar->push(token);
                }
            }

            // After iterating over the infix expression, pop all elements remaining in the 
            // stack and place them in the postfix expression.
            while (stackChar->isEmpty() == false) {
                postfix[positionInPostfix++] = stackChar->pop();
            }

            // Adding the '\0' character to denote the end of the expression.
            postfix[positionInPostfix++] = '\0';
        }

        // To get the prefix expression of an infix expression we do the following-
        // 1) Reverse the infix expression(Invert the brackets).
        // 2) Obtain the postfix expression of the reversed infix expression.
        // 3) Reverse the postfix exression to get the desired prefix expression.
        void infixToPrefix(char infix[], char prefix[]) {

            reverseExpression(infix);
            infixToPostfix(infix, prefix);
            int length = strlen(prefix);
            std::reverse(prefix, prefix+length);
        }

        // This method evaluates an expression and returns the answer.
        // 'isPrefix' is a boolean variable which specifies to the method whether
        // the given expression is prefix or postfix.
        int evaluate(char expression[], bool isPrefix) {
            
            // Calculating length of expression and declaring a bunch variables.
            int length = strlen(expression), temp, operand1, operand2;

            // If the given expression is prefix then reverse it.
            // For example- +ab ---> ba+
            if (isPrefix == true) {
                std::reverse(expression, expression + length);
            }

            // Iterating over the expression.
            for (int i = 0; i < length; i++) {

                // Checking if the current character is an alphabet.
                // If yes then getting its value from the user and
                // pushing that value onto the stack.
                if (isalpha(expression[i]) != 0) {
                    std::cout << "Enter Value of " << expression[i] << ": ";
                    std::cin >> temp;
                    stackInt->push(temp);
                }

                // If the current character is not an alphabet then it has to be an operator.
                // So we pop two elements from the stack and operate on them according to the
                // operator and push the result onto the stack.
                else {

                    // For example- Postfix: ab-
                    // Here operand1 = b and operand2 = a
                    // Therefore result = operand2 - operand1 = a - b
                    if (isPrefix == false) {
                        operand1 = stackInt->pop();
                        operand2 = stackInt->pop();
                    }

                    // For example- Prefix: ab
                    // Expression after reversing: ba-
                    // Here operand2 = a and operand1 = b
                    // Therefore result = operand2 - operand1 = a - b
                    else {
                        operand2 = stackInt->pop();
                        operand1 = stackInt->pop();
                    }

                    // Switch case for different operators
                    switch (expression[i]) {
                        case '+':
                            stackInt->push(operand2 + operand1);
                            break;
                    
                        case '-':
                            stackInt->push(operand2 - operand1);
                            break;

                        case '*':
                            stackInt->push(operand2 * operand1);
                            break;

                        case '/':
                            stackInt->push(operand2 / operand1);
                            break;

                        case '^':
                            stackInt->push(std::pow(operand2, operand1));
                            break;            
                        default:
                            break;
                    }
                }
            }

            if (isPrefix == true) {
                std::cout << "Prefix Evaluation: ";
            }
            else {
                std::cout << "Postfix Evaluation: ";
            }

            // Returning final result
            return stackInt->pop();
        }

        // Destructor
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
    std::cout << "Infix: ";
    std::cin >> infix;
    e.infixToPostfix(infix, postfix);
    std::cout << "\nPostfix: " << postfix << std::endl;
    std::cout << e.evaluate(postfix, false) << std::endl;
    e.infixToPrefix(infix, prefix);
    std::cout << "\nPrefix: " << prefix << std::endl;
    std::cout << e.evaluate(prefix, true) << std::endl;
    return 0;
}