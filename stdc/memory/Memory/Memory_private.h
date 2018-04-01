#ifndef STDC_MEMORY_MEMORY_MEMORY_PRIVATE
#define STDC_MEMORY_MEMORY_MEMORY_PRIVATE

#include "stdc/lib.h"

struct MemoryObject {
    ListObject* scope;
};

Ptr     new_Memory      ();
void    del_Memory      (Ptr);
void    init_Memory     (MemoryObject*);
void    track_Memory    (MemoryObject*, Ptr);
Ptr     alloc_Memory    (MemoryObject*, size_t);
Ptr     make_Memory     (MemoryObject*, Maker);

MemoryVtable Memory = {

    // Construction/destruction
    .new   = &new_Memory,
    .init  = &init_Memory,
    .del   = &del_Memory,
    
    // Methods
    .track = &track_Memory,
    .alloc = &alloc_Memory,
    .make  = &make_Memory
};

#endif
