#ifndef STDC_UTIL_LIST_LIST_PRIVATE_STACK
#define STDC_UTIL_LIST_LIST_PRIVATE_STACK

#include "private.h"

void        push_List       (ListObject*, Ptr);
void        pushes_List     (ListObject*, long, ...);
Ptr         pop_List        (ListObject*, MemoryObject*);
Ptr         back_List       (ListObject*);
void        extend_List     (ListObject*, ListObject*);

#endif
