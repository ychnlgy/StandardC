#ifndef STDC_UTIL_LIST_PRIVATE_ACCESSOR
#define STDC_UTIL_LIST_PRIVATE_ACCESSOR

#include "private.h"

Ptr         getitem_List    (ListObject*, long);
void        setitem_List    (ListObject*, long, Ptr);
Ptr         at_List         (ListObject*, long);
bool        set_List        (ListObject*, long, Ptr);
ListObject* slice_List      (ListObject*, MemoryObject*, long, long);

#endif
