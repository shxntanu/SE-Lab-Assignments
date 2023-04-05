/* Write C++ program for storing appointment schedule for day. Appointments are booked
   randomly using linked list. Set start and end time and min and max duration for visit slot.
   Write functions for- a) Display free slots b) Book appointment c) Cancel appointment (
   check validity, time bounds, availability) d) Sort list based on time e) Sort list based on time
   using pointer manipulation
 */

#include <iostream>
using namespace std;

class Node
{
public:
    int status;
    int stime;
    int min, max;
    Node *next;
};

class Appointment
{
public:
    Node *head, *tail, *temp;
    Appointment()
    {
        head = tail = NULL;
    }
    
    void create();
    void freeslots();
    void book();
    void cancel();
};

int main()
{
    Appointment a;
    a.create();
    int choice;
    int flag =1;
    while(flag)
    {
        cout<<"\n~~~~~ DOCTOR ~~~~~"<<endl;
        cout<<"Enter: \n1. Check Free slots\n2. Book a slot\n3. Cancel a booking:  ";
        cin>>choice;
        switch (choice)
        {
            case 1:
                a.freeslots();
                break;
            
            case 2:
                a.book();
                break;
            
            case 3:
                a.cancel();
                break;
            
            default:
                cout<<"\nWrong input"<<endl;
        }
        label:
        cout<<"\nDo you want to perform any other operation? (1/0): ";
        cin>>flag;
        if(flag == 1 or flag == 0)
            continue;
        else
        {
            cout<<"Wrong Input!"<<endl;
            goto label;
        }
        
    }
    return 0;
}


void Appointment::create()
{
    // Assuming a 9 to 5 work day
    temp = new Node;
    temp->stime=9;
    head = tail = temp;
    int counter = 10;
    for(int i=2;i<=8;i++)
    {
        Node *t = new Node;
        t->status=0;
        t->stime = counter++;
        tail->next = t;
        tail = t;
    }
}

void Appointment::freeslots()
{
    temp = head;
    while(temp!=NULL)
    {
        if(temp->status==0)
            cout<<"Slot at "<<temp->stime<<" is empty"<<endl;
        temp=temp->next;
    }
}

void Appointment::book()
{
    int time;
    cout<<"\nEnter the time which you want to book (9-17): ";
    cin>>time;
    if(time>=9 and time<17)
    {
        temp = head;
        while(temp->stime!=time)
            temp=temp->next;
        temp->status=1;
        cout<<"\nEnter the minimum time: ";
        cin>>temp->min;
        cout<<"\n Enter the maximum time: ";
        cin>>temp->max;
        cout<<"\nTime slot of "<<temp->stime<<" has been booked"<<endl;
    }
    else
        cout<<"Wrong time!";
}

void Appointment::cancel()
{
    int time;
    cout<<"\nEnter the time which you want to cancel (9-17): ";
    cin>>time;
    temp = head;
    while(temp->stime!=time)
        temp=temp->next;
    temp->status=0;
    cout<<"\nTime slot of "<<temp->stime<<" has been cancelled"<<endl;
}
