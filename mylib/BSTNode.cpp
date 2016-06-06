#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "BSTNode.hh"

enum {
    LEFT,
    RIGHT
};

_bstnode::_bstnode() {
    left = NULL;
    right = NULL;
    data = LONG_MAX;
}

_avlnode::_avlnode() {
    height=1;
}

_avlnode::~_avlnode() {
}

_bstnode::~_bstnode() {

}

long _bstnode::getdata() {
    return data;
}

int _bstnode::add_element(long element) {
    p_BSTnode cur = this;
    int ret = EC_success;
    while(1) {
        if(cur->data == LONG_MAX) {
            cur->data = element;
            break;
        }
        if(cur->data > element) {
            if(cur->left == NULL)
                cur->left = new _bstnode;
            cur=cur->left;
        }
        else if(cur->data < element) {
            if(cur->right == NULL)
                cur->right = new _bstnode;
            cur=cur->right;
        }
        else {
            ret=EC_dup;
            break;
        }
    }

    return ret;
}

void adjust_height(_avlnode *node) {
    node->height = 1;
    if(node->left && node->right)
        node->height+= std::max(static_cast<_avlnode *>(node->left)->height, static_cast<_avlnode*>(node->right)->height);
    else if(node->left)
        node->height+=static_cast<_avlnode*>(node->left)->height;
    else if(node->right)
        node->height+=static_cast<_avlnode*>(node->right)->height;
}

static void rotate_left(p_BSTnode node, p_BSTnode parent) {
    //cout<<"Left rotation required for node:"<<node->getdata()<<endl;
    p_BSTnode newchild = node->right;
    node->right= newchild->left;
    if(parent && parent->left == node) parent->left = newchild;
    else if(parent)parent->right = newchild;
    newchild->left = node;
    adjust_height(static_cast<_avlnode*>(node));
    adjust_height(static_cast<_avlnode*>(newchild));
}

static void rotate_right(p_BSTnode node, p_BSTnode parent) {
    //cout<<"Right rotation required for node:"<<node->getdata()<<endl;
    p_BSTnode newchild = node->left;
    node->left= newchild->right;
    if(parent && parent->left == node) parent->left = newchild;
    else if(parent) parent->right = newchild;
    newchild->right = node;
    adjust_height(static_cast<_avlnode*>(node));
    adjust_height(static_cast<_avlnode*>(newchild));
}

int balance_tree(stack<_avlnode*> stk, bool direction, _avlnode ** rootp) {
    _avlnode *pnode=NULL;
    while(stk.empty() == false) {
        _avlnode * node = stk.top();
        stk.pop();
        int lheight=0, rheight=0;
        if(node->left)
            lheight = static_cast<_avlnode*>(node->left)->height;
        if(node->right)
            rheight = static_cast<_avlnode*>(node->right)->height;
        int balance = lheight-rheight;
        if(balance>1) {
        //New node was added to left subtree
            cout<<"tree imbalance at ("<<node->getdata()<<") Need ";
            if(direction == RIGHT)  {//This is LR rotation
                cout<<"L";
                rotate_left(node->left, node);
            }
            cout<<"R rotation"<<endl;
            if(stk.empty() == false)
                pnode=stk.top();
            else {
                *rootp=static_cast<_avlnode*>(node->left);
            }
            rotate_right(node, pnode);
        }
        else if(balance<-1) {
        //New node was added to right subtree
            cout<<"tree imbalance at ("<<node->getdata()<<") Need ";
            if(direction == LEFT)   {//This is RL rotation
                cout<<"R";
                rotate_right(node->right, node);
            }
            cout<<"L rotation"<<endl;
            if(stk.empty() == false)
                pnode=stk.top();
            else {
                *rootp=static_cast<_avlnode*>(node->right);
            }
            rotate_left(node, pnode);
        }
        adjust_height(static_cast<_avlnode*>(node));
    }
    return EC_success;
}

int avl_add_element(_avlnode **rootp, long element) {
    int ret = EC_success;
    bool direction=LEFT;
    stack<_avlnode *> avlstk;
    _avlnode * root=*rootp;

    if(root->getdata() == LONG_MAX || element == root->getdata()) {
        root->setdata(element);
        return ret;
    }
    //avlstk.push(root);
    _avlnode * node = *rootp;
    bool parentnotfound = true;
    while(parentnotfound) {
        avlstk.push(node);
        if(node->getdata() == element) break;
        if(node->getdata() > element && node->left)
            node=static_cast<_avlnode*>(node->left);
        else if(node->getdata() > element) {
            parentnotfound=false;
            direction=LEFT;
            cout<<"Added ("<<element<<") to left of "<<node->getdata()<<endl;
            node->left = new _avlnode;
            node=static_cast<_avlnode*>(node->left);
            node->setdata(element);
        }
        else if(node->getdata() < element && node->right)
            node=static_cast<_avlnode*>(node->right);
        else {
            parentnotfound=false;
            direction=RIGHT;
            cout<<"Added ("<<element<<") to right of "<<node->getdata()<<endl;
            node->right = new _avlnode;
            node=static_cast<_avlnode*>(node->right);
            node->setdata(element);
        }
    }
    if(parentnotfound) {
        while(avlstk.empty() == false) avlstk.pop();
        return EC_success;
    }
    else {
        ret = balance_tree(avlstk, direction, rootp);
    }
    return ret;
}

int get_heightof_tree(p_BSTnode root) {
    int lheight=0, rheight=0, height=1;

    if(root == NULL) return 0;
    if(root->left == NULL && root->right == NULL) return 1;
    lheight = get_heightof_tree(root->left);
    rheight = get_heightof_tree(root->right);
    height+=(lheight > rheight) ? lheight : rheight;
    return height;
}

int buildBST_from_Arr(p_BSTnode root, long arr[], int sz) {
    int i =0;
    for(i=0; i<sz;i++)
        root->add_element(arr[i]);

    return get_heightof_tree(root);
}

int buildAVL_from_Arr(_avlnode **rootp, long arr[], int sz) {
    int i=0;
    for(i=0; i<sz;i++)
        avl_add_element(rootp, arr[i]);

    return get_heightof_tree(*rootp);
}

