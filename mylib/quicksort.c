#include <stdio.h>
#include <stdlib.h>

void arrswap(int arr[], int pos1, int pos2) {
    arr[pos1]^=arr[pos2];
    arr[pos2]^=arr[pos1];
    arr[pos1]^=arr[pos2];
}

void quickc(int arr[], int start, int end) {

    int up = start, down = end, i=0;
    int pivot = up++;
    //arrswap(arr, pivot, start);
    while(arr[pivot] > arr[up] && up < down) up++;
    while(down >= up) {
        if(arr[pivot] <= arr[down]) down--;
        else
            arrswap(arr, up++, down--);
    }
    up--;
    arrswap(arr, up, pivot);
    pivot = up;
    printf("pivot: %d, val: %d", pivot, arr[pivot]);
    printf("array status for bounds(%d, %d):\n\t", start, end);
    for(i=start; i<=end; i++)
        printf("%d ", arr[i]);
    quickc(arr, start, pivot-1);
    quickc(arr, pivot+1, end);
}

/*
int main() {
    int arr[10] = {3,6,7,1,8,5,4,9,2,0};
    int start = 0, end=9;

    quickc(arr, start, end);
    return 0;
}
*/
