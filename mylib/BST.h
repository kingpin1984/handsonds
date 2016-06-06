#ifndef __BST_H_
#define __BST_H_

#ifdef __cplusplus
extern "C" {
#endif
typedef struct _bst {
    long data;
    int dup_count;
    struct _bst *left;
    struct _bst *right;
} *BST;

extern BST get_BSTnode();
extern int buildBST_from_Arr(BST root, long arr[], int sz);
extern int add_element_to_BST(BST root, long element);
#ifdef __cplusplus
}
#endif

#endif
