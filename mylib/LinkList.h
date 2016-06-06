#ifndef __LINKLIST_H_
#define __LINKLIST_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct _llist {
    long data;
    struct _llist *next;
} LL;

typedef struct _dllist {
    long data;
    struct _dllist *next;
} DLL;

extern LL *get_llnode();
extern DLL *get_dllnode();

#endif
