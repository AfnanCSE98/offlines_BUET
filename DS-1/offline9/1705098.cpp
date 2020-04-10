#include <bits/stdc++.h>
using namespace std;
struct Activitiy
{
    int start, finish;
};
void swap(Activitiy* s1 , Activitiy*  s2)
{
    Activitiy tmp = *s1;
    *s1=*s2;
    *s2 = tmp;
}
int Partition(Activitiy ara[] , int low ,int high)
{
    int x = ara[high].finish;
    int i = low-1;
    for(int j=low;j<=high-1;j++){
        if(ara[j].finish<=x){
            i++;
            swap(&ara[i] , &ara[j]);
        }
    }
    swap(&ara[high] , &ara[i+1]);
    return i+1;
}
void quickSort(Activitiy ara[] , int low , int high)
{
    if(low < high){
        int piv = Partition(ara , low , high);
        quickSort(ara , low , piv-1);
        quickSort(ara , piv+1 , high);
    }

}
void printMaxActivities(Activitiy ara[] , int n)
{
    int i=0;
    cout<<"\nThe maximum optimal subset is : "<<endl;
    cout<<"("<<ara[i].start<<" "<<ara[i].finish<<") ";
    int no=0;
    for(int j=1;j<n;j++)
    {

        if(ara[j].start>=ara[i].finish)
        {
            cout<<"("<<ara[j].start<<" "<<ara[j].finish<<") ";
            no++;
            i=j;
        }
    }
    cout<<"\nAnd The number of maximum possible activities is "<<no<<endl;

}
int main()
{
    int n=rand()%100;
    cout<<"The no of activities is "<<n<<endl;
    Activitiy ara[n];
    cout<<"The activity list is"<<endl;
    for(int i=0;i<n;i++)
    {
        int a=rand()%24;
        int b=rand()%24;
        if(a>b){
            swap(a,b);
        }
        ara[i].start=a;
        ara[i].finish=b;
        cout<<"("<<ara[i].start<<" "<<ara[i].finish<<")";
    }
    quickSort(ara,0,n-1);

    printMaxActivities(ara , n);



}
