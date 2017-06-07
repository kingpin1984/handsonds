#ifndef __PQUEUE_HH_
#define __PQUEUE_HH_ 
#include <vector>
#include <limits.h>

using namespace std;

class PQ {
        vector<void *> Q;
        vector<void *>::size_type QSZ;
        int (*compare) (void *obj1, void *obj2);
    public:
        PQ(int (*foo)(void *o1, void *o2)) {
            compare = foo;
        }
        ~PQ() {
        }
        void push(void *elt);
        void *pop();
        void siftup(unsigned ind);
        void siftdown(unsigned ind, unsigned tail);
        void heapify();
};
#endif /* __PQUEUE_HH_ */
