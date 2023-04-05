#include <iostream>
#include <cstring>
using namespace std;

#define MAX 100

class DEQueue
{
public:
    int arr[MAX];
    int front, rear;
    
    DEQueue() {front = -1; rear = -1;}
    
    bool isEmpty();
    bool isFull();
    void push_front(int d);
    void push_rear(int d);
    int pop_front();
    int pop_rear();
    void display();
};

int main()
{
    DEQueue q;
    int flag = 1, temp;
    while(flag)
    {
        cout<<"~~~~~ DEQUEUE MENU ~~~~~"<<endl;
        cout<<"1. Push Front\n2. Push Rear\n3. Pop Front\n4. Pop back\n5. Display: ";
        int choice;
        cin>>choice;
        switch(choice)
        {
            case 1:
                cout<<"Enter element to push: ";
                cin>>temp;
                q.push_front(temp);
                break;
            
            case 2:
                cout<<"Enter element to push: ";
                cin>>temp;
                q.push_rear(temp);
                break;
                
            case 3:
                temp = q.pop_front();
                cout<<"Element "<<temp<<" has been popped!"<<endl;
                break;
                
            case 4:
                temp = q.pop_rear();
                cout<<"Element "<<temp<<" has been popped!"<<endl;
                break;
                
            case 5:
                q.display();
                break;
                
            default:
                cout<<"Wrong Input!"<<endl;
        }
        label:
        cout<<"Do you want to perform another operation? (1/0): ";
        cin>>flag;
        if(flag==1 or flag == 0)
            continue;
        else {
            cout<<"Wrong Input!"<<endl;
            goto label;
        }
    }
    return 0;
}

bool DEQueue::isEmpty()
{
    return front == -1;
}

bool DEQueue::isFull()
{
    return (front == 0 and rear == MAX - 1);
}

void DEQueue::push_front(int d)
{
    if(isEmpty())
    {
        front =0;
        rear = 0;
        arr[front] = d;
    }
    
    else if(isFull())
        cout<<"Queue Overflow, insertion not possible!"<<endl;
    
    else if(front!=0)
        cout<<"Insertion at front not possible!"<<endl;
    
    else
    {
        for(int i=rear;i>=front;i--)
            arr[i+1] = arr[i];
        arr[front] = d;
        rear++;
    }
}

void DEQueue::push_rear(int d)
{
    if(isEmpty())
    {
        front = 0;
        rear = 0;
        arr[front]=d;
    }
    
    else if(isFull())
        cout<<"Queue Overflow, Insertion not possible!"<<endl;
    
    else if(rear == MAX-1)
        cout<<"Insertion at end not possible!"<<endl;
    
    else{
        rear++;
        arr[rear] = d;
    }
}

int DEQueue::pop_front()
{
    if(isEmpty())
    {
        cout<<"Queue Underflow, cannot pop!"<<endl;
        return -1;
    }
    
    else if(front == rear)
    {
        int t = arr[front];
        front = -1;
        rear = -1;
        return t;
    }
    
    else
    {
        int t= arr[front];
        front++;
        return t;
    }
}

int DEQueue::pop_rear()
{
    if(isEmpty())
    {
        cout<<"Queue Underflow, cannot pop!"<<endl;
        return -1;
    }
    
    else if(front == rear)
    {
        int t = arr[front];
        front = -1;
        rear = -1;
        return t;
    }
    
    else
    {
        int t= arr[rear];
        rear--;
        return t;
    }
}

void DEQueue::display()
{
    if(isEmpty())
        cout<<"Queue is empty, nothing to display!"<<endl;
    
    else
    {
        for(int i = front;i<=rear;i++)
            cout<<arr[i]<<" ";
        cout<<endl;
    }
}
