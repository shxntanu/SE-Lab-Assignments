/*
Represent a given graph using adjacency matrix/list to perform DFS and using adjacency list to 
perform BFS. Use the map of the area around the college as the graph. 
Identify the prominent land marks as nodes and perform DFS and BFS on that.

Functions to be implemented:
1. Read graph
2. Display adjacency list
3. DFS
4. BFS
5. indegree & outdegree
6. isConnected
*/

#include <bits/stdc++.h>
using namespace std;

class Node {
    public:
    string name;
    Node* next = nullptr ;
    Node* down = nullptr ;
};

class Graph {

    Node *head = nullptr;

    void add( string node1, string node2 ) {

        if( head == nullptr ) {
            Node *newNode1 = new Node();
            Node *newNode2 = new Node();
            newNode1->name = node1;
            newNode2->name = node2;

            newNode1->next = newNode2;
            head = newNode1;
        }
        
        else {
            Node *currentNode = head;
            Node *prevNode = nullptr;
            bool found = false;

            while( currentNode != nullptr ) {
                if( currentNode->name == node1 ) {
                    found = true;
                    Node *currentNeighbour = currentNode;
                    while( currentNeighbour->next != nullptr )
                        currentNeighbour = currentNeighbour->next;
                    Node *newNode = new Node();
                    newNode->name = node2;
                    currentNeighbour->next = newNode;
                    break;
                }
                prevNode = currentNode;
                currentNode = currentNode->down;
            }
            if( !found ) {
                Node *newNode1 = new Node();
                Node *newNode2 = new Node();
                newNode1->name = node1;
                newNode2->name = node2;
                currentNode->down = newNode1;
                newNode1->next = newNode2;
            }
        }
    }

    void printLL( Node* headNode ) {
        Node* currentNode = headNode ;
        while( currentNode != nullptr ) {
            // cout.width(5);
            cout << currentNode->name << "->" ;
            currentNode = currentNode -> next ;
        }
    }

    public:

    void addNode( string node1, string node2 ) {
        add( node1, node2 );
        add( node2, node1 );
    }

    void printAL() {
        Node *currentNode = head;
        while( currentNode != nullptr ) {
            printLL( currentNode );
            cout<<endl;
            currentNode = currentNode->down;
        }
    }

    void BFS( string startingNode ) {
        queue<string> myQueue;
        vector<string> visited;
        visited.push_back( startingNode );
        myQueue.push( startingNode );
        while ( true ) {

            // if Queue is not empty, pop an element
            // and assign its non-visited neighbours
            // to the visited list
            if( !myQueue.empty() ) {
                string poppedNode = myQueue.front();
                myQueue.pop();
                startingNode = poppedNode;
                cout<< startingNode << " ";
            }
            else {
                cout<<endl;
                break;
            }

            Node *currentNode = head;
            bool found = false;
            while( currentNode != nullptr ) {
                if( currentNode->name == startingNode ) {
                    found = true;
                    Node *currentNeighbour = currentNode->next;
                    while( currentNeighbour != nullptr ) {

                        // if Neighbour has not been visited
                        if( find( visited.begin(), visited.end(), currentNeighbour->name ) == visited.end() ) {
                            myQueue.push( currentNeighbour->name );
                            visited.push_back( currentNeighbour->name );
                        }

                        currentNeighbour = currentNeighbour->next;
                    }
                    break;
                }
                currentNode = currentNode->down;
            }

            if( !found ) {
                cout<<"Starting node doesn't exist in the graph"<<endl;
            }
        }
    }

    void DFS( string startingNode ) {
        stack<string> myStack;
        vector<string> visited;
        myStack.push( startingNode );
        visited.push_back( startingNode );
        while( true ) {

            if( !myStack.empty() ) {
                string poppedNode = myStack.top();
                myStack.pop();
                startingNode = poppedNode;
                cout<< startingNode << " ";
            }
            else {
                cout<<endl;
                break;
            }

            Node *currentNode = head;
            bool found = false;
            while( currentNode != nullptr ) {
                if( currentNode->name == startingNode ) {
                    found = true;
                    Node *currentNeighbour = currentNode->next;
                    while( currentNeighbour != nullptr ){
                        if( find( visited.begin(), visited.end(), currentNeighbour->name ) == visited.end() ) {
                            myStack.push( currentNeighbour->name );
                            visited.push_back( currentNeighbour->name );
                        }
                        currentNeighbour = currentNeighbour->next;
                    }
                    break;
                }   
            }

            if( !found ) {
                cout<<"Starting node doesn't exist in the list"<<endl;
                break;
            }
        }
    }

    void inDegree() {
        
    }

};
