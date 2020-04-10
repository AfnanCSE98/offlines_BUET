#include<bits/stdc++.h>
using namespace std;

#define bound 10

class Stack{
    int sz=-1;
    int len=0;
    int *ara;
public:
    Stack()
    {
        ara = new int[bound];
        len=bound;
    }
    int* create_new()
    {
        int* new_ara;
        new_ara = new int[len+bound];
        for(int i=0;i<len;i++)
        {
            new_ara[i] = ara[i];
        }
        len+=bound;
        return new_ara;
    }
    void push(int val)
    {
        if(sz==len-1)
        {
            ara = create_new();
        }
        ara[++sz] = val;
    }
    int pop()
    {
       sz--;
       cout<<"pop function called!\n";
    }
    bool empty()
    {
        return sz<=0;
    }
    int size()
    {
        return sz+1;
    }
    int top()
    {
        return ara[sz];
    }
    void display()
    {
         if (sz == -1)
            cout << "Stack is Empty" << endl;
         else {
            cout << "Stack: ";
            for (int i = 0; i <= sz; i++)
                cout << ara[i] << " ";
            cout << endl;
    }
    }
};
main()
{
    Stack s;

    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.pop();
    cout<<"top element of stack is "<<s.top()<<endl;
    cout<<"the size of the stack is "<<s.size()<<endl;
    s.display();
}
