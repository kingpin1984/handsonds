#ifndef __PQUEUE_HH_
#define __PQUEUE_HH_ 
#include <vector>
#include <limits.h>

#define MINHEAP 0
#define MAXHEAP 1

using namespace std;

class PQ {
        vector<void *> Q;
        vector<void *>::size_type QSZ;
        char heapType;
        int (*compare) (void *obj1, void *obj2);
    public:
        PQ(int (*foo)(void *o1, void *o2), char type=MINHEAP) {
            compare = foo;
            heapType = type;    //0: minheap 1:maxheap
        }
        ~PQ() {
        }
        void push(void *elt);
        void *pop();
        void set_HeapType(char type);
        void set_CompareCallback(int (*foo)(void *o1, void *o2));
    protected:
        void siftup(unsigned ind);
        void siftdown(unsigned ind, unsigned tail);
        void heapify();
};
#endif /* __PQUEUE_HH_ */
