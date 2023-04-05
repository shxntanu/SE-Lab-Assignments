#include <iostream>
#include <cstring>
using namespace std;
#define MAX 100

class Stack {

public:
    char a[MAX];
    int top;
    Stack(){ top = -1; }
    bool push(char c);
    char pop();
    char peek();
    bool isEmpty();
};

int precedence(char c)
{
    if(c=='*' or c=='/')
        return 2;
    else if (c=='+' or c=='-')
        return 1;
    else
        return -1;
}

int main()
{
    Stack s;
    string e;
    cout<<"Enter Expression: ";
    cin>>e;
    char exp[e.length()];
    strcpy(exp, e.c_str());
    bool flag=0;
    string result="";
    for(int i=0;i<e.length();i++)
    {
        char c = exp[i];
        if(c=='{' or c=='[' or c=='(')
            s.push(c);

        if(c=='}' or c==']' or c==')')
        {
            char t = s.pop();
            if(c=='}' and t=='{')
                continue;
            else if(c==']' and t=='[')
                continue;
            else if(c==')' and t=='(')
                continue;
            else
                flag=1;
                break;
        }
    }
    if(flag)
    {
        cout<<"Wrongly Formatted Expression!"<<endl;
        return 0;
    }
    else
    {
        for(int i=0;i<e.length();i++)
        {
            char c = exp[i];

            if(c=='(' or c=='{' or c=='[')
                s.push(c);

            else if((c>='a' and c<='z') or (c>='A' and c<='Z') or (c>='0' and c<='9'))
                result += c;

            else if(c==')')
            {
                while(s.peek()!='(')
                    result += s.pop();
                s.pop();
            }
            else if(c=='}')
            {
                while(s.peek()!='{')
                    result += s.pop();
                s.pop();
            }
            else if(c==']')
            {
                while(s.peek()!='[')
                    result += s.pop();
                s.pop();
            }
            else
            {
                while(!s.isEmpty() and precedence(exp[i]) <= precedence(s.peek()))
                    result+=s.pop();
                s.push(c);
            }
        }
        while(!s.isEmpty())
            result+=s.pop();

        cout<<"\nPostfix Expression: "<<result<<endl;

        for(int i=0;i<result.length();i++)
        {
            char c = result[i];
            if(c >= 48 and c <= 57)
                s.push(c);
            else {
                int res;
                int a = s.pop() - 48;
                int b = s.pop() - 48;
                if(c == '+')
                    res = b+a;
                else if(c == '-')
                    res = b-a;
                else if(c=='*')
                    res = b*a;
                else if(c == '/')
                    res = b/a;
                s.push(res+48);
            }
        }
        cout<<"Result: "<<s.peek()<<endl;
    }
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
