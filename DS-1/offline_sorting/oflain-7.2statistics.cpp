#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<chrono>
#define debug 0
#define MAX 100000
#define SENTINEL 1000000

 using namespace std;
 using namespace std::chrono;

int arraySize[] = {10,100,200,500,1000,2000,5000,10000,25000};

 void swapp(int &x, int &y)
 {
     int t;
     t=x;
     x=y;
     y=t;
 }

 void print(string s, int a)
 {
     cout<<s<<" is "<<a<<endl;
 }

 void printArr(int *arr,int n)
 {
     cout<<"Elements are: ";
     for(int i=0;i<n;i++)
     {
         cout<<i[arr]<<" ";
     }
     cout<<endl;
     cout<<endl;
     cout<<endl;
 }

void copyArr(int *src,int *dest,int n)
{
     for(int i=0;i<n;i++)
     {
          dest[i]=src[i];
     }
}

void revArr(int *arr,int n)
{
     for(int i=0,j=n-1;i<n/2;i++,j--)
          swapp(arr[i],arr[j]);
}

/*void generateArray(int *p,int sz)
{

     p=new int[sz];
     for(int j=0;j<sz;j++)
     {
          p[j]=rand()%MAX;
     }
}*/





int Partition(int *arr,int l, int r)
{
     int x=arr[r];
     int i=l-1;
     for(int j=l;j<r;j++)
     {
          if(arr[j]<=x)
          {
               i++;
               swapp(arr[i],arr[j]);
          }
     }
     swapp(arr[i+1],arr[r]);
     return i+1;
}

int quicksort(int *arr,int l, int r)
{
     if(l<r)
     {
          int mid=Partition(arr,l,r);
          quicksort(arr,l,mid-1);
          quicksort(arr,mid+1,r);
     }
}





void merge(int *arr,int l,int r,int mid)
{
    int n1=mid-l+1;
    int n2=r-mid;

    int *larr=new int[n1+1];
    int *rarr=new int[n2+1];

    for(int i=0,j=l;i<n1;i++,j++) larr[i]=arr[j];
    for(int i=n2-1,j=r;i>=0;i--,j--) rarr[i]=arr[j];

    larr[n1]=SENTINEL;
    rarr[n2]=SENTINEL;

    bool larr_done=false, rarr_done=false;

    for(int k=l,i=0,j=0;k<=r;k++)
    {
        if(larr[i]<=rarr[j])
        {
            arr[k]=larr[i];
            i++;
        }

        else if(larr[i]>rarr[j])
        {
            arr[k]=rarr[j];
            j++;
        }
    }

    delete[]larr;
    delete[]rarr;

}

void mergesort(int *arr,int l, int r)
{
    if(l<r)
    {
        int mid=(l+r)/2;
        mergesort(arr,l,mid);
        mergesort(arr,mid+1,r);
        merge(arr,l,r,mid);
    }
}

