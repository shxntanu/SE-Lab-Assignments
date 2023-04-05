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

#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    Node *left;
    int data;
    Node *right;
    
    Node(int d)
    {
        left = NULL;
        data = d;
        right = NULL;
    }
    
    Node()
    {
        left = NULL;
        data = 0;
        right = NULL;
    }
};

class BinaryTree
{
public:
    Node *root;
    
    // Creating the tree
    Node* buildTree(Node *root);
    // Swapping all Nodes (Mirroring the tree)
    void nodeSwap(Node *root);
    
    // Recursive Traversal Functions
    void rpostorder(Node *root);
    void rpreorder(Node *root);
    void rinorder(Node *root);
    
    // Iterative Traversal Functions
    void ipostorder(Node *root);
    void ipreorder(Node *root);
    void iinorder(Node *root);
    
    int maxDepth(Node* root);
    int getLeafCount(Node *root);
    int getInternalCount(Node *root);
    void deleteTree(Node* root);
    
    BinaryTree()
    {
        root = buildTree(root);
    }
    
    BinaryTree(BinaryTree &t)
    {
        this->root = t.root;
    }
};

int main()
{
    BinaryTree tree;
    int flag = 1, choice1;
    while(flag)
    {
        int choice;
        cout<<"======================================="<<endl;
        cout<<"||                                   ||"<<endl;
        cout<<"||       ~~~~~ BST MENU ~~~~~        ||"<<endl;
        cout<<"||                                   ||"<<endl;
        cout<<"||       1. Display BST              ||"<<endl;
        cout<<"||       2. Swap all nodes           ||"<<endl;
        cout<<"||       3. Height of tree           ||"<<endl;
        cout<<"||       4. Number of leaf nodes     ||"<<endl;
        cout<<"||       5. Number of internal nodes ||"<<endl;
        cout<<"||       6. Delete all nodes         ||"<<endl;
        cout<<"||                                   ||"<<endl;
        cout<<"======================================="<<endl;
        cout<<"\nEnter your choice: ";
        cin>>choice;
        
        switch(choice)
        {
            case 1:
                cout<<"\n\t1. Recursive Inorder\n\t2. Iterative Inorder\n\t3. Recursive Preorder\n\t4. Iterative Preorder\n\t5. Recursive Postorder\n\t6. Iterative Postorder\n\tEnter your choice: ";
                cin>>choice1;
                switch(choice1)
                {
                    case 1:
                        tree.rinorder(tree.root);
                        break;
                        
                    case 2:
                        tree.iinorder(tree.root);
                        break;
                        
                    case 3:
                        tree.rpreorder(tree.root);
                        break;
                        
                    case 4:
                        tree.ipreorder(tree.root);
                        break;
                        
                    case 5:
                        tree.rpostorder(tree.root);
                        break;
                        
                    case 6:
                        tree.ipostorder(tree.root);
                        break;
                        
                    default:
                        cout<<"Wrong Input!"<<endl;
                }
                break;
                
            case 2:
                tree.nodeSwap(tree.root);
                cout<<"Nodes swapped!, Inorder Display: "<<endl;
                tree.iinorder(tree.root);
                break;
                
            case 3:
                cout<<"Height of tree: "<<tree.maxDepth(tree.root);
                break;
                
            case 4:
                cout<<"Number of leaf nodes: "<<tree.getLeafCount(tree.root)<<endl;
                break;
                
            case 5:
                cout<<"Number of internal nodes: "<<tree.getInternalCount(tree.root);
                break;
                
            case 6:
                tree.deleteTree(tree.root);
                break;
                
            default:
                cout<<"Wrong input!"<<endl;
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
    
    // Copying the binary tree
    // uses operator "="
    BinaryTree Tree2 = tree;
    
    return 0;
}


Node* BinaryTree::buildTree(Node *root)
{
    cout<<"Enter data for node (-1 indicates no data): ";
    int d;
    cin>>d;
    root = new Node(d);
    
    if(d == -1)
        return NULL;
    
    cout<<"Enter data to the left of "<<d<<" ";
    root->left = buildTree(root->left);
    cout<<"Enter data to the right of "<<d<<" ";
    root->right = buildTree(root->right);
    return root;
}

void BinaryTree::nodeSwap(Node *root)
{
    if(root) // If root is not NULL
    {
        if(root->left || root->right) // If either of left or right of root exists
        {
            Node *temp = root->left;
            root->left = root->right;
            root->right = temp;
        }
        nodeSwap(root->right); // Continue in right subtree
        nodeSwap(root->left);  // Continue in left subtree
    }
}

void BinaryTree::rpostorder(Node *root)
{
    if(root == NULL)
        return;

    rpostorder(root->left);
    rpostorder(root->right);
    cout<<root->data<<" ";
}

void BinaryTree::rpreorder(Node *root)
{
    if(root == NULL)
        return;

    cout<<root->data<<" ";
    rpreorder(root->left);
    rpreorder(root->right);
}

void BinaryTree::rinorder(Node *root)
{
    if(root == NULL)
        return;

    rinorder(root->left);
    cout<<root->data<<" ";
    rinorder(root->right);
}

void BinaryTree::iinorder(Node *root)
{
    stack<Node*> s;
    Node *curr = root;
    while(!s.empty() or curr!=NULL)
    {
        while(curr!=NULL)
        {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        cout<<curr->data<<" ";
        curr = curr->right;
    }
}

void BinaryTree::ipreorder(Node *root)
{
    if (root == NULL)
        return;
    stack<Node*> nodeStack;
    nodeStack.push(root);
 
    while (nodeStack.empty() == false) {
        Node* node = nodeStack.top();
        cout<<node->data<<" ";
        nodeStack.pop();
        if (node->right)
            nodeStack.push(node->right);
        if (node->left)
            nodeStack.push(node->left);
    }
}

void BinaryTree::ipostorder(Node *root)
{
    // 2 Stack method
    stack<Node*> s1, s2;
    s1.push(root);
    while(!s1.empty())
    {
        Node *t = s1.top();
        s1.pop();
        s2.push(t);
        if(t->right)
            s1.push(t->right);
        if(t->left)
            s1.push(t->left);
    }
    while(!s2.empty())
    {
        cout<<s2.top()->data<<" ";
        s2.pop();
    }
}

int BinaryTree::maxDepth(Node* root)
{
    if (root == NULL)
        return 0;
    else {
        // Compute the depth of each subtree
        int lDepth = maxDepth(root->left);
        int rDepth = maxDepth(root->right);
 
        // Using the larger depth
        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}

int BinaryTree::getLeafCount(Node *root)
{
    if(root == NULL)
        return 0;
    // Condition for leaf Node
    else if(root->left == NULL and root->right == NULL)
        return 1;
    else
        return getLeafCount(root->right) + getLeafCount(root->left);
}

int BinaryTree::getInternalCount(Node *root)
{
    if(root == NULL or (root->right == NULL and root->left == NULL))
        return 0;
    else return 1 + getInternalCount(root->left) + getInternalCount(root->right);
}

void BinaryTree::deleteTree(Node* root)
{
    if (root == NULL) return;

    deleteTree(root->left);
    deleteTree(root->right);

    cout << "\n Deleting node: " << root->data;
    delete root;
}
