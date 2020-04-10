//#include<iostream>
//#include<string>
//#include<cmath>
//#include<cstring>
//#include<cstdlib>
//#include<cstdio>
//#include<chrono>
//#include<vector>
#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

char sample[62];

void print(string s, int a)
{
    cout<<s<<" is "<<a<<endl;
}

void printArr(char *arr,int n)
{
    cout<<"Elements are: ";
    for(int i=0; i<n; i++)
    {
        cout<<i[arr]<<" ";
    }
    cout<<endl;
}

void ps(char ar[], int len)
{

    vector<string> power_set;

    long long int sz=pow(2,len);
    cout<<"size of power set is: "<<sz<<endl;

    for(long long int i=0; i<sz; i++)
    {
        string ss="{ ";
        for(int j=0; j<len; j++)
        {
            if(i & 1<<j)
            {
                ss = ss+ar[j]+" ";

            }
        }
        ss=ss+"}";
        power_set.push_back(ss);
    }
    for(string s: power_set)
        cout<<s<<endl;
}

void generateSample()
{
    int i,j;
    for(i=0,j=48; i<10; j++,i++)
        sample[i]=j;
    for(j=65; j<=90; j++,i++)
        sample[i]=j;
    for(j=97; j<=122; j++,i++)
        sample[i]=j;
}

int main()
{
    char *arr;
    string s;
    int sz,len;
    bool printPowerSet;
    srand(time(NULL));

    generateSample();

    int sampleSize = sizeof(sample)/sizeof(char);

    cout<<"the size of the array is: ";
    cin>>sz;

    print("size", sz);

    arr = new char[sz];

    for(int j=0; j<sz; j++)
    {
        int idx=rand()%sampleSize;
        arr[j]=sample[idx];
    }
    printArr(arr,sz);
    auto t1 = high_resolution_clock::now();
    ps(arr,sz);
    auto t2 = high_resolution_clock::now();

    auto duration1 = duration_cast<microseconds>( t2 - t1 ).count();
    cout <<"Time required to generate power set is: "<< duration1<<" microseconds"<<endl<<endl;
    //cout << duration1<<endl;
    delete[]arr;


}
