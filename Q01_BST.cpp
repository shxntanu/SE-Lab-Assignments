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
using namespace std;

class Node
{
    public:
    Node* left;
    int data;
    Node* right;

    Node(int d = 0)
    {
        left = right = NULL;
        data = d;
    }
};

class BST
{
    public:
    Node *root, *temp;
    Node *null = NULL;
    
    BST(int d)
    {
        root = new Node(d);
    }

    void insert_node(int d, Node *n) {
        if(d > n->data) {
            if(n->right == nullptr)
                n->right = new Node(d);

            else
                insert_node(d, n->right);
        }

        else {
            if(n->left == nullptr)
                n->left = new Node(d);

            else
                insert_node(d, n->left);
        }
    }
    
    void iinsert(int x)
    {
        if(root == nullptr)
        {
            root = new Node(x);
        }

        else
        {
            Node* curr = root, *prev = nullptr;
            while(curr!= nullptr) {
                prev = curr;

                // we assume no duplicate entries
                if( x > curr->data )
                    curr = curr->right;
                else
                    curr = curr->left;
            }

            if( x > prev->data ) {
                Node *newNode = new Node(x);
                prev->right = newNode;
            }

            else {
                Node *newNode = new Node(x);
                prev->left = newNode;
            }
        }
    }
    
    void display(Node *t) {
        if(t==NULL)
            return;

        if(t->left != NULL)
            display(t->left);
        cout<<t->data<<" ";
        if(t->right != NULL)
            display(t->right);
    }
    
    int min_value() {
        Node *temp;
        temp = root;

        while(temp->left != NULL)
            temp = temp->left;

        return temp->data;
    }
    
    int max_value() {
        Node *temp;
        temp = root;

        while(temp->right != NULL)
            temp = temp->right;

        return temp->data;
    }
    
    void search(int d, Node *n) {
        Node *temp;
        temp = n;

        if(d > temp->data)
        {
            if (temp->right == NULL)
                cout<<"Element doesn't exist!"<<endl;

            else search(d, temp->right);
        }

        else if(d < temp->data)
        {
            if(temp->left == NULL)
                cout<<"Element doesn't exist!"<<endl;

            else search(d, temp->left);
        }

        else cout<<"Element exists!"<<endl;
    }
    
    void swap_all_nodes(Node *p) {
        if(p){
            if(p->left || p->right)
            {
                Node *temp = p->left;
                p->left = p->right;
                p->right = temp;
            }
            swap_all_nodes(p->left);
            swap_all_nodes(p->right);
        }
    }
    
    int height(Node* node) {
        if(node == NULL) return 0;

        int h1 = height(node->left);
        int h2 = height(node->right);

        return max(h1,h2)+1;
    }
    
    int dia(Node *node) {
        if(node == NULL) return 0;

        int l = height(node->left);
        int r = height(node->right);

        int op1 = dia(node->left);
        int op2 = dia(node->right);
        int op3 = l+r+1;

        return max(op1,max(op2,op3));
    }
    
    void del(Node *node, int key) {
        if(node)
        {
            Node *current;
            current = node;

            if(node == NULL)
                return;

            if(key < node->data)
            {
                current = node->left;
                del(node->left, key);
            }

            else if(key > node->data)
            {
                current = node->right;
                del(node->right, key);
            }

            else
            {
                // Node has no child
                if(current->left == NULL and current->right == NULL)
                {
                    cout<<"Deleted Node containing "<<current->data;
                    delete (current);
                }

                // Node has 1 child
                else if(current->left == NULL)
                {
                    cout<<"Deleted Node containing "<<current->data;
                    current->data = current->right->data;
                    delete (current->right);
                    current->right = NULL;

                }

                else if (current->right == NULL)
                {
                    cout<<"Deleted Node containing "<<current->data;
                    current->data = current->left->data;
                    delete (current->left);
                    current->left = NULL;
                }

                else
                {
                    Node *temp = minvaluenode(current->right);
                    current->data = temp->data;
                    del(current->right, temp->data);
                }
            }
        }
    }
    
    Node* minvaluenode(Node *node) {
        Node *current = node;
        while(current && current->left != NULL)
            current = current->left;

        return current;
    }

};

int main()
{
    int choice;
    int flag = 1;
    int d,path;
    cout<<"\nEnter root node: ";
    int root;
    cin>>root;
    BST tree(root);
    while(flag==1)
    {
        cout<<"======================================="<<endl;
        cout<<"||                                   ||"<<endl;
        cout<<"||       ~~~~~ BST MENU ~~~~~        ||"<<endl;
        cout<<"||                                   ||"<<endl;
        cout<<"||       1. Insert Node              ||"<<endl;
        cout<<"||       2. Search for a Node        ||"<<endl;
        cout<<"||       3. Display BST              ||"<<endl;
        cout<<"||       4. Display Smallest Value   ||"<<endl;
        cout<<"||       5. Display largest value    ||"<<endl;
        cout<<"||       6. Swap all nodes           ||"<<endl;
        cout<<"||       7. Longest Path             ||"<<endl;
        cout<<"||       8. Delete a node            ||"<<endl;
        cout<<"||                                   ||"<<endl;
        cout<<"======================================="<<endl;
        cout<<"\nEnter your choice: ";
        cin>>choice;

        switch(choice)
        {
            case 1: cout<<"Enter element to insert: ";
                    cin>>d;
                    tree.insert_node(d,tree.root);
                    cout<<"Element Inserted!"<<endl;
                    break;
            
            case 2: cout<<"Enter element to search: "<<endl;
                    cin>>d;
                    tree.search(d, tree.root);
                    break;
                
            case 3: tree.display(tree.root);
                    break;

            case 4: cout<<"Smallest value is: "<<tree.min_value()<<endl;
                    break;
                    
            case 5: cout<<"Largest value is: "<<tree.max_value()<<endl;
                    break;
            
            case 6: tree.swap_all_nodes(tree.root);
                    cout<<"All Nodes swapped!"<<endl;
                    break;

            case 7: path=tree.dia(tree.root)-1;
                    cout<<"Longest Path: "<<path<<endl;
                    break;
                
            case 8: cout<<"Enter element to delete: ";
                    cin>>d;
                    tree.del(tree.root, d);
                    break;

            default:cout<<"Wrong Input"<<endl;
        }

        label:
        cout<<"\nDo you want to perform another operation? (1/0): ";
        cin>>flag;
        if(flag == 1)
            continue;
        else if(flag == 0)
            break;
        else
        {
            cout<<"Wrong input, try again!";
            goto label;
        }
    }
}
