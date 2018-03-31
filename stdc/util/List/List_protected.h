#ifndef STDC_UTIL_LIST_LIST_PROTECTED
#define STDC_UTIL_LIST_LIST_PROTECTED

#include "stdc/lib.h"

void    init_List       (List*);
void    del_List        (Ptr);

// Getters
long    size_List       (List*);

// Modifiers
void    push_List       (List*, Ptr);
Ptr     pop_List        (List*);

// Fast but unsafe operations (does not check range).
Ptr     getitem_List    (List*, long);
void    setitem_List    (List*, long, Ptr);

// Slow but safe operations.(checks range).
Ptr     at_List         (List*, long);
bool    set_List        (List*, long, Ptr);

#endif
