#include <iostream>
#include "pqueue.hh"
#include "Utils.h"

using namespace std;
struct tds {
    int val;
};

int mycompare(void *e1, void *e2) {
    if(((tds *)e1)->val > ((tds *)e2)->val) return 1;
    if(((tds *)e1)->val < ((tds *)e2)->val) return -1;
    return 0;
}
    
int main(int argc,char *argv[]) {

    unsigned sz=0, mod = 0;
    int order = MINHEAP;
    cout<<"Enter max queue size:";
    cin>>sz;
    cout<<"Enter mod val(0 for default):";
    cin>>mod;
    cout<<"Enter Order of heap(0:min 1:max):";
    cin>>order;
    cout<<"Current order:"<<order;
    int *arr = new int[sz];

    PQ pq(mycompare, order);
    alloc_intarr(arr, sz, mod);
    cout<<"Base arr:"<<endl;
    for(unsigned i=0;i<sz;i++) {
        tds *nd = new tds;
        nd->val = arr[i];
        cout<<arr[i]<<" ";
        pq.push(nd);
    }

    cout<<endl<<endl<<"Pop(2) queue:"<<endl;
    for(unsigned i=0;i<2;i++) {
        tds *nd = (tds *)(pq.pop());
        if(nd)
            cout<<nd->val<<" ";
        else {
            cout<<"Pop failed. Something went wrong..."; break;
        }
    }
    cout<<endl;
    cout<<"Toggle heap type:";
    pq.set_HeapType(!(order));
    cout<<endl<<endl<<"Pop queue:"<<endl;
    for(unsigned i=0;i<sz-2;i++) {
        tds *nd = (tds *)(pq.pop());
        if(nd)
            cout<<nd->val<<" ";
        else {
            cout<<"Pop failed. Something went wrong..."; break;
        }
    }
    cout<<endl;
    return 0;
}
