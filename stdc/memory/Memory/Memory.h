#ifndef STDC_MEMORY_MEMORY_MEMORY
#define STDC_MEMORY_MEMORY_MEMORY

#include "stdc/lib.h"

typedef struct MemoryObject MemoryObject;

typedef struct {

    // Construction/destruction
    Ptr     (*new)      ();
    void    (*init)     (MemoryObject*);
    void    (*del)      (Ptr);
    
    // Methods
    void    (*track)    (MemoryObject*, Ptr);
    Ptr     (*alloc)    (MemoryObject*, size_t);
    Ptr     (*make)     (MemoryObject*, Maker);

} MemoryVtable;

extern MemoryVtable Memory;

#endif
