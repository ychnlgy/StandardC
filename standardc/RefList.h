#ifndef STANDARDC_REFLIST
#define STANDARDC_REFLIST

#include "List.h"

void* new_RefList();

typedef struct RefList RefList;

struct RefList {
    ListFields* fields;
    
    // Getters
    int     (*len)          (RefList*);
    
    // Modifiers
    void    (*push)         (RefList*, void*);
    void*   (*pop)          (RefList*);
    
    // Fast but unsafe accessors (does not check range)
    void*   (*getitem)      (RefList*, int);
    void    (*setitem)      (RefList*, int, void*);
    
    // Slow but safe accessors (checks for range)
    void*   (*at)           (RefList*, int);
    bool    (*set)          (RefList*, int, void*);
    
    // Iteration
    void    (*foreach)      (RefList*, void(*)(void*));
    
};

#endif
