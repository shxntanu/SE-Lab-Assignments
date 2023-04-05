#include<iostream>
using namespace std;

class Node
{	
	Node *prev;
	bool n;
	Node*next;
public:
	Node()
	{
		prev=next=NULL;
	}
	Node(bool b) 
	{
		n=b;
		prev=next=NULL;
	}
	friend class binary;
};

class binary
{
	Node *start;
	
	public:
		binary()
		{
			start=NULL;
		}
		void generate(int no);
		void displayBinary();
		void oc();
		void tc();
		binary operator +(binary n1);

	bool insert(bool val)
	{
		Node *nodee=new Node(val);
		if(start==NULL)
		{
			start=nodee;
		}
		else
		{
			nodee->next=start;
			start->prev=nodee;
			start=nodee;
		}
		return true;
	}
};

void binary::generate(int no)
{
	bool rem;
	Node *p;
	rem=no%2; // Remainder
	start=new Node(rem);
	no=no/2;
	while(no!=0)
	{
		rem=no%2;
		no=no/2;
		
			p=new Node(rem);
			p->next=start;
			start->prev=p;

			start=p;
	}
}
void binary::displayBinary()
{
	Node *t;
	t=start;
	while(t!=NULL)
	{
		cout<<t->n;
		t=t->next;
	}
	
}
void binary::oc()
{
	Node *t;
	t=start;
	
	while(t!=NULL)
	{
		if(t->n==0)
			t->n=1;
		else
			t->n=0;
		
		t=t->next;
		
	}
}
binary binary::operator +(binary n1)
{
	binary sum;
	Node *a=start;
	Node *b=n1.start;

	bool carry=false;
	while(a->next!=NULL)
		a=a->next;
	while(b->next!=NULL)
		b=b->next;
	
	while(a!=NULL && b!=NULL)
	{
		sum.insert((a->n)^(b->n)^carry);
		carry=((a->n&& b->n) || (a->n&& carry) || (b->n && carry));
		
		a=a->prev;
		b=b->prev;
	}
	while(a!=NULL)
	{
		sum.insert(a->n^carry);
		a=a->prev;
	}
	while(b!=NULL)
	{
		sum.insert(b->n^carry);
		b=b->prev;
	}
	sum.insert(carry);
	return sum;
}
void binary::tc()
{
	oc();
	bool carry=1;
	Node *t;
	t=start;
	while(t->next!=NULL)
	{
		t=t->next;
	}
	while(t!=NULL)
	{
	if(t->n==1&& carry==1)
	{
		t->n=0;
		carry=1;
	}
	else
	if(t->n==0&& carry==1)
	{
		t->n=1;
		carry=0;
	}
	else
	if(carry==0)
	break;
	
	t=t->prev;
}
displayBinary();
}
int main()
{
	int num,num1;
	binary n1,n3,n2;
	int choice=1;
	do
	{
		cout<<"\n\n=========Binary Number Operations========\n";
		cout<<"1. Generate binary\n2.One's Complement\n3.Two's Complement\n4. Addition\n0.Exit\nEnter your choice: ";
		cin>>choice;
		switch(choice)
		{
			case 1: cout<<"\nENter Number in decimal form: ";
					cin>>num;
					n1.generate(num);
					cout<<"\nBinary Representation: ";
					n1.displayBinary();
					break;
			case 2:cout<<"\nENter Number in decimal form: ";
					cin>>num;
					n1.generate(num);
					cout<<"\nBinary Representation: ";
					n1.displayBinary();
					cout<<"\nOnes Complement: ";
					n1.oc();
					n1.displayBinary();
					break;
			case 3:cout<<"\nENter Number in decimal form: ";
					cin>>num;
					n1.generate(num);
					cout<<"\nBinary Representation: ";
					n1.displayBinary();
					cout<<"\nTwos complement; ";
					n1.tc();
					break;
			case 4: cout<<"\nENter Two Numbers: ";
					cin>>num>>num1;
					n1.generate(num);
					n2.generate(num1);
					n1.displayBinary();
					cout<<" + ";
					n2.displayBinary();
					cout<<"= ";
					n3=n1+n2;
					n3.displayBinary();		
		}
	}while(choice!=0);
	cout<<"\n\nThank You!"<<endl;
	return 0;
}
