/*
Create an inordered threaded binary tree. Perform inorder, preorder traversals without recursion and deletion of a node.
 Analyze time and space complexity of algorithm.
*/

#include <bits/stdc++.h>
using namespace std;

class Node {
    int data;
    bool lt, rt;
    Node *left, *right;

    Node(int d) {
        data = d;
        lt = rt = 0;
        left = right = nullptr;
    }

    friend class TBST;
};

class TBST {

    Node *head, *root;

    Node* inSucc( Node *node ) {
        if(node->rt == true)
            return node->right;

        node = node->right;
        while(node->lt == false)
            node = node->left;
        return node;
    }

    Node* inPred(Node *node) {
        if(node->lt == true)
            return node->left;

        node = node->left;
        while(node->rt == false)
            node = node->right;
        return node;
    }

    Node* inOrderSuccessor(Node *node) {
        Node *current = node->right;
        if(node->rt == false) {
            while(current->lt == false)
                current = current->left;
        }
        return current;
    }

    void del(Node *parent, Node *child) {
        // leaf node
        if(child->lt == true and child->rt == true) {
            if(parent->right == child) {
                parent->rt = true;
                parent->right = child->right;
                delete child;
            }
            else {
                parent->lt = true;
                parent->left = child->left;
                delete child;
            }
        }

        // left subtree
        else if(child->lt == false) {
            Node *gc = child->left;
            Node *s = inSucc(child);
            Node *p = inPred(child);

            p->right = s;
            if(parent->right == child)
                parent->right = gc;
            else 
                parent->left = gc;
            delete child;
        }

        // right subtree
        else if(child->rt = false){
            Node *gc = child->right;
            Node *s = inSucc(child);
            Node *p = inPred(child);

            s->left = p;
            if(parent->right == child)
                parent->right = gc;
            else 
                parent->left = gc;
            delete child;
        }

        // two children
        else {
            Node *leftMost = child->right, *LMparent = child;
            while(leftMost->lt == false) {
                LMparent = leftMost;
                leftMost = leftMost->left;
            }

            child->data = leftMost->data;

            del(LMparent, leftMost);
        }
    }

    public: 

    TBST () {
        root = nullptr;

        head = new Node(0);
        head->lt = true;
        head->rt = false;
        head->left = head;
        head->right = head;
    }

    void insert(int data) {
        
        // Tree empty
        if(root == nullptr) {
            root = new Node(data);
            root->lt = root->rt = 1;
            root->left = root->right = head;
            head->left = root;
            head->lt = false;
        }
        
        else {
            Node *curr = root, *parent = nullptr;
            while(true) {
                parent = curr;
                if(data > curr->data) {
                    if(curr->rt == false) {
                        curr = curr->right;
                    }
                    else 
                        break;
                }
                else {
                    if(curr->lt == false) {
                        curr = curr->left;
                    }
                    else 
                        break;
                }
            }

            Node *newNode = new Node(data);
            if(data > parent->data) {
                newNode->rt = parent->rt;
                newNode->right = parent->right;
                newNode->lt = true;
                newNode->left = parent;
                parent->rt = false;
                parent->right = newNode;
            }
            else {
                newNode->lt = parent->lt;
                newNode->left = parent->left;
                newNode->rt = true;
                newNode->right = parent;
                parent->lt = false;
                parent->left = newNode;
            }
        }
    }

    void deletion( int key ) {
        Node *curr = root, *prev = head;
        if(curr == nullptr) {
            cout<<"Tree empty"<<endl;
            return;
        }
        while(curr->data != key) {
            prev = curr;
            if(key < curr->data) {
                if(curr->lt == false) {
                    curr = curr->left;
                }
                else
                    break;
            }
            else {
                if(curr->rt == false) {
                    curr = curr->right;
                }
		else 
		    break;
            }
        }
        del(prev, curr);
    }

    void inOrder() {
        Node *curr = head;
        while(true) {
            curr = inOrderSuccessor(curr);
            if(curr == head) {
                cout<<endl;
                return;
            }
            cout<<curr->data<<" ";
        }
    }
};

int main(){
    TBST t;
    t.insert(50);
    t.insert(60);
	t.insert(30);
	t.insert(10);
	t.insert(20);
	t.insert(40);
	t.insert(80);
	t.insert(75);
    t.inOrder();

    t.deletion(50);
    t.inOrder();

    return 0;
}
