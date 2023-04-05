/*
 * main.cpp
 *
 *  Created on: Dec 1, 2022
 *      Author: Shantanu
 *
 *  Write C++ program using STL for sorting and searching user defined records such as Item
 *	records (Item code, name, cost, quantity etc) using vector container.
 */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
class Element
{
      public:
        char itemname[10];
        int quantity;
        int cost;
        int itemcode;

        bool operator==(const Element& i1)
        {
            if(itemcode==i1.itemcode)
                return 1;
            return 0;
        }

        bool operator<(const Element& i1)
        {
            if(itemcode<i1.itemcode)
                return 1;
            return 0;
        }
};

vector<Element> store;
void print(Element &i1);
void display();
void insert();
void search();
void del();
bool compare(const Element &i1, const Element &i2);

int main()
{
    int ch;
    do
    {
        cout<<"\n***** Menu *****";
        cout<<"\n1.Insert";
        cout<<"\n2.Display";
        cout<<"\n3.Search";
        cout<<"\n4.Sort";
        cout<<"\n5.Delete";
        cout<<"\n6.Exit";
        cout<<"\nEnter your choice:";
        cin>>ch;

        switch(ch)
        {
               case 1:
                       insert();
                       break;

               case 2:
                       display();
                       break;

               case 3:
                       search();
                       break;

               case 4:
            	   	   sort(store.begin(),store.end(),compare);
                       cout<<"\n\n Sorted on Cost";
                       display();
                       break;

               case 5:
                       del();
                       break;

               case 6:
                       exit(0);
        }

    }
    while(ch!=7);

      return 0;
}

void insert()
{
    Element i1;
    cout<<"\nEnter Item Name:";
    cin>>i1.itemname;
    cout<<"\nEnter Item Quantity:";
    cin>>i1.quantity;
    cout<<"\nEnter Item Cost:";
    cin>>i1.cost;
    cout<<"\nEnter Item Code:";
    cin>>i1.itemcode;
    store.push_back(i1);
}

void display()
{
	// Function to display all items available in the store
	// Using the for_each loop available in <algorithm> STL header file

    for_each(store.begin(),store.end(),print);
}

void print(Element &i1)
{
	 // Printing info of a given element
     cout<<"\n";
     cout<<"\nItem Name:"<<i1.itemname;
     cout<<"\nItem Quantity:"<<i1.quantity;
     cout<<"\nItem Cost:"<<i1.cost;
     cout<<"\nItem Code:"<<i1.itemcode;
}

void search()
{

    vector<Element>::iterator p;
    Element i1;
    cout<<"\nEnter Item Code to search:";
    cin>>i1.itemcode;
    p=find(store.begin(),store.end(),i1);
    if(p==store.end())
    {
         cout<<"\nNot found.";
    }
    else
    {
         cout<<"\nFound.";
    }
}

void del()
{
    vector<Element>::iterator p;
    Element i1;
    cout<<"\nEnter Item Code to delete:";
    cin>>i1.itemcode;
    p=find(store.begin(),store.end(),i1);
    if(p==store.end())
    {
         cout<<"\nNot found.";
    }
    else
    {
         store.erase(p);
         cout<<"\nDeleted.";
    }
}

bool compare(const Element &i1, const Element &i2)
{
   return i1.cost < i2.cost;
}
