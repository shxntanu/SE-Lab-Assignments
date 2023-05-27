/*
Author - Shantanu Wable

Given sequence k = k1 <k2 < … < kn of n sorted keys, with a search
probability pi for each key ki . Build the Binary search tree that has
the least search cost given the access probability for each key.
*/

#include <bits/stdc++.h>
using namespace std;
#define MAX 20

class Node
{
	int key;
	Node *left, *right;
	friend class OBST;

  public:
	Node()
	{
		key = 0;
		left = NULL;
		right = NULL;
	}
	Node(int k)
	{
		key = k;
		left = NULL;
		right = NULL;
	}
};

class OBST
{
	double C[MAX][MAX];  // Matrix to store the cost of optimal binary search trees
	double W[MAX][MAX];  // Matrix to store the weight (sum of access probabilities) of subtrees
	int R[MAX][MAX];     // Matrix to store the roots of optimal subtrees
	double q[MAX];       // Array to store the access probabilities of dummy keys
	double p[MAX];       // Array to store the access probabilities of actual keys

	int n;               // Number of keys
	int keys[MAX];       // Array to store the actual keys
	Node *root;          // Root node of the constructed optimal binary search tree

  public:
	OBST()
	{
		root = NULL;
	}

	void Calculate_W_C_R()
	{
		double x;
		double min;
		int i, j, k, h, m;

		for (i = 0; i <= n; i++)
		{
			W[i][i] = q[i];  // Weight of a single node is its access probability (dummy key or actual key)
			for (j = i + 1; j <= n; j++)
				W[i][j] = W[i][j - 1] + p[j] + q[j];  // Weight of a subtree is the sum of its nodes' access probabilities

		}

		for (i = 0; i <= n; i++)
			C[i][i] = W[i][i];  // Cost of a single node is its weight
		for (i = 0; i <= n - 1; i++)
		{
			j = i + 1;
			C[i][j] = C[i][i] + C[j][j] + W[i][j];  // Cost of a subtree with two nodes is the sum of the nodes' weights and the root weight
			R[i][j] = j;  // Root of the subtree with two nodes is the second node
		}
		for (h = 2; h <= n; h++)
			for (i = 0; i <= n - h; i++)
			{
				j = i + h;
				m = R[i][j - 1];
				min = C[i][m - 1] + C[m][j];
				for (k = m + 1; k <= R[i + 1][j]; k++)
				{
					x = C[i][k - 1] + C[k][j];
					if (x < min)
					{
						m = k;
						min = x;
					}
				}
				C[i][j] = W[i][j] + min;  // Cost of the subtree is the sum of its weight and the minimum cost of its left and right subtrees
				R[i][j] = m;  // Root of the subtree is the node that gives the minimum cost
			}

		cout << "\nThe weight matrix W:\n";
		for (i = 0; i <= n; i++)
		{
			for (j = i; j <= n; j++)
				cout << W[i][j] << " ";
			cout << "\n";
		}

		cout << "\nThe cost matrix C:\n";
		for (i = 0; i <= n; i++)
		{
			for (j = i; j <= n; j++)
				cout << C[i][j] << " ";
			cout << "\n";
		}

		cout<<("\nThe root matrix R:\n");
		for (i = 0; i <= n; i++)
		{
			for (j = i+1; j <= n; j++)
				cout << R[i][j] << " ";
			cout << "\n";
		}
	}

	Node *Construct_OBST(int i, int j)
	{
		Node *p;

		if (i == j)
			p = NULL;
		else
		{
			p = new Node();
			p->key = keys[R[i][j]];  // Root node key is determined by the optimal root index stored in R[i][j]
			p->left = Construct_OBST(i, R[i][j] - 1);  // Construct left subtree recursively
			p->right = Construct_OBST(R[i][j], j);  // Construct right subtree recursively
		}
		return p;
	}

	void display(Node *ROOT, int nivel)
	{
		if (ROOT != 0)
		{
			display(ROOT->left, nivel + 1);
			cout << ROOT->key<< endl;
			display(ROOT->right, nivel + 1);
			// Display the tree in an inorder traversal (left subtree, root, right subtree)
		}
	}
	void obst()
	{


		Calculate_W_C_R();

		cout << "C[0] = " << C[0][n] << " W[0] = " << W[0][n] << endl;


		cout << "The Least cost is: \n"
			 << C[0][n]<<endl;
		root = Construct_OBST(0, n);  // Construct the optimal binary search tree using the root matrix R
	}
	void inp()
	{
		cout << "Enter number of keys:";
		cin >> n;
		cout<<" Enter keys"<<endl;
		for (int i = 1; i <= n; i++)
		{

			cin >> keys[i];
			cout << " probability = ";
			cin >> p[i];
		}
		for (int i = 0; i <= n; i++)
		{
			cout << "q" << i << "= ";
			cin >> q[i];
		}
	}
	Node *get()
	{
		return root;
	}
};

int main()
{
	int k;

	OBST tree;

	while (true)
	{
		cout << "1.Construct tree\n2.Display tree\n3.Exit\n";
		cin >> k;
		switch (k)
		{
		case 1:
		    tree.inp();  // Input the number of keys, their access probabilities, and dummy key access probabilities
			tree.obst();  // Calculate the optimal binary search tree and construct it
			break;
		case 2:
			tree.display(tree.get(), 0);  // Display the constructed tree
			break;
		}
		if(k==3)
			break;
	}
	return 0;
}
