/*
Source : Advait Naik (GitHub - @Advait0801)

Given a sequence of keys k1<k2<k3........<kn of n sorted keys with a search probablilty pi for each key 
ki build a binary search tree that has the least searching cost.
*/

#include <iostream>
using namespace std;

class Node{
    int key;
    Node *left = nullptr, *right = nullptr;

public:
    friend class OBST;
};

class OBST{
    int R[100][100];
    int C[100][100];
    Node *root = nullptr;

    int sumOfFrequencies(int *arr,int low,int high){
        int sum = 0;
        for(int i=low;i<high;i++){
            sum = sum + arr[i];
        }
        return sum;
    }

    void findOptimalSubTree(int *freqs,int numNodes,int n){
        for(int i=0;i<n - numNodes;i++){
            int j = numNodes + i;
            int minCost = 9999;
            int minRoot = R[i][j-1];
            for(int k=i+1;k<=j;k++){
                int cost = C[i][k-1] + C[k][j];
                if(cost < minCost){
                    minCost = cost;
                    minRoot = k;
                }
            }
            C[i][j] = minCost + sumOfFrequencies(freqs,i,j);
            R[i][j] = minRoot;
        }
    }

    Node *constructOBST(int i,int j,int *values){
        if(i == j){
            return nullptr;
        }
        else{
            Node *node = new Node();
            node -> key = values[R[i][j] - 1];
            node -> left = constructOBST(i , R[i][j] - 1 , values);
            node -> right = constructOBST(R[i][j] , j , values);
            return node;
        }
    }

    void inOrder(Node *node){
        if(node == nullptr) return;

        inOrder(node -> left);
        cout<<node -> key<<" ";
        inOrder(node -> right);
    }

    void preOrder(Node *node){
        if(node == nullptr) return;

        cout<<node -> key<<" ";
        preOrder(node -> left);
        preOrder(node -> right);
    }

public:
    void display(){
        inOrder(this -> root);
        cout<<endl;
        preOrder(this -> root);
    }

    void findOBST(int *values,int *freqs,int totalNodes){
        int n = totalNodes + 1;

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                C[i][j] = 0;
                R[i][j] = 0;
            }
        }

        for(int i=0;i<n;i++){
            int j = i + 1;
            C[i][j] = freqs[i];
            R[i][j] = j;
        }

        for(int i=2;i<n;i++){
            findOptimalSubTree(freqs , i , n);
        }

        cout<<"Cost of OBST is "<<C[0][n-1]<<endl;

        this -> root = new Node();
        this -> root = constructOBST(0 , n-1 , values);
    }    
};

int main(){
    OBST t;
    int nodes;
    cout<<"Enter no of nodes: ";
    cin>>nodes;
    int values[nodes];
    int frequencies[nodes];
    for(int i=0;i<nodes;i++){
        cout<<"Enter value and frequency: ";
        cin>>values[i]>>frequencies[i];
    }
    cout<<endl;
    t.findOBST(values , frequencies , nodes);
    t.display();

    return 0;
}
