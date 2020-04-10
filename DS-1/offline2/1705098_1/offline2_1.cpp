#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mx = 1e5;
void selection_sort(int ara[] , int n)
{
    int i, j, idx;
    for (i = 0; i < n-1; i++)
    {

        idx = i;
        for (j = i+1; j < n; j++)
        if (ara[j] < ara[idx])
            idx = j;

        swap(ara[idx], ara[i]);
    }
}
void insertion_sort(int ara[] , int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = ara[i];
        j = i - 1;
        while (j >= 0 && ara[j] > key)
        {
            ara[j+1] = ara[j];
            j--;
        }
        ara[j+1] = key;
    }
}
main()
{
    int n;
    cin>>n;
    int a[n];
    int b[n];
    int c[n];
    for(int i=0;i<n;i++)
    {
        a[i]=rand();
    }
    b[0]=1;
    for(int i=1;i<n;i++)
    {
        b[i]=b[i-1]+rand()%10;
    }
    c[0]=100000;
    for(int i=1;i<n;i++)
    {
        c[i]=c[i-1]-rand()%10;
    }
    ///Selection average case
    clock_t t_a= clock();
    selection_sort(a , n);
    printf("Time taken for selection sort for average case is : %.7f microsecond\n", (double)(clock() - t_a)*1000000/CLOCKS_PER_SEC);

    ///Selection best case
    clock_t t_b= clock();
    selection_sort(b , n);
    printf("Time taken for selection sort for best case is : %.7f microsecond\n", (double)(clock() - t_b)*1000000/CLOCKS_PER_SEC);

    ///Selection worst case
    clock_t t_c= clock();
    selection_sort(c , n);
    printf("Time taken for selection sort for worst case is : %.7f microsecond\n", (double)(clock() - t_c)*1000000/CLOCKS_PER_SEC);


    for(int i=0;i<n;i++)
    {
        a[i]=rand();
    }
    b[0]=1;
    for(int i=1;i<n;i++)
    {
        b[i]=b[i-1]+rand()%10;
    }
    c[0]=100000;
    for(int i=1;i<n;i++)
    {
        c[i]=c[i-1]-rand()%10;
    }

    ///Insertion average case
    clock_t t_aa= clock();
    insertion_sort(a , n);
    printf("Time taken for insertion sort for average case is : %.7f microsecond\n", (double)(clock() - t_aa)*1000000/CLOCKS_PER_SEC);

    ///Insertion best case
    clock_t t_bb= clock();
    insertion_sort(b , n);
    printf("Time taken for insertion sort for best case is : %.7f microsecond\n", (double)(clock() - t_bb)*1000000/CLOCKS_PER_SEC);

    ///Insertion worst case
    clock_t t_cc= clock();
    insertion_sort(c , n);
    printf("Time taken for insertion sort for worst case is : %.7f microsecond\n", (double)(clock() - t_cc)*1000000/CLOCKS_PER_SEC);


}
