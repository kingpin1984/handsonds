#include <stdio.h>

void swap(int arr[], int pos1, int pos2) {
    int tmp;
    tmp=arr[pos1];
    arr[pos1]=arr[pos2];
    arr[pos2]=tmp;
}

void heapify(int arr[], int end) {
int i=end, lnode, rnode, larger, root;

lnode=(end%2)?i:i-1;
rnode=i;
    while(i>0) {
        root=(lnode-1)/2;
        larger=(arr[lnode]>arr[rnode])?lnode:rnode;
        if(arr[root] < arr[larger]) {
            swap(arr, root, larger);
        }
        rnode=lnode-1;
        i=lnode=lnode-2;
    }
}

void siftdown(int arr[], int end) {
int i=0, lnode=0, rnode=0, larger=0;
lnode=(i*2)+1;
rnode=(i*2)+2;
for(;lnode <=end && rnode<=end;) {
    larger=arr[(i*2)+1] > arr[(i*2)+2]?(i*2)+1:(i*2)+2;
    if(arr[i] < arr[larger]) {
        swap(arr, i, larger);
        i=larger;
        lnode=(i*2)+1;
        rnode=(i*2)+2;
    }
    else break;
}
}
void heapsort(int arr[], int sz) {
int i=0;
heapify(arr, sz-1);
for(i=sz-1;i>=0;) {
    swap(arr, 0, i);
    siftdown(arr, --i);
}
}

/*int main() {
int arr[10]={5,8,1,2,6,0,9,7,3,4};

heapsort(arr, 10);
return 0;
}
*/
