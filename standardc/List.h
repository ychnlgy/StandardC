#ifndef STANDARDC_LIST
#define STANDARDC_LIST

#include "bool.h"

void* new_List();

typedef struct ListFields ListFields;

typedef struct ListConstructors {
    void    (*init)         (void*, int);
    void    (*initall)      (void*, int, int, void*);
    void    (*initarray)    (void*, int, int, void*);
} ListConstructors;

typedef struct List {
    ListFields* fields;
    ListConstructors* constructors;
    
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
    
} List;

#endif
