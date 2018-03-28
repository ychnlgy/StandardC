#ifndef STANDARDC_REFLIST
#define STANDARDC_REFLIST

#include "List.h"

void* new_RefList();

typedef struct RefList {
    ListFields* fields;
    ListVtable* vtable;
    
    // Getters
    int     (*len)          (void*);
    
    // Modifiers
    void    (*push)         (void*, void*);
    void*   (*pop)          (void*);
    
    // Fast but unsafe accessors (does not check range)
    void*   (*getitem)      (void*, int);
    void    (*setitem)      (void*, int, void*);
    
    // Slow but safe accessors (checks for range)
    void*   (*at)           (void*, int);
    bool    (*set)          (void*, int, void*);
    
    // Iteration
    void    (*foreach)      (void*, void(*)(void*));
    
} RefList;

#endif
