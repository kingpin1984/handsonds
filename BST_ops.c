#include "BST.h"
#include <stdio.h>

void traverse_tree(BST node) {
    if(node->left) traverse_tree(node->left);
    if(node->right) traverse_tree(node->right);
    if(node->left == NULL && node->right == NULL)
        printf("L%ld\n", node->data);
    else
        printf("%ld\n", node->data);
}
int main() {

    long arr[10] = {300, 600, 150, 450, 50, 700, 200, 500, 75, 100};
    int height =0;
    BST head = get_BSTnode();
    if(head == NULL) {
        perror("malloc");
    }
    height = buildBST_from_Arr(head, arr, 10);
    printf("height of tree: %d\n", height);
    
    traverse_tree(head);
    return 0;
}
