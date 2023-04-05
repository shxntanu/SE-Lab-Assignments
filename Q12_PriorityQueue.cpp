#include <iostream>
using namespace std;
#define MAX 100

template<typename P>
struct item
{
    P data;
    int priority;
};

template<typename T>
class PQueue
{
public:
    item<T> queue[MAX];
    int count;

    PQueue() {count = -1;}

    void enqueue(T d, int p)
    {
        count++;
        queue[count].data = d;
        queue[count].priority = p;
    }

    int peek()
    {
        int max = 0;
        for(int i=0;i<=count;i++) {
            if(queue[i].priority > queue[max].priority)
                max = i;
        }
        return max;
    }

    void dequeue()
    {
        int max = peek();
        T temp = queue[max].data;
        for(int i=max;i<count;i++)
            queue[i] = queue[i+1];
        count--;
        cout<<"Element Dequeued is: "<<temp<<endl;
    }

    void display()
    {
        for(int i=0;i<=count;i++)
            cout<<"( "<<queue[i].data<<" , "<<queue[i].priority<<" )"<<endl;
    }
};

int main()
{
    cout<<"\nDo you want an integer queue or a float queue? (1/0): ";
    int c;
    cin>>c;
    if(c==1) {
        PQueue<int> q;
        int d,p;
        int flag = 1;
        while(flag)
        {
            cout<<"~~~~~ PQUEUE MENU ~~~~~"<<endl;
            cout<<"1. Insert Element\n2. Dequeue Element\n3. Display: ";
            int choice;
            cin>>choice;
            switch(choice)
            {
                case 1:
                    cout<<"\nEnter data: ";
                    cin>>d;
                    cout<<"Enter priority: ";
                    cin>>p;
                    q.enqueue(d, p);
                    break;

                case 2:
                    q.dequeue();
                    break;

                case 3:
                    q.display();
                    break;

                default:
                    cout<<"Wrong Input!!"<<endl;
            }
        label1:
            cout<<"Do you want to perform another operation? (1/0): ";
            cin>>flag;
            if(flag == 1 or flag == 0)
                continue;
            else{
                cout<<"Wrong Input!!"<<endl;
                goto label1;
            }
        }
    }
    else if(c==0)
    {
        PQueue<float> q;
        int p; float d;
        int flag = 1;
        while(flag)
        {
            cout<<"~~~~~ PQUEUE MENU ~~~~~"<<endl;
            cout<<"1. Insert Element\n2. Dequeue Element\n3. Display: ";
            int choice;
            cin>>choice;
            switch(choice)
            {
                case 1:
                    cout<<"\nEnter data: ";
                    cin>>d;
                    cout<<"\nEnter priority: ";
                    cin>>p;
                    q.enqueue(d, p);
                    break;

                case 2:
                    q.dequeue();
                    break;

                case 3:
                    q.display();
                    break;

                default:
                    cout<<"Wrong Input!!"<<endl;
            }
        label2:
            cout<<"Do you want to perform another operation? (1/0): ";
            cin>>flag;
            if(flag == 1 or flag == 0)
                continue;
            else{
                cout<<"Wrong Input!!"<<endl;
                goto label2;
            }
        }
    }
    return 0;
}
