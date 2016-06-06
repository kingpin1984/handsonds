#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "BST.h"

BST get_BSTnode() {
    BST node = (BST)malloc(sizeof(struct _bst));
    node->left = NULL;
    node->right = NULL;
    node->data = LONG_MAX;
    node->dup_count = 0;
    return node;
}

int add_element_to_BST(BST root, long element) {
    BST cur = root;
    while(1) {
        if(cur->data == LONG_MAX) {
            cur->data = element;
            break;
        }
        if(cur->data > element) {
            if(cur->left == NULL)
                cur->left = get_BSTnode();
            cur=cur->left;
        }
        else if(cur->data < element) {
            if(cur->right == NULL)
                cur->right = get_BSTnode();
            cur=cur->right;
        }
        else {
            cur->dup_count++;
            break;
        }
    }

    return 1;
}

int get_heightof_subtree(BST root) {
    int lheight=0, rheight=0, height=1;

    if(root == NULL) return 0;
    if(root->left == NULL && root->right == NULL) return 1;
    lheight = get_heightof_subtree(root->left);
    rheight = get_heightof_subtree(root->right);
    height+=(lheight > rheight) ? lheight : rheight;
    return height;
}

int buildBST_from_Arr(BST root, long arr[], int sz) {
    int i =0;
    for(i=0; i<sz;i++)
        add_element_to_BST(root, arr[i]);

    return get_heightof_subtree(root);
}

