/*
Source : Advait Naik

Create an inordered threaded binary search tree. Perform inorder, preorder
traversals without recursion and deletion of a node. Analyze time and
space complexity of the algorithm.
*/

#include <iostream>
using namespace std;

class Node{
    int data;
    Node *left , *right;
    bool rightThread;

public:
    //parameterized constructor
    Node(int i){
        this -> data = i;
        this -> left = nullptr;
        this -> right = nullptr;
        this -> rightThread = false;
    }

    friend class TBST;
};

class TBST{
    Node *root;

public:
    //parameterized constructor
    TBST(int i){
        this -> root = new Node(i);
    }
    
    //inserts a node as per insertion in BST
    void insert(int i){
        Node *current = this -> root;
        Node *previous = nullptr;

        while(current!=nullptr){
            previous = current;
            if(i < current -> data){
                current = current -> left;
            }
            else{
                if(!current -> rightThread){
                    current = current -> right;
                }
                else{
                    break;
                }
            }
        }

        if(i < previous -> data){
            Node *newnode = new Node(i);
            previous -> left = newnode;
            newnode -> right = previous;
            newnode -> rightThread = true;
        }
        else{
            Node *newnode = new Node(i);
            newnode -> right = previous -> right;
            newnode -> rightThread = previous -> rightThread;
            previous -> rightThread = false;
            previous -> right = newnode;
        }
    }

    //inorder display of the existing tree
    void inorderTraversal(){
        cout<<"The inorder traversal of the existing tree is...."<<endl;
        Node *current = this -> root;

        //get the smallest node in tree i.e. leftmost
        while(current -> left != nullptr){
            current = current -> left;
        }

        while(true) {
            cout<<current -> data<<" ";

            //leaf node
            if(current -> left == nullptr && current -> right == nullptr){
                cout<<endl;
                return;
            }

            //inorder successor present
            if(current -> rightThread){
                current = current -> right;
            }

            //right child is not present
            else if(current -> right == nullptr){
                return;
            }

            //smallest node in right subtree
            else{
                current = current -> right;
                while(current -> left != nullptr){
                    current = current -> left;
                }
            }
        }
    }

    //preorder display of the existing tree
    void preorderTraversal(){
        cout<<"The preorder traversal of the existing tree is...."<<endl;
        Node *current = this -> root;
        while(true){
            cout<<current -> data<<" ";

            //left child present
            if(current -> left){
                current = current -> left;
            }

            //right child or inorder successor present
            else if(current -> right){
                while (current->rightThread)
                {
                    current = current -> right;
                }
                if (current -> right)
                {
                    current = current -> right;
                }
                else
                {
                    return;
                }
            }

            //max element node reached and printed it
            else{
                cout<<endl;
                return;
            }
        }        
    }    
    
    void deleteNode(int key){
        Node *current = this -> root;
	    Node *previous = nullptr;
	    while( true ){
		    if( current -> left == nullptr && current -> rightThread ) {
		    	break;
		    }
		    if (current -> data > key) {
			    // Go left
		    	previous = current;
			    current = current -> left;
		    }
		    else if( current -> data < key ) {
			    // Go right if rightThread is False
		    	// We wish to travel down the tree,
		    	// if we encounter a thread, break the loop (as we've encountered a leaf node)
			    if (!(current -> rightThread)) {
				    previous = current;
				    current = current->right;
			    }
			    else {
				    break;
			    }
		    }
		    else {
			    break ;
		    }
	    }

	    cout << "data: " << current -> data << "\n" ;
	    cout << "rightThread: " << current -> rightThread << "\n" ; 

	    cout << "prev data: " << previous -> data << "\n" ;
	    cout << "prev rightThread: " << previous -> rightThread << "\n" ; 
 

	    if( current -> left == nullptr  && (current -> rightThread) ) {
		    cout << "Leaf Node deletion" << "\n" ; 
		    // Leaf node deletion
		    if( previous -> left == current ) {
		    	cout << "Left child delete" << "\n" ; 
		    	previous -> left = nullptr ;
	    	}
		    else if( previous -> right == current ) {
			    previous -> rightThread = true ;
			    previous -> right = current -> right ;
		    }
		    delete current ;
	    }
	    else if( current -> left != nullptr && current -> right != nullptr && !(current -> rightThread) ) {
		    cout << "Two children deletion" << "\n" ; 
		    // current has two children
		    Node* minInRightTree = current -> right ; 
		    Node* newParent = current ; 
		    while( minInRightTree -> left != nullptr ) {
			    newParent = minInRightTree ;
			    minInRightTree = minInRightTree -> left ; 
		    }
		    int temp = minInRightTree -> data ; 
		    minInRightTree -> data = current -> data ; 
		    current -> data = temp ; 

		    previous = current ; 
		    current = minInRightTree ; 
		
		    if( current -> left != nullptr ) {
			    current -> left -> right = previous ; 
			    previous -> left = current -> left ; 
		    }
		    else if( current -> right != nullptr ) {
			    previous -> right = current -> right ; 
		    }

		    delete minInRightTree ; 
	    }
	    else {
		    cout << "Single Child deletion" << "\n" ; 
		    if( current -> left != nullptr ) {
		    	current -> left -> right = previous ; 
			    previous -> left = current -> left ; 
		    }
		    else if( current -> right != nullptr ) {
			    previous -> right = current -> right ; 
		    }
		    delete current ;
	    }
    }
};

int main(){
    TBST t(25);
    t.insert(12);
    t.insert(4);
    t.insert(35);
    t.insert(67);
    t.insert(43);
    t.deleteNode(12);
    t.inorderTraversal();

    return 0;
}
