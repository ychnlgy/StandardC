#ifndef STDC_UTIL_LIST_LIST_PRIVATE
#define STDC_UTIL_LIST_LIST_PRIVATE

#include "stdc/lib.h"

struct ListObject {
    long size;
    long capacity;
    Ptr* data;
};

Ptr     new_List        ();
void    init_List       (ListObject*);
void    del_List        (Ptr);

// Getters
long    size_List       (ListObject*);

// Modifiers
void    push_List       (ListObject*, Ptr);
Ptr     pop_List        (ListObject*);

// Fast but unsafe operations (does not check range).
Ptr     getitem_List    (ListObject*, long);
void    setitem_List    (ListObject*, long, Ptr);

// Slow but safe operations.(checks range).
Ptr     at_List         (ListObject*, long);
bool    set_List        (ListObject*, long, Ptr);

ListVtable List = {

    // Construction/destruction
    .new        = &new_List,
    .init       = &init_List,
    .del        = &del_List,
    
    // Methods
    .size       = &size_List,
    .push       = &push_List,
    .pop        = &pop_List,
    .getitem    = &getitem_List,
    .setitem    = &setitem_List,
    .at         = &at_List,
    .set        = &set_List
};

#endif
