#include <stdio.h>
#include "LinkList.h"

LL *get_llnode() {
    LL *node = (LL *)malloc(sizeof(LL));
    node->next = NULL;
    return node;
}

DLL *get_dllnode() {
    DLL *node = (DLL *)malloc(sizeof(DLL));
    node->next = NULL;
    return node;
}

