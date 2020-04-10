#include <cstdio>
#include <iostream>
#define _POSIX_C_SOURCE 199309L
#include <ctime>
#include <algorithm>
#include<bits/stdc++.h>
using namespace std;
#define maxsize 100010
void Merge(int ara[], int low, int mid, int high)
{
    int n1 = mid-low+1;
    int n2 = high-mid;
    int L[n1+1],R[n2+1];
    for(int i=1; i<=n1; i++)
    {
        L[i] = ara[low+i-1];
    }
    for(int i=1; i<=n2; i++)
    {
        R[i] = ara[mid+i];
    }
    L[n1+1] = INT_MAX;
    R[n2+1] = INT_MAX;
    int i=1;
    int j=1;
    for(int k=low; k<=high; k++)
    {
        if(L[i]<=R[j])
        {
            ara[k] = L[i];
            i++;
        }
        else
        {
            ara[k] = R[j];
            j++;
        }
    }
}
void mergeSort(int ara[], int low, int high)
{
    if(low<high)
    {
        int mid = (low+high)/2;
        mergeSort(ara, low, mid);
        mergeSort(ara, mid+1, high);
        Merge(ara,low,  mid, high );
    }
}
int Partition(int ara[] , int low ,int high)
{
    int x = ara[high];
    int i = low-1;
    for(int j=low;j<=high-1;j++){
        if(ara[j]<=x){
            i++;
            swap(ara[i] , ara[j]);
        }
    }
    swap(ara[high] , ara[i+1]);
    return i+1;
}
void quickSort(int ara[] , int low , int high)
{
    if(low < high){
        int piv = Partition(ara , low , high);
        quickSort(ara , low , piv-1);
        quickSort(ara , piv+1 , high);
    }
}
void print(int ara[], int n)
{
    for(int i=1; i<=n; i++)
    {
        cout<<ara[i]<<" ";
    }
    cout<<endl;
}
double getTime(void (*f) (int*, int, int), int *a, int l, int r)
{
    struct timespec start, stop;
    double elapsed;

    clock_gettime(CLOCK_MONOTONIC, &start);

    (*f)(a, l, r);

    clock_gettime(CLOCK_MONOTONIC, &stop);

    elapsed = (stop.tv_sec - start.tv_sec) * 1e3;
    elapsed = elapsed + (stop.tv_nsec - start.tv_nsec) / 1e6;

    return elapsed;
}
int main()
{
   int n, *input_size, *a, *b;
    struct timespec start, stop;
    double elapsed;
    double merge_avg, quick_avg, merge_best, quick_best, merge_worst, quick_worst;

    input_size = new int[8];
    input_size[0] = 10, input_size[1] = 100, input_size[2] = 200, input_size[3] = 500;
    input_size[4] = 1000, input_size[5] = 2000, input_size[6] = 5000, input_size[7] = 10000;

    for(int i = 0; i < 8; i++)
    {
        n = input_size[i];

        merge_avg = 0;
        quick_avg = 0;
        merge_best = 0;
        quick_best = 0;
        merge_worst = 0;
        quick_worst = 0;

        for(int i = 0; i < 5; i++){

            a = new int[n];
            b = new int[n];

            for(int i = 0; i < n; i++){
                a[i] = rand();
                b[i] = a[i];
            }

            merge_avg += getTime(mergeSort, a, 0, n - 1);
            quick_avg += getTime(quickSort, b, 0, n - 1);

            merge_best += getTime(mergeSort, a, 0, n - 1);
            quick_best += getTime(quickSort, a, 0, n - 1);

            sort(a, a + n, greater<int>());

            merge_worst += getTime(mergeSort, a, 0, n - 1);
            quick_worst += getTime(quickSort, a, 0, n - 1);
        }

        cout << "n = " << n << ":\n";

        cout << "best:     " << "merge: " << merge_best / 5 << " millisec" << "    quick: " << quick_best / 5 << " millisec" << endl;
        cout << "avg:     " << "merge: " << merge_avg / 5 << " millisec" << "    quick: " << quick_avg / 5 << " millisec" << endl;
        cout << "worst:     " << "merge: " << merge_worst / 5 << " millisec" << "    quick: " << quick_worst / 5 << " millisec" << endl;

    }
}
