/*
The ticket booking system of Cinemax theater has to
be implemented using C++ program.
There are 10 rows and 7 seats in each row. Doubly
circular linked list has to be maintained
to keep track of free seats at rows. Assume some
random booking to start with. Use array to store
pointers (Head pointer) to each row. On demand
a) The list of available seats is to be displayed
b) The seats are to be booked
c) The booking can be cancelled
*/

#include <iostream>
#include <cstring>
using namespace std;

class Node
{
public:
    int seat, status;
    Node *next;
    Node *prev;
};

class CDLL
{
public:
    Node *head, *tail, *temp;
    CDLL()
    {
        head = temp = NULL;
    }
    void create_list();
    void display();
    void book();
    void cancel();
    void availability();
};

int main()
{
    CDLL cinema;
    cinema.create_list();
    int choice;
    int flag =1;
    while(flag)
    {
        cinema.display();
        cout<<"\n*********************************************\n";
        cout<<" CINEMAX MOVIE THEATRE\n";
        cout<<"*********************************************\n";
        cout<<"\nEnter Choice\n1.Current Seat Status\n2.Book Seat \n3.Available Seat\n4.CancelSeat\n";
        cin>>choice;
        switch(choice)
        {
            case 1:
                cinema.display();
                break;
            case 2:
                cinema.book();
                break;
            case 3:
                cinema.availability();
                break;
            case 4:
                cinema.cancel();
                break;
            default:
                cout<<"Wrong Input!!"<<endl;
        }
        cout<<"Do you want to perform any other operation? (1 for yes/0 for no): ";
        cin>>flag;
    }
    return 0;
}

void CDLL::create_list()
{
    temp = new Node;
    temp->status=0;
    temp->seat=1;
    tail = head = temp;
    for(int i=2;i<=70;i++)
    {
        Node *t;
        t = new Node;
        t->seat = i;
        t->status = 0;
        tail->next = t;
        t->prev = tail;
        tail = t;
        tail->next = head;
        head->prev = tail;
    }
}

void CDLL::book()
{
    int no;
    cout<<"Which seat do you want to book?: ";
    cin>>no;
    if(no >=1 and no <= 70)
    {
        temp = head;
        while (temp->seat!=no)
            temp = temp->next;
        temp->status=1;
        cout<<endl<<"Seat number "<<no<<"booked"<<endl;
    }
    else
        cout<<"\nSeat Number out of range!"<<endl;
}

void CDLL::display()
{
    temp = head;
    int count =1;
    cout<<"\n-------------------------------------------------------"<<endl;
    cout<<"Screen This Way"<<endl;
    cout<<"-------------------------------------------------------"<<endl;
    while(temp->next!=head)
    {
        if(temp->seat/10==0)
            cout<<"S0"<<temp->seat;
        else
            cout<<"S"<<temp->seat;
        
        if(temp->status==0)
            cout<<"|___|";
        else
            cout<<"|_B_|";
        
        if(count%7==0)
            cout<<endl;
        temp=temp->next;
        count++;
    }
    
    // Last seat
    cout<<"S"<<temp->seat;
    if(temp->status==0)
        cout<<"|___|";
    else
        cout<<"|_B_|";
}

void CDLL::cancel()
{
    int no;
    cout<<"Which booking do you want to cancel?: ";
    cin>>no;
    if(no<=70 and no>=1)
    {
        temp = head;
        while(temp->seat!=no)
            temp=temp->next;
        temp->status=0;
        cout<<endl<<"Seat number "<<no<<"cancelled"<<endl;
    }
    else
        cout<<"\nSeat Number out of range!"<<endl;
}

void CDLL::availability()
{
    int no;
    cout<<"Which seat number's availability do you want to check?: ";
    cin>>no;
    if(no<=70 and no>=1)
    {
        temp = head;
        while(temp->seat!=no)
            temp=temp->next;
        if(temp->status==0)
            cout<<"\nNot Booked";
        else
            cout<<"\nBooked";
    }
    else
        cout<<"\nSeat Number out of range!"<<endl;
}
