#ifndef __BST_HH_
#define __BST_HH_

#define EC_success 0
#define EC_dup 1
#define EC_failed -1
#define DIR_LEFT 0
#define DIR_RIGHT 1

#include <algorithm>
#include <stack>
#include <queue>
#include <stack>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <utility>

using namespace std;

class _bstnode;
typedef class _bstnode* p_BSTnode;
class _bstnode {
    protected:
        long data;
    public:
        p_BSTnode left;
        p_BSTnode right;
        _bstnode();
        virtual ~_bstnode();
        virtual long getdata();
        virtual void setdata(long val) { data = val; }
        int add_element(long element);
};

class _avlnode:public _bstnode {
    public:
        int height;
        _avlnode();
        ~_avlnode();
        int delete_element(long element);
};

extern int buildBST_from_Arr(p_BSTnode root, long arr[], int sz);
extern int buildAVL_from_Arr(_avlnode **rootp, long arr[], int sz);
#endif
