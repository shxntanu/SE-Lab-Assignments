/*
Author - Shantanu Wable

Create an inordered threaded binary tree. Perform inorder, preorder traversals without 
recursion and deletion of a node.
Analyze time and space complexity of algorithm.
*/

#include <bits/stdc++.h>
using namespace std;

class Node
{

    Node* left;
    bool lthread;
    int data;
    bool rthread;
    Node*right;

public:
	Node(int d)
    {
		data=d;
		left=right=NULL;
		lthread=rthread=true;
	}

	friend class TBST;

};

class TBST
{
public:
	Node* root;

	TBST()
    {
		root = NULL;
		cout << "Creation of Threaded Binary Search Tree" << endl;
        cout << "Enter no. of nodes: " << endl;
        int n;
        cin >> n;
        cout << "Enter values of each node: " << endl;
        int a[n];
        for(int i=0;i<n;i++)
        {
        	cin>>a[i];
        	insert(a[i]);
        }
	}

    void insert(int key);
    void inorder();
    void preorder();
    void postorder();
    Node* leftMost(Node* temp);
    Node* inorderSuccessor(Node *temp);
    Node* inorderPredecessor(Node* temp);
    void deletion(int key);
};

int main()
{
	TBST tree;
	while(true)
    {
		cout<<"Implementation of Threaded BST"<<endl<<endl;
		cout<<"1. Traversal of Threaded BST"<<endl;
		cout<<"2. Delete a node from Threaded BST"<<endl;
		cout<<"3. Exit"<<endl;
		int res;
		cout<<"Enter your choice : ";
		cin>>res;
		if(res==1)
        {
			cout<<"Inorder :";
			tree.inorder();
			cout<<"Preorder :";
			tree.preorder();
			cout<<"Postorder :";
			tree.postorder();
			cout<<endl;
		}
		else if(res==2)
        {
			int n;
			cout<<"Enter a no. to delete from threaded BST : ";
			cin>>n;
			tree.deletion(n);
			cout<<"After deletion : "<<endl;
			cout<<"Inorder :";
			tree.inorder();
			cout<<"Preorder :";
			tree.preorder();
			cout<<"Postorder :";
			tree.postorder();
			cout<<endl;
		}
		else if(res==3)
        {
			cout<<"Terminating program"<<endl;
			break;
		}
		else
            continue;
	}
	return 0;
}

void TBST::insert(int key)
{
    Node* newNode=new Node(key);

    // If tree is empty
    if(root==NULL)
    {
        root=newNode;
        return;
    }

    Node* temp=root;
    Node* parent=NULL;

    // Searching for the place to insert the node
    while(temp!=NULL)
    {
        if(key==temp->data)
        {
            return;
        }
        parent=temp;
        if(key<temp->data)
        {
            if(temp->lthread==false)
                temp=temp->left;
            else 
                break;
        }
        else
        {
            if(temp->rthread==false) 
                temp=temp->right;
            else
                break;
        }
    }

    // Inserting node as left child
    if(key<temp->data)
    {
        newNode->left=parent->left;
        newNode->right=parent;
        parent->lthread=false;
        parent->left=newNode;
    }

    // Inserting node as right child
    else
    {
        newNode->left=parent;
        newNode->right=parent->right;
        parent->rthread=false;
        parent->right=newNode;
    }
}

void TBST::deletion(int key)
{
    Node* temp=root;
    Node* parent=NULL;

    // Searching for the node
    while(temp!=NULL){
        if(key==temp->data){
            break;
        }
        parent=temp;
        if(key<temp->data){
            if(temp->lthread==false) temp=temp->left;
            else break;
        }
        else{
            if(temp->rthread==false) temp=temp->right;
            else break;
        }
    }

    // Node not found
    if(key!=temp->data){
        cout<<key<<" not found"<<endl;
        return;
    }

    // Node to be deleted is a leaf node
    else if (temp->lthread == true && temp->rthread == true)
    {
        if (parent == NULL)
            root = NULL;

        else if (temp == parent->left) {
            parent->lthread = true;
            parent->left = temp->left;
        }
        else {
            parent->rthread = true;
            parent->right = temp->right;
        }
        delete temp;
        cout<<key<<" Successfully deleted"<<endl;
        return;
    }

    // Node to be deleted has only one child
    else if((temp->lthread==true && temp->rthread==false) || (temp->lthread==false && temp->rthread==true)){
        Node* child;
        if(temp->lthread==false)
            child=temp->left;
        else
            child=temp->right;
        if(parent==NULL){
            root=child;
        }
        if(temp==parent->left){
            parent->left=child;
        }
        else parent->right=child;
        Node* s=inorderSuccessor(temp);
        Node* p=inorderPredecessor(temp);

        if(temp->lthread==false){
            p->right=s;
        }
        else{
            s->left=p;
        }
        delete temp;
        cout<<key<<" Successfully deleted"<<endl;
        return;
    }

    // Node to be deleted is an internal node
    else
    {
        Node* s=inorderSuccessor(temp);
        int t=s->data;
        deletion(s->data);
        temp->data=t;
    }
}

Node* TBST::leftMost(Node *temp)
{
    if(temp==NULL) return NULL;
    while(temp->left!=NULL && temp->lthread==false)
    {
        temp=temp->left;
    }
    return temp;
}

Node* TBST::inorderSuccessor(Node *temp)
{
    if(temp->rthread==true){
        return temp->right;
    }
    else{
        temp=temp->right;
        return leftMost(temp);
    }
}

Node* TBST::inorderPredecessor(Node *temp)
{
        return temp->left;
}

void TBST::inorder()
{
    Node* temp=leftMost(root);
    while(temp!=NULL)
    {
        cout<<temp->data<<" ";
        if(temp->rthread==true) temp=temp->right;
        else 
        {
            temp=temp->right;
            temp=leftMost(temp);
        }
    }
    cout<<endl;
}

void TBST::preorder()
{
    if(root==NULL) return;
    Node* temp=root;
    while(temp!=NULL){
        cout<<temp->data<<" ";
        if(temp->lthread==false)
            temp=temp->left;
        else if(temp->rthread==false)
            temp=temp->right;
        else{
            while(temp!=NULL && temp->rthread==true)
                temp=temp->right;
            if(temp!=NULL)
                temp=temp->right;
        }
    }
    cout<<endl;
}

void TBST::postorder()
{
    Node* temp=root;
    stack<Node*> s;
    stack<Node*> out;
    s.push(temp);
    while(!s.empty())
    {
        temp=s.top();
        s.pop();
        out.push(temp);
        if(temp->lthread==false){
            s.push(temp->left);
        }
        if(temp->rthread==false){
            s.push(temp->right);
        }
    }
    while(!out.empty())
    {
        temp=out.top();
        out.pop();
        cout<<temp->data<<" ";
    }
    cout<<endl;
}
