#include <bits/stdc++.h>
using namespace std;
#define maxsz 100
struct subset
{
    int parent;
    int rank;
};
class disjointSet
{
public:
    subset *ara;
    disjointSet()
    {
        ara = new subset[maxsz];
        for(int i=0; i<maxsz; i++)
        {
            ara[i].parent = -1;
        }
    }
    void MakeSet(int x)
    {
        ara[x].parent = x;
        ara[x].rank = 0;
    }
    int Findset(int x)
    {
        if(ara[x].parent != x)
        {
            ara[x].parent = Findset(ara[x].parent);
        }
        return ara[x].parent;
    }
    void Union(int x, int y)
    {
        int xroot = Findset(x);
        int yroot = Findset(y);

        if(xroot==yroot)
            return;

        if(ara[xroot].rank < ara[yroot].rank)
        {
            ara[xroot].parent = yroot;
        }
        else
        {
            ara[yroot].parent = xroot;
        }
        if(ara[xroot].rank == ara[yroot].rank)
        {
            ara[xroot].rank++;
        }
    }
    void print(int u)
    {
        int p=Findset(u);

        for(int i=0; i<maxsz; i++)
        {
            if(ara[i].parent!=-1)
            {
                if(Findset(i)==p)
                {
                    cout<<i<<" ";
                }
            }

        }
        cout<<endl;
    }
};
int main()
{
    disjointSet s;
    while(1)
    {
        cout<<"\n1.Make Set\t 2.Find Set\t 3.Union\t 4.print\t 5.quit\n";
        int ch;
        int val,data;
        cin>>ch;
        if(ch==1)
        {
            cout<<"enter the element to insert: ";
            cin>>val;
            s.MakeSet(val);
        }
        if(ch==2)
        {
            cout<<"Enter the element to find its parent: ";
            cin>>val;
            cout<<"The parent is "<<s.Findset(val);
        }
        if(ch==3)
        {
            cout<<"Enter two elements to union: ";
            cin>>val>>data;
            s.Union(val, data);
        }
        if(ch==4)
        {
            cout<<"Enter the root of tree you want to print: ";
            cin>>val;
            s.print(val);
        }
        if(ch==5)
        {
            break;
        }
    }
}
