/*
Author - Shantanu Wable

Beginning with an empty binary tree, Construct binary search tree by inserting
the values in the order given. After constructing a binary tree, perform the
following operations on it -
1. Perform inorder, preorder and postorder traversal
2. Change a tree so that the roles of the left and right pointers are swapped at every node
3. Find the height of the tree
4. Copy this tree to another tree (operator =)
5. Count number of leaves, number of internal nodes
6. Erase all nodes in a binary tree

(implement both recursive and iterative methods)
*/

#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>
using namespace std;

class Node {
    int data;
    Node *left, *right;

    Node() {
        data = 0;
        left = right = nullptr;
    }

    Node(int d) {
        data = d;
        left = right = nullptr;
    }

    friend class BT;
};

class BT {

    Node* buildTree (Node *root) {
        cout<<"\nData (-1: Null): ";
        int d;
        cin>>d;
        root = new Node(d);

        if(d == -1)
            return nullptr;

        cout<<"Enter data for left of "<<d<<endl;
        root->left = buildTree(root->left);
        cout<<"Enter data for right of "<<d<<endl;
        root->right = buildTree(root->right);
    }

    void rswapAllNodes(Node *root)
    {
        if(root == nullptr)
            return;
        
        if(root->left || root->right) // If either of left or right of root exists
        {
            Node *temp = root->left;
            root->left = root->right;
            root->right = temp;
        }
        rswapAllNodes(root->right); // Continue in right subtree
        rswapAllNodes(root->left);  // Continue in left subtree
    }

    void iswapAllNodes(Node* root) {
        if (root == nullptr)
            return;

        std::stack<Node*> nodeStack;
        nodeStack.push(root);

        while (!nodeStack.empty()) {
            Node* current = nodeStack.top();
            nodeStack.pop();

            if (current->left || current->right) {
                Node* temp = current->left;
                current->left = current->right;
                current->right = temp;
            }

            if (current->right)
                nodeStack.push(current->right);

            if (current->left)
                nodeStack.push(current->left);
        }
    }

    Node* rClone(Node *root) {
        if(root == nullptr)
            return nullptr;

        Node *rootCopy = new Node(root->data);
        rootCopy->right = rClone(root->right);
        rootCopy->left = rClone(root->left);

        return rootCopy;
    }

    Node* iClone(Node* root) {
        if (root == nullptr)
            return nullptr;

        stack<Node*> nodeStack;
        unordered_map<Node*, Node*> cloneMap;

        Node* rootCopy = new Node(root->data);
        cloneMap[root] = rootCopy;
        nodeStack.push(root);

        while (!nodeStack.empty()) {
            Node* current = nodeStack.top();
            nodeStack.pop();

            Node* currentCopy = cloneMap[current];

            if (current->right) {
                Node* rightCopy = new Node(current->right->data);
                currentCopy->right = rightCopy;
                cloneMap[current->right] = rightCopy;
                nodeStack.push(current->right);
            }

            if (current->left) {
                Node* leftCopy = new Node(current->left->data);
                currentCopy->left = leftCopy;
                cloneMap[current->left] = leftCopy;
                nodeStack.push(current->left);
            }
        }

        return rootCopy;
    }

    int rHeight(Node *node) {
        if(node == nullptr)
            return 0;

        int l = rHeight(node->left);
        int r = rHeight(node->right);

        return max(l,r) + 1;
    }

    int iHeight(Node* root) {
        if (root == nullptr)
            return 0;

        queue<Node*> nodeQueue;
        nodeQueue.push(root);
        int height = 0;

        while (!nodeQueue.empty()) {
            int size = nodeQueue.size();

            while (size > 0) {
                Node* current = nodeQueue.front();
                nodeQueue.pop();

                if (current->left)
                    nodeQueue.push(current->left);

                if (current->right)
                    nodeQueue.push(current->right);

                size--;
            }

            height++;
        }

        return height;
    }

    int rLeafCount(Node *root) {
        if(root == NULL)
            return 0;
        // Condition for leaf Node
        else if(root->left == NULL and root->right == NULL)
            return 1;
        else
            return rLeafCount(root->right) + rLeafCount(root->left);
    }

    int iLeafCount(Node* root) {
        if (root == nullptr)
            return 0;

        stack<Node*> nodeStack;
        nodeStack.push(root);
        int leafCount = 0;

        while (!nodeStack.empty()) {
            Node* current = nodeStack.top();
            nodeStack.pop();

            if (current->left == nullptr && current->right == nullptr)
                leafCount++;

            if (current->right)
                nodeStack.push(current->right);

            if (current->left)
                nodeStack.push(current->left);
        }

        return leafCount;
    }

    void rDeleteTree(Node* root) {
        if (root == NULL) return;

        rDeleteTree(root->left);
        rDeleteTree(root->right);

        cout << "\n Deleting node: " << root->data;
        delete root;
    }

    void iDeleteTree(Node* root) {
        if (root == nullptr)
            return;

        std::stack<Node*> nodeStack;
        nodeStack.push(root);

        while (!nodeStack.empty()) {
            Node* current = nodeStack.top();
            nodeStack.pop();

            if (current->right)
                nodeStack.push(current->right);

            if (current->left)
                nodeStack.push(current->left);

            cout << "\n Deleting node: " << current->data;
            delete current;
        }
    }

    void rpreorder(Node *root)
    {
        if(root == NULL)
            return;

        cout<<root->data<<" ";
        rpreorder(root->left);
        rpreorder(root->right);
    }

    void rinorder(Node *root)
    {
        if(root == NULL)
            return;

        rinorder(root->left);
        cout<<root->data<<" ";
        rinorder(root->right);
    }

    void rpostorder(Node *root)
    {
        if(root == NULL)
            return;

        rpostorder(root->left);
        rpostorder(root->right);
        cout<<root->data<<" ";
    }

    public: 

    Node *root = nullptr;
    
    BT() {
        cout<<"Enter Data for root"<<endl;
        buildTree(root);
    }

    void operator = (BT &Tree) {
        this->root = iClone(Tree.root);
    }

    void iinorder() {
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

    void ipreorder() {
        if(root == nullptr)
            return;

        stack<Node*> Stack;
        Stack.push(root);
        while(!Stack.empty()) {
            Node *poppedNode = Stack.top();
            Stack.pop();
            cout<<poppedNode->data<<" ";
            if(poppedNode->right)
                Stack.push(poppedNode->right);
            if(poppedNode->left)
                Stack.push(poppedNode->left);
        }
    }

    void ipostorder() {
        stack<Node*> s1, s2;
        s1.push(root);
        while(!s1.empty()) {
            Node *temp = s1.top();
            s1.pop();
            s2.push(temp);
            if(temp->right)
                s1.push(temp->right);
            if(temp->left)
                s1.push(temp->left);
        }
        while(!s2.empty()) {
            cout<<s2.top()->data<<" ";
            s2.pop();
        }
    }
};

int main() {
    BT Tree;
    return 0;
}
