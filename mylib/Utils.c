#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Utils.h"

long alloc_intarr(int *arr, long sz, int mod) {
    int i=0;
    srand(time(0));
    
    for(i=0;i<sz;i++) {
        if(mod)
            arr[i]=rand()%mod;
        else
            arr[i]=rand();
    }
    return sz;
}

