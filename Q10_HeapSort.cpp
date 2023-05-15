/*
Credits - Shubham Panchal (@Shubham0204)
Implement the Heap Sort algorithm demonstrating the Heap / Shell data structure with 
modularity of programming language.
*/

#include <iostream>
#include <queue>
using namespace std ; 

class Node {

    int val ; 
    Node* left = nullptr ; 
    Node* right = nullptr ;

    public:

    friend class Heap ;   

} ;

class Heap {

    Node* ROOT = nullptr ;
    int numNodes = 0 ; 

    public:

    void insert( int keys[] , int n ) {
        // Levelwise insertion of nodes
        // keys is an array that represents the binary tree
        // n is the number of nodes
        numNodes = n ; 

        // Create ROOT node and assign it val = keys[0]
        Node* newNode = new( Node ) ; 
        newNode -> val = keys[ 0 ] ; 
        ROOT = newNode ; 

        // Perform level-wise traversal and insert nodes with values
        // from keys
        int i = 0 ; 
        queue<Node*> q ; 
        q.push( ROOT ) ;

        while( i < n - 1 ) {

            // Pop node from queue
            Node* poppedNode = q.front() ; 
            q.pop() ; 

            // Add left child and increment i
            Node* leftNode = new( Node ) ; 
            leftNode -> val = keys[ ++i ] ; 
            poppedNode -> left = leftNode ; 
            q.push( poppedNode -> left ) ;

            // Add right child and increment i
            Node* rightNode = new( Node ) ; 
            rightNode -> val = keys[ ++i ] ; 
            poppedNode -> right = rightNode ; 
            q.push( poppedNode -> right ) ; 

        }
    }

    void breadthFirst() {
        queue<Node*> q ; 
        q.push( ROOT ) ;
        while( !q.empty() ) {
            Node* poppedNode = q.front() ;
            cout << poppedNode -> val << " " ; 
            q.pop() ; 
            if( poppedNode -> left != nullptr ) {
                q.push( poppedNode -> left ) ; 
            }
            if( poppedNode -> right != nullptr ) {
                q.push( poppedNode -> right ) ;
            }
        }
        cout << "\n" ; 
    }

    Node* heapify( Node* node ) {
        if( node == nullptr ) {
            return nullptr;
        }
        node -> left = heapify( node -> left ) ;   // Heapify left subtree of node
        node -> right = heapify( node -> right ) ; // Heapify right subtree of node 
        if( node -> left != nullptr && node -> left -> val > node -> val ) {
            // Left child's value is greater than root's value
            int temp = node -> left -> val ; 
            node -> left -> val = node -> val ; 
            node -> val = temp ; 
        }
        if( node -> right != nullptr && node -> right -> val > node -> val ) {
            // Right child's value is greater than root's value
            int temp = node -> right -> val ; 
            node -> right -> val = node -> val ; 
            node -> val = temp ; 
        }
        return node ; 
    }

    void sort() {
        // Heap Sort Algorithm
        for( int i = 0 ; i < numNodes ; i++ ) {

            // 1. Heapify the tree
            heapify( ROOT ) ; 

            // 2. Get the last node from the heapified tree
            Node* lastNode = getLastNodeValue() ; 

            // 3. Swap the values of the last node and ROOT node
            int temp = ROOT -> val ; 
            ROOT -> val = lastNode -> val ; 
            lastNode -> val = temp ; 

            // 4. Print the value of the lastNode and delete it from the tree
            cout << lastNode -> val << " " ; 
            deleteNode( ROOT , lastNode -> val ) ; 
        }

        cout << "\n" ; 
    }

    Node* deleteNode( Node* node, int val ) {
        if( node == nullptr ) {
            return nullptr; 
        }
        if( node -> val == val ) {
            delete node ; 
            return nullptr ; 
        }
        node -> left = deleteNode( node -> left , val ) ; 
        node -> right = deleteNode( node -> right , val ) ;
        return node ; 
    }

    Node* getLastNodeValue() {
        // Perform BFS traversal and return the node
        // popped last from the queue
        queue<Node*> q ; 
        q.push( ROOT ) ; 
        Node* poppedNode = nullptr ; 
        while( !q.empty() ) {
            poppedNode = q.front() ; 
            q.pop() ; 
            if( poppedNode -> left != nullptr ) {
                q.push( poppedNode -> left ) ;
            }
            if( poppedNode -> right != nullptr ) {
                q.push( poppedNode -> right ) ;
            }
        }
        // Once the queue is empty, poppedNode is not updated
        // Hence, poppedNode represents the last node of the BFS sequence
        return poppedNode ; 
    }

} ; 

int main() {
    int keys[ 7 ] = { 87 , 5 , 34 , 99 , 44 , 12 , 68 } ; 
    Heap heap ; 
    heap.insert( keys , 7 ) ;
    heap.sort() ; 
    return 0 ;
}
