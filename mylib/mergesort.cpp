#include<cstdio>
#include<iostream>
#include<time.h>
#include<cstdlib>

using namespace std;

//extern void quick(int arr[], int start, int end);

void merge(int arr[], int lend, int rend, int shadow[]) {

    int mid=(lend+rend)/2;
    int i,j,k;
    if(lend==rend) return;
    merge(arr, lend, mid, shadow);
    merge(arr, mid+1, rend, shadow);
    for(i=lend, j=mid+1,k=lend;i<=mid&&j<=rend;)
        if(arr[i]<arr[j])
            shadow[k++]=arr[i++];
        else
            shadow[k++]=arr[j++];
    if(i>mid)
        while(j<=rend) shadow[k++]=arr[j++];
    if(j>rend)
        while(i<=mid) shadow[k++]=arr[i++];
    for(i=lend;i<=rend;i++) arr[i]=shadow[i];
        
}

void mergesort(int arr[], int sz) {
    int *shadow = new int[sz];
    int lend=0, rend=sz-1;
    merge(arr, lend, rend, shadow);
    return;
}

int main() {

    int size;
    int *arr;
    //int staticarr[10]={5,2,7,8,1,5,6,9,3,21};
    
    cout<<"Enter size of the array:";
    cin>>size;

    arr = new int[size];
    srand(time(0));
    for(int i=0;i<size;i++)
        arr[i]=rand()%(size*3);

    //size=10;
    for(int i=0;i<size;i++)
        cout<<arr[i]<<" ";
    mergesort(arr, size);

    cout<<endl<<"Sorted arr:";
    for(int i=0;i<size;i++)
        cout<<arr[i]<<" ";
    cout<<endl;

    cout<<endl<<"Sorted arr using quick:";
    //quick(arr,0, size-1);
    for(int i=0;i<size;i++)
        cout<<arr[i]<<" ";
    cout<<endl;
    return 0;
}
