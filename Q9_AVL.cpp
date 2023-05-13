/*
 Author - Shantanu Wable
 
 Data Structure Explanation: https://www.javatpoint.com/avl-tree
 
 A dictionary stores keywords and its meanings. Provide facility for adding new keywords, deleting keywords,
 updating values of an entry. Provide facility to display whole data in sorted Ascending / Descending order.
 Also find out how many comparisons are required for finding any entry. Use height balance tree and find
 complexity for finding a keyword.
 */

// #include <bits/stdc++.h>
#include <iostream>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std ;

struct Node {
    int key ;
    string value ;
    int height = 1 ;       // Default height of a node w.r.t its parent would be one
    Node* left = nullptr ;
    Node* right = nullptr ;
};


class AVLTree {
    
    Node* root = nullptr ;
    
    int nodeBalanceFactor( Node* node ) {
        if( node == nullptr ) {
            return 0 ;
        }
        return nodeHeight( node -> left ) - nodeHeight( node -> right ) ;
    }
    
    int nodeHeight( Node *node ) {
        if( node == nullptr ) {
            return 0;
        }
        return node -> height ;
    }
    
    void updateHeight( Node* node ) {
        node -> height = 1 + max( nodeHeight( node -> left ) , nodeHeight( node -> right ) )  ;
    }
    
    Node* LLRotation( Node *node ) {
        Node *newRoot = node->left;
        newRoot->right = node;
        node->left = nullptr;
        
        updateHeight( node );
        updateHeight( newRoot );
        
        return newRoot;
    }
    
    Node* RRRotation( Node *node ) {
        Node *newRoot = node->right;
        newRoot->left = node;
        node->right = nullptr;
        
        updateHeight( node );
        updateHeight( newRoot );
        
        return newRoot;
    }
    
    Node* RLRotation( Node* node ) {
        node -> right = RRRotation( node -> right ) ;
        return LLRotation( node ) ;
    }

    Node* LRRotation( Node* node ) {
        node -> left = LLRotation( node -> left ) ;
        return RRRotation( node ) ;
    }
    
    Node* balance( Node* node ) {
        if( nodeBalanceFactor( node ) == 2 ) {
            if( nodeBalanceFactor( node -> left ) < 0 )
                node = LRRotation( node ) ;
            else
                node = LLRotation( node ) ;
        }
        else if( nodeBalanceFactor( node ) == -2 )  {
                if( nodeBalanceFactor( node -> right ) > 0 )
                    node =RLRotation( node ) ;
                else
                    node = RRRotation( node ) ;
        }
        updateHeight( node ) ;
        return node ;
    }
    
    void iinorder( Node *root ) {
        if( root == nullptr )
            return;
        iinorder( root->left );
        cout<< root->key <<" ";
        iinorder( root->right );
    }
    
    Node* insertSubTree( Node* curr , int key , string value ) {
        if( curr == nullptr ) {
            Node* newNode = new Node() ;
            newNode -> key = key ;
            newNode -> value = value ;
            return newNode ;
        }
        if( curr -> key > key ) {
            curr -> left = insertSubTree( curr -> left , key , value ) ;
        }
        else if( curr -> key < key ) {
            curr -> right = insertSubTree( curr -> right , key , value ) ;
        }
        else {
            curr -> value = value ;
            return curr ;
        }
        return balance( curr ) ;
    }
    
public:
    
    void insert( int key, string value ) {
        root = insertSubTree( root, key, value);
    }
    
    void inorder() {
        cout<< "\nInorder: " <<endl;
        iinorder( root );
        cout<<endl;
    }
    
    Node* search( int key ) {
        Node *curr = root;
        while( curr != nullptr ) {
            if( key > curr->key )
                curr = curr->right;
            else if( key < curr->key )
                curr = curr->left;
            else
                return curr;
        }
        return nullptr;
    }
    
    void BFS() {
        cout<< "\nBFS: " <<endl;
        queue<Node*> Queue;
        Queue.push( root ) ;
        while( !Queue.empty() ) {
            Node* poppedNode = Queue.front() ;
            cout << poppedNode -> key << " " ;
            Queue.pop() ;
            if( poppedNode -> left != nullptr ) {
                Queue.push( poppedNode -> left ) ;
            }
            if( poppedNode -> right != nullptr ) {
                Queue.push( poppedNode -> right ) ;
            }
        }
        cout<<endl;
    }
};

int main() {
    AVLTree tree;
    
    tree.insert(100, "1");
    tree.insert(50, "2");
    tree.insert(150, "3");
    tree.insert(25, "4");
    tree.insert(75, "5");
    tree.insert(125, "6");
    
    tree.BFS();
    tree.inorder();
    
    tree.insert(175, "7");
    tree.insert(65, "8");
    tree.insert(85, "9");
    
    tree.BFS();
    tree.inorder();
    
    return 0;
}
