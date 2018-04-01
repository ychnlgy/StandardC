// Interface: inherits Object

#ifndef STDC_UTIL_INTERFACES_ACCESSOR
#define STDC_UTIL_INTERFACES_ACCESSOR

#include "stdc/lib.h"

typedef struct Accessor Accessor;

typedef struct {
    ObjectVtable super;
    
    long    (*size)     (Accessor*);
    
    // Fast but unsafe accessors (does not check range)
    Ptr     (*getitem)  (Accessor*, long);
    void    (*setitem)  (Accessor*, long, Ptr);

    // Slow but safe accessors (checks for range)
    Ptr     (*at)       (Accessor*, long);
    bool    (*set)      (Accessor*, long, Ptr);
} AccessorVtable;

struct Accessor {
    AccessorVtable* _;
};

#endif
