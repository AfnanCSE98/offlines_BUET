#include <cstdio>
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
void GenerateBestCase(int A[], int l, int r){    if(r-l+1 < 3) return;    int mid = (l+r)/2;    GenerateBestCase(A, mid+1, r);    swap(A[r], A[mid]);    GenerateBestCase(A, l, mid);}
int main()
{
    int choice, n;

    while(1)
    {
        printf("1. Generate average case\n");
        printf("2. Generate best case\n");
        printf("3. Generate worst case\n");
        printf("4. Apply Merge sort\n");
        printf("5. Apply Quicksort\n");
        printf("6. Print array\n");
        printf("> ");
        scanf("%d", &choice);
        int a[maxsize];
        switch(choice)
        {
        case 1:
        {
            printf("Number of elements: ");
            scanf("%d", &n);
            int ara[n+1];
            for(int i=1; i<=n; i++)
            {
                ara[i] = rand()%1000;
               // cout<<ara[i]<<"--";
            }
            for(int i=1; i<=n; i++)
            {
                a[i] = ara[i];
            }

            break;
        }
        case 2:
        {
            printf("Number of elements: ");
            scanf("%d", &n);
            int ara[n+1];
            ara[1] = 10;
            for(int i=2; i<=n; i++)
            {
                ara[i] = ara[i-1]+rand()%1000;
            }
            GenerateBestCase(ara , 1 , n);
            for(int i=1; i<=n; i++)
            {
                a[i] = ara[i];
            }
            break;

        }
        case 3:
        {
            printf("Number of elements: ");
            scanf("%d", &n);
            int ara[n+1];
            ara[1] = 10000;
            for(int i=2; i<=n; i++)
            {
                ara[i] = ara[i-1]-rand()%1000;
            }
            for(int i=1; i<=n; i++)
            {
                a[i] = ara[i];
            }
            break;

        }
        case 4:
        {
            printf("Applying merge sort\n");
            const clock_t begin_time = clock();
            mergeSort(a, 1, n);

            printf("Time taken to finish: <your time>");
            cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC<<endl;

            break;
        }
        case 5:
        {
            printf("Applying quicksort\n");

            const clock_t begin_time = clock();
            quickSort(a, 1, n);

            printf("Time taken to finish: <your time>");
            cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC<<endl;
            break;

        }
        case 6:
            printf("Array\n");
            print(a, n);
            break;
        }
    }
}
