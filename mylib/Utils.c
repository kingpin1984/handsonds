#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Utils.h"

long alloc_intarr(int *arr, long sz, int mod) {
    int i=0;
    srand(time(0));
    mod = (mod==0)?1:mod;
    
    for(i=0;i<sz;i++) {
        arr[i]=rand()%mod;
    }
    return sz;
}

