/*
 * templates.cpp
 *
 *  Created on: Nov 18, 2022
 *      Author: Shantanu Wable
 */

#include<iostream>
using namespace std;

template<typename T>
void sort(T A[], int len)
{
	int i,j,min;
	T temp;
	for(i=0;i<len-1;i++)
	{
		min =i;
		for(j=i+1;j<len;j++)
		{
			if(A[j]<A[min])
				min=j;
		}
		temp = A[i];
		A[i] = A[min];
		A[min] = temp;
	}
	cout<<"Sorted Array: "<<endl;
	for(i=0;i<len;i++)
	{
		cout<<" "<<A[i];
	}
}

int main()
{
    int i,n;
    cout<<"\nEnter total no of int elements:";
    cin>>n;
    int A[n];
    cout<<"\nEnter all int elements:";
    for(i=0;i<n;i++)
    {
        cin>>A[i];
    }
    sort(A,n);
   
    cout<<"\nEnter total no of float elements:";
    cin>>n;
    float B[n];
    cout<<"\nEnter float elements:";
    for(i=0;i<n;i++)
    {
        cin>>B[i];
    }
    sort(B,n);
}