int main()
{freopen("mergesort+quicksort statistics notun laptop.txt","w",stdout);
     int sz,len,times;
     int *arr,*arr2,*arrq;
     string s;
     srand(time(NULL));

     len=sizeof(arraySize)/sizeof(int);
     for(int i=0;i<len;i++)
     {
         sz=arraySize[i];
         cout<<"array size is: "<<sz<<endl;
         times=1000000/sz;

         arr = new int[sz];
         arr2 = new int[sz];
         arrq = new int[sz];

         for(int j=0;j<sz;j++)
         {
             arr[j]=rand()%MAX;
         }
         copyArr(arr,arrq,sz);

         ///average case for merge sort
            copyArr(arr,arr2,sz);
            auto t1 = high_resolution_clock::now();
            for(int t=0;t<times;t++)
            {
                 mergesort(arr,0,sz-1);
                 copyArr(arr2,arr,sz);
            }

            auto t2 = high_resolution_clock::now();

            auto duration1 = duration_cast<microseconds>( t2 - t1 ).count();

            t1 = high_resolution_clock::now();
            for(int t=0;t<times;t++)
            {
                 copyArr(arr2,arr,sz);
            }

            t2 = high_resolution_clock::now();

            auto duration2 = duration_cast<microseconds>( t2 - t1 ).count();

            auto duration = duration1-duration2;
            duration=duration/times;
            printf("Time taken for merge sort in average case: %d microseconds\n",duration);




            ///ascending order for merge sort
            mergesort(arr,0,sz-1);
            t1 = high_resolution_clock::now();
            for(int t=0;t<times;t++)
            {
                 mergesort(arr,0,sz-1);
            }

            t2 = high_resolution_clock::now();

            duration1 = duration_cast<microseconds>( t2 - t1 ).count();

            duration=duration1/times;
            printf("Time taken for merge sort initially in ascending order: %d microseconds\n",duration);



            ///descending order for merge sort
            revArr(arr,sz);
            copyArr(arr,arr2,sz);
            t1 = high_resolution_clock::now();
            for(int t=0;t<times;t++)
            {
                 mergesort(arr,0,sz-1);
                 copyArr(arr2,arr,sz);
            }

            t2 = high_resolution_clock::now();

            duration1 = duration_cast<microseconds>( t2 - t1 ).count();

            t1 = high_resolution_clock::now();
            for(int t=0;t<times;t++)
            {
                 copyArr(arr2,arr,sz);
            }

            t2 = high_resolution_clock::now();

            duration2 = duration_cast<microseconds>( t2 - t1 ).count();

            duration = duration1-duration2;
            duration=duration/times;
            printf("Time taken for merge sort initially in descending order: %d microseconds\n",duration);


            cout<<endl;



            ///average case for quick sort
            copyArr(arrq,arr,sz);
            copyArr(arrq,arr2,sz);
            t1 = high_resolution_clock::now();
            for(int t=0;t<times;t++)
            {
                 quicksort(arr,0,sz-1);
                 copyArr(arr2,arr,sz);
            }

            t2 = high_resolution_clock::now();

            duration1 = duration_cast<microseconds>( t2 - t1 ).count();

            t1 = high_resolution_clock::now();
            for(int t=0;t<times;t++)
            {
                 copyArr(arr2,arr,sz);
            }

            t2 = high_resolution_clock::now();

            duration2 = duration_cast<microseconds>( t2 - t1 ).count();

            duration = duration1-duration2;
            duration=duration/times;
            printf("Time taken for quick sort in average case: %d microseconds\n",duration);




            ///ascending order for quick sort
            quicksort(arr,0,sz-1);
            t1 = high_resolution_clock::now();
            for(int t=0;t<times;t++)
            {
                 quicksort(arr,0,sz-1);
            }

            t2 = high_resolution_clock::now();

            duration1 = duration_cast<microseconds>( t2 - t1 ).count();
            duration=duration1/times;
            printf("Time taken for quick sort initially in ascending order: %d microseconds\n",duration);



            ///descending order for quick sort
            revArr(arr,sz);
            copyArr(arr,arr2,sz);
            t1 = high_resolution_clock::now();
            for(int t=0;t<times;t++)
            {
                 quicksort(arr,0,sz-1);
                 copyArr(arr2,arr,sz);
            }

            t2 = high_resolution_clock::now();

            duration1 = duration_cast<microseconds>( t2 - t1 ).count();

            t1 = high_resolution_clock::now();
            for(int t=0;t<times;t++)
            {
                 copyArr(arr2,arr,sz);
            }

            t2 = high_resolution_clock::now();

            duration2 = duration_cast<microseconds>( t2 - t1 ).count();

            duration = duration1-duration2;
            duration=duration/times;
            printf("Time taken for quick sort initially in descending order: %d microseconds\n",duration);

            cout<<endl<<endl;

            delete[]arr;
            delete[]arr2;
            delete[]arrq;



     }


}
