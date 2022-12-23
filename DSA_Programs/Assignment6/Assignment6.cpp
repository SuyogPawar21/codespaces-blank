#include <iostream>

class TreeNode {
    public:
        int data;
        TreeNode* left;
        TreeNode* right;
        bool lbit, rbit;

        TreeNode() {
            this->data = 0;
            left = right = nullptr;
            lbit = rbit = true;
        }

        TreeNode(int data) {
            this->data = data;
            left = right = nullptr;
            lbit = rbit = true;
        }

        TreeNode(int data, TreeNode* left, TreeNode* right) {
            this->data = data;
            this->left = left;
            this->right = right;
            lbit = rbit = false;
        }
};


class InorderThreadedTree {
    private:
        TreeNode* head;
        TreeNode* root;

        TreeNode* insertHelper(TreeNode* root, int data) {
            if (!root) return new TreeNode(data, head, head);
            else {
                TreeNode* previous = nullptr;
                TreeNode* current = root;
                while (true) {
                    if (current->data > data) {
                        if (current->lbit == false) {
                            current->left = new TreeNode(data, current->left, current);
                            current->lbit = true;
                            break;
                        }
                        else {
                            previous = current;
                            current = current->left;
                        }
                    }
                    else {
                        if (current->rbit == false) {
                            current->right = new TreeNode(data, current, current->right);
                            current->rbit = true;
                            break;
                        }
                        else {
                            previous = current;
                            current = current->right;
                        }
                    }
                }
                return root;
            }
        }

    public:
        InorderThreadedTree() {
            head = new TreeNode();
            head->left = root;
            head->right = head;
            head->lbit = true;
            head->rbit = false;
        }

        void insert(int data) {
            root = insertHelper(root, data);
        }

        void inorderNR() {
            if (!root) {
                std::cout << "Empty Tree" << std::endl;
            }
            else {
                std::cout << "Inorder: ";
                TreeNode* temp = root;
                while (temp->lbit == true) {
                    temp = temp->left;
                }
                while (temp != head) {
                    std::cout << temp->data << "\t";
                    if (temp->rbit == false) {
                        temp = temp->right;
                    }
                    else {
                        temp = temp->right;
                        while (temp->lbit == true) {
                            temp = temp->left;
                        }
                    }
                }
                std::cout << "\n";
            }
        }
};


int main() {
    InorderThreadedTree* tree = new InorderThreadedTree();
    tree->insert(10);
    tree->insert(5);
    tree->insert(15);
    tree->insert(20);
    tree->insert(1);
    tree->inorderNR();
}