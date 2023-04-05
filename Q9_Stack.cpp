#include <iostream>
#include <cstring>
using namespace std;

#define MAX 100

class Stack 
{
    public:
        int top;
        char a[MAX];

    public:
        Stack() { top = -1; }
        bool isEmpty();
        char peek();
        char pop();
        bool push(char x);
};

int main()
{
    Stack s;
    cout<<"Enter expression: ";
    string exp;
    cin>>exp;
    bool flag=0;
    char str[exp.length()+1];
    strcpy(str, exp.c_str());
    for(int i=0;i<exp.length();i++)
    {
        if(str[i]=='{' or str[i]=='[' or str[i]=='(')
            s.push(str[i]);
        
        if(str[i]=='}' or str[i]==']' or str[i]==')')
        {
            char t = s.pop();
            if(str[i]=='}' and t=='{')
                continue;
            if(str[i]==']' and t=='[')
                continue;
            if(str[i]==')' and t=='(')
                continue;
            flag=1;
            break;
        }   
    }
    if(flag or !s.isEmpty())
        cout<<"Incorrect Formatting"<<endl;
    else
        cout<<"Correct Formatting"<<endl;
    return 0;
}

bool Stack::isEmpty()
{
    return (top < 0);
}

char Stack::peek()
{
    return a[top];
}

char Stack::pop()
{
    if(top<0)
    {
        return 0;
    }
    else
        return a[top--];
}

bool Stack::push(char x)
{
    if(top >=MAX-1)
    {
        return false;
    }
    else
    {
        a[++top] = x;
        return true;
    }
}
