#ifndef STANDARDC_LIST
#define STANDARDC_LIST

#include "bool.h"

void* new_List();

typedef struct ListFields ListFields;
typedef struct List List;

struct List {
    ListFields* fields;
    
    // Init
    void    (*init)         (List*, int);
    void    (*initall)      (List*, int, int, void*);
    void    (*initarray)    (List*, int, int, void*);
    
    // Getters
    int     (*len)          (List*);
    
    // Modifiers
    void    (*push)         (List*, void*);
    void*   (*pop)          (List*);
    
    // Fast but unsafe accessors (does not check range)
    void*   (*getitem)      (List*, int);
    void    (*setitem)      (List*, int, void*);
    
    // Slow but safe accessors (checks for range)
    void*   (*at)           (List*, int);
    bool    (*set)          (List*, int, void*);
    
    // Iteration
    void    (*foreach)      (List*, void(*)(void*));
    
};

#endif
