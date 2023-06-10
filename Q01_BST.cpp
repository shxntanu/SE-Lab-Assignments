/*
Author - Shantanu Wable

Beginning with an empty binary search tree, Construct binary search tree by inserting
the values in the order given. After constructing a binary tree -
i.      Insert new node,
ii.     Find number of nodes in longest path from root,
iii.    Minimum data value found in the tree,
iv.     Change a tree so that the roles of the left and right pointers are swapped at every node,
v.      Search a value.

*/

#include <iostream>
#include <stack>
using namespace std;

class Node {
    int data;
    Node *left, *right;

    Node() {
        data =0;
        left = right = nullptr;
    }

    Node(int d) {
        data =d;
        left = right = nullptr;
    }

    friend class BST;
};

class BST {
    Node *root = nullptr;

    int height(Node *node) {
        if(node == nullptr)
            return 0;

        int l = height(node->left);
        int r = height(node->right);

        return max(l,r) + 1;
    }

    void swapAllNodes(Node *node) {
        if(node == nullptr)
            return;

        if(node->left or node->right) {
            Node *temp = node->left;
            node->left = node->right;
            node->right = temp;
        }

        swapAllNodes(node->right);
        swapAllNodes(node->left);
    }

    void ipreorder() {
        Node *curr = root;
        stack<Node*> Stack;

        while(!Stack.empty() or curr != nullptr) {
            while(curr != nullptr) {
                Stack.push(curr);
                curr = curr->left;
            }
            curr = Stack.top();
            Stack.pop();
            cout<<curr->data<<" ";
            curr = curr->right;
        }
    }

    Node* minValueNode (Node *node) {
        Node *curr = node;
        while(curr->left != nullptr)
            curr = curr->left;

        return curr;
    }

    Node* deleteSubTree(Node *root, int key) {

        if(key > root->data)
            root->right = deleteSubTree(root->right, key);

        else if(key < root->data)
            root->left = deleteSubTree(root->left, key);

        else {
            if(root->right == nullptr or root->left == nullptr) {
                Node *temp = root->left ? root->left : root->right;

                if(temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }

                else {
                    root->data = temp->data;
                    root->left = root->right = nullptr;
                }

                delete temp;
            }

            else {
                Node *temp = minValueNode(root->right);
                root->data = temp->data;

                root->right = deleteSubTree(root->right, temp->data);
            }
        }
        
        return root;
    }

    public: 

    void insert(int d) {
        Node *curr = root, *prev = nullptr;

        if(curr == nullptr) {
            root = new Node(d);
        }

        else {
            while(curr != nullptr) {
                if(d > curr->data) {
                    prev = curr;
                    curr = curr->right;
                }

                else if( d < curr->data ) {
                    prev = curr;
                    curr = curr->left;
                }

                else {
                    cout<<"Node already exists."<<endl;
                    return;
                }
            }
            
            if( d > prev->data ) {
                Node *temp = new Node(d);
                prev->right = temp;
            }

            else {
                Node *temp = new Node(d);
                prev->left = temp;
            }
        }
    }

    void search(int d) {
        Node *curr = root;
        while(curr != nullptr) {
            if(d > curr->data)
                curr = curr->right;
            else if(d < curr->data)
                curr = curr->left;
            else {
                cout<<"\nNode found"<<endl;
                return;
            }
        }
        cout<<"\nNode does not exist"<<endl;
    }

    void del(int key){
        root = deleteSubTree(root, key);
    }

    void getHeight() {
        cout<<"\nNumber of nodes in the longest path from root are: "<<height(root) + 1<<endl;
    }

    void getMinValue() {
        cout<<"\nMinimum value in the tree: "<<minValueNode(root)->data<<endl;
    }

    void getAscending() {
        cout<<"\nValues in ascending order are: ";
        ipreorder();
    }

    void printSwapped() {
        swapAllNodes(root);
        cout<<"\nTree when swapped: ";
        ipreorder();
    }
};

int main() {
    BST tree;

    tree.insert(50);
    tree.insert(70);
    tree.insert(60);
    tree.insert(20);
    tree.insert(90);
    tree.insert(10);
    tree.insert(40);
    tree.insert(100);

    tree.getAscending();

    tree.del(10);

    tree.getAscending();
    tree.getHeight();

    BST tree2;

    tree2.insert(10);
    tree2.insert(12);
    tree2.insert(5);
    tree2.insert(4);
    tree2.insert(20);
    tree2.insert(8);
    tree2.insert(7);
    tree2.insert(15);
    tree2.insert(13);

    tree2.getAscending();
    tree2.getHeight();
    
    return 0;
}
