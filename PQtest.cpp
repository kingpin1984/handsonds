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

    PQ pq(mycompare);
    unsigned sz=0;
    cout<<"Enter max queue size:";
    cin>>sz;
    int *arr = new int[sz];

    alloc_intarr(arr, sz, 0);
    cout<<"Base arr:"<<endl;
    for(unsigned i=0;i<sz;i++) {
        tds *nd = new tds;
        nd->val = arr[i];
        cout<<arr[i]<<" ";
        pq.push(nd);
    }

    cout<<endl<<endl<<"Pop queue:"<<endl;
    for(unsigned i=0;i<sz;i++) {
        tds *nd = (tds *)(pq.pop());
        if(nd)
            cout<<" "<<nd->val;
        else {
            cout<<"Pop failed. Something went wrong..."; break;
        }
    }
    cout<<endl;
    return 0;
}
