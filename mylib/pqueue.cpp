#include "pqueue.hh"

void PQ::push(void *elt) {
    Q.push_back(elt);
    QSZ = Q.size();
    siftup(QSZ-1);
}
void* PQ::pop() {
    void *ret = Q[0];
    Q[0] = Q[QSZ-1];
    Q[QSZ-1] = ret;
    Q.pop_back();
    QSZ = Q.size();
    if(QSZ > 1)
        siftdown(0, QSZ-1);
    return ret;
}

void PQ::heapify() {
    vector<void *>::size_type sz = Q.size();
    for(unsigned i=(sz-1)/2;i!=UINT_MAX;i--)
        siftdown(i, sz-1);
    
}
void PQ::siftup(unsigned ind) {
    unsigned parent;
    if(ind == 0) return;
    parent = (ind%2)?ind/2:(ind/2-1);
    unsigned prefChild;
    if(heapType == MINHEAP) {
        prefChild = (ind%2)?ind:((compare(Q[ind-1], Q[ind])<0)?(ind-1):ind);
        if(compare(Q[parent], Q[prefChild])>=0) {
            void *tmp = Q[parent];
            Q[parent] = Q[prefChild];
            Q[prefChild] = tmp;
            siftup(parent);
        }
    } else {
        prefChild = (ind%2)?ind:((compare(Q[ind-1], Q[ind])>0)?(ind-1):ind);
        if(compare(Q[parent], Q[prefChild])<=0) {
            void *tmp = Q[parent];
            Q[parent] = Q[prefChild];
            Q[prefChild] = tmp;
            siftup(parent);
        }
    }
}

void PQ::siftdown(unsigned ind, unsigned tail) {
    unsigned lc=ind*2+1, rc=ind*2+2;
    if(lc>tail || lc == ind) return;
    unsigned prefChild;

    if(heapType == MINHEAP) {
        prefChild = (rc>tail)?lc:((compare(Q[lc], Q[rc])<0)?lc:rc);
        if(compare(Q[ind], Q[prefChild])>=0) {
            void *tmp = Q[ind];
            Q[ind] = Q[prefChild];
            Q[prefChild] = tmp;
            siftdown(prefChild, tail);
        }
    } else {
        prefChild = (rc>tail)?lc:((compare(Q[lc], Q[rc])>0)?lc:rc);
        if(compare(Q[ind], Q[prefChild])<=0) {
            void *tmp = Q[ind];
            Q[ind] = Q[prefChild];
            Q[prefChild] = tmp;
            siftdown(prefChild, tail);
        }
    }
}

void PQ::set_HeapType(char type) {
    heapType = type;
    heapify();
}

void PQ::set_CompareCallback(int (*foo)(void *o1, void *o2)) {
    compare = foo;
    heapify();
}
