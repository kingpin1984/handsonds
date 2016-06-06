#ifndef __TSMARTPTR_HH_
#define __TSMARTPTR_HH_ 

#include <iostream>
#include <sstream>
#include <string.h>

using namespace std;
class RC {
    protected:
        int refCount;
    public:
        RC():refCount(0) {}
        ~RC() {}
        inline void addRef() {
            ++refCount;
        }
        inline int Release() {
            return --refCount;
        }
        inline int getCount() {
            return refCount;
        }
};

template <typename T> class SPtr {
    private:
        T *dataobj;
        RC *reference;
    public:
        SPtr() {
            dataobj= new T();
            reference=new RC();
            reference->addRef();
        }
        SPtr(T* v):dataobj(v),reference(0) {
            reference=new RC();
            reference->addRef();
        }
        SPtr(const SPtr<T>& v):dataobj(v.dataobj),reference(v.reference) {
            reference->addRef();
        }
        ~SPtr() {
            //cout<<"Destroying "<<getprintable();
            if(reference->Release() == 0) {
                delete dataobj;
                delete reference;
            }
        }
        T& operator *() {
            return *dataobj;
        }
        T* operator ->() {
            return dataobj;
        }
        SPtr<T>& operator =(T* v) {
            if(reference->Release() == 0) {
                //cout<<"Destroying "<<getprintable();
                delete dataobj;
                delete reference;
            }
            dataobj=v;
            reference=new RC();
            reference->addRef();
            return *this;
        }
        SPtr<T>& operator =(const SPtr<T>& v) {
            if(this != v) {
                if(reference->Release() == 0) {
                    //cout<<"Destroying "<<getprintable();
                    delete dataobj;
                    delete reference;
                }
                dataobj=v.dataobj;
                reference=v.reference;
                reference->addRef();
            }
            return *this;
        }
        string getprintable() {
            ostringstream outs;
            outs<<*dataobj<<"("<<dataobj<<") ref:"<<reference->getCount()<<endl;
            return outs.str();
        }
};
#endif /* __TSMARTPTR_HH_ */
