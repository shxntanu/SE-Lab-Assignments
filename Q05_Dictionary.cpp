/*
Implement all the functions of a dictionary (ADT) using open
hashing technique: separate chaining using linked list Data: Set of
(key, value) pairs, Keys are mapped to values, Keys must be
comparable, and Keys must be unique. Standard Operations: Insert
(key, value), Find(key), Delete(key)

|---------|
|   394   | -> abcd -> cdba -> dbca
|---------|
|   410   | -> laal -> lala -> aall
|---------|
|   548   | -> dwupd -> puddw
|---------|


*/

#include <bits/stdc++.h>
using namespace std; 

class Node {
    string key;
    string value;
    Node *next = nullptr;

    friend class Dictionary;
};

class Dictionary {

    Node **table;
    int tableSize;

    int hash( string value ) {
        int asciiSum = 0;
        for( int i = 0; i < value.length(); i++ ) {
            asciiSum += int( value[i] );
        } 
        return asciiSum % tableSize ;
    }

    void insertLL( Node *headNode, string key, string value ) {
        Node *currentNode = headNode;
        while( currentNode->next != nullptr )
            currentNode = currentNode->next;
        Node *newNode = new ( Node );
        newNode->key = key;
        newNode->next = NULL;
        newNode->value = value;
        currentNode->next = newNode;
    }

    // Finds the Linked List mapped to the Key
    Node* findLL ( Node *headNode, string key ) {
        Node *currentNode = headNode;
        while( currentNode->next != NULL ) {
            if( currentNode->key == key ) {
                return currentNode;
            }
            currentNode = currentNode -> next;
        }
        if(currentNode->key == key) return currentNode;
        else return nullptr;
    }

    // Prints the Linked List mapped to the Key
    void printLL( Node* headNode ) {
        Node* currentNode = headNode ;
        while( currentNode != nullptr ) {
            // cout.width(5);
            cout << currentNode -> key << " " << currentNode -> value << "," ;
            currentNode = currentNode -> next ;
        }
    }

    // Deletes from the Linked List mapped to the key
    void deleteLL( int index, Node* headNode, string key ) {

        if(headNode == NULL)
            cout<<"No such record exists to be deleted!"<<endl;
        
        else if( headNode->key == key ) {
            Node *nextNode = headNode->next;
            delete table[ index ];
            table[ index ] = nextNode;
        }
        
        else {
            Node *currentNode = headNode;
            Node *prevNode = NULL;
            while( currentNode->next != nullptr ) {
                if( currentNode->key == key )
                    break;
                prevNode = currentNode;
                currentNode = currentNode->next;
            }
        
            if (currentNode->key == key) {
                prevNode->next = currentNode->next;
                delete currentNode;
            }

            else cout<<"No such element"<<endl;
        }
    }

    public: 
    
    Dictionary ( int n ) {
        this->tableSize = n;
        table = new Node*[ tableSize ];
        for( int i = 0; i < tableSize; i++ ) {
            table[i] = nullptr;
        }
    } 

    void insert( string key, string value ) {
        int hashAddress = hash( key );
        if( table[ hashAddress ] == nullptr ) {
            Node *newNode = new ( Node );
            newNode->key = key;
            newNode->next = NULL;
            newNode->value = value;
            table[ hashAddress ] = newNode;
        }

        else {
            insertLL(table[ hashAddress ], key, value );
        }
    }

    void display() {
        for( int i = 0; i < tableSize; i++ ) {
            // cout.width( 5 );
            cout<<i<<" ";
            printLL( table[i] );
            cout<<endl;
        }
    }

    void search( string key ) {
        int hashAddress = hash(key);
        Node *foundNode = findLL( table[ hashAddress ], key );
        if( foundNode == nullptr )
            cout<<"No record found"<<endl;
        else {
            cout<<"\nKey: "<<key<<endl;
            cout<<"Value: "<<foundNode->value<<endl;
        }
    }

    void del( string key ) {
        int hashAddress = hash(key);
        deleteLL( hashAddress, table[ hashAddress ], key);
    }
};

int main() {

    Dictionary dict(10);

    // Placeholder values
    dict.insert("abcd", "1000");
    dict.insert("cdba", "2000");
    dict.insert("dbca","5000");

    dict.insert("laal", "1000");
    dict.insert("lala", "2000");
    dict.insert("aall","5000");

    dict.insert("dwupd", "1000");
    dict.insert("puddw", "2000");
    
    while( true ) {
        cout<<"1. Insert key:value pair"<<endl;
        cout<<"2. Search for value with key"<<endl;
        cout<<"3. Delete the key:value pair"<<endl;
        cout<<"4. Display the dictionary"<<endl;
        cout<<"\nEnter your choice (any other i/p for exit) : ";
        int choice;
        cin>>choice;

        if( choice == 1) {
            string key, value;
            cout<<"Enter key: "; cin>>key;
            cout<<"Enter corresponding value: "; cin>>value;
            dict.insert( key, value ); 
        }
        
        else if( choice == 2) {
            string key;
            cout<<"Enter key: "; cin>>key;
            dict.search( key );
        }

        else if( choice == 3) {
            string key;
            cout<<"Enter key: "; cin>>key;
            dict.del( key );
            // cout<< key << " has been deleted"<<endl;
        }

        else if( choice == 4 ) {
            dict.display();
        }

        else 
            break;
    }

    return 0;
}
