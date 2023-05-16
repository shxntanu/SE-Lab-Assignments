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
	double C[MAX][MAX];
	double W[MAX][MAX];
	int R[MAX][MAX];
	double  q[MAX];
   double p[MAX];

	int n;
	int keys[MAX];
	Node *root;

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
			W[i][i] = q[i];
			for (j = i + 1; j <= n; j++)
				W[i][j] = W[i][j - 1] + p[j] + q[j];
		}

		for (i = 0; i <= n; i++)
			C[i][i] = W[i][i];
		for (i = 0; i <= n - 1; i++)
		{
			j = i + 1;
			C[i][j] = C[i][i] + C[j][j] + W[i][j];
			R[i][j] = j;
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
				C[i][j] = W[i][j] + min;
				R[i][j] = m;
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
			p->key = keys[R[i][j]];
			p->left = Construct_OBST(i, R[i][j] - 1);
			p->right = Construct_OBST(R[i][j], j);
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
		}
	}
	void obst()
	{


		Calculate_W_C_R();

		cout << "C[0] = " << C[0][n] << " W[0] = " << W[0][n] << endl;


		cout << "The Least cost is: \n"
			 << C[0][n]<<endl;
		root = Construct_OBST(0, n);
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

	OBST ob;

	while (1)
	{
		cout << "1.Construct tree\n2.Display tree\n3.Exit\n";
		cin >> k;
		switch (k)
		{
		case 1:
		    ob.inp();
			ob.obst();
			break;
		case 2:
			ob.display(ob.get(), 0);
			break;
		}
		if(k==3)
			break;
	}
}
