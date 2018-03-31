#ifndef STDC_MEMORY_MEMORY_MEMORY_PROTECTED
#define STDC_MEMORY_MEMORY_MEMORY_PROTECTED

#include "stdc/lib.h"

void    del_Memory      (Ptr);
void    init_Memory     (Memory*);
void    track_Memory    (Memory*, Ptr);
Ptr     alloc_Memory    (Memory*, size_t);
Ptr     make_Memory     (Memory*, Maker);

static MemoryVtable MEMORY_VTABLE = {
    .track = &track_Memory,
    .alloc = &alloc_Memory,
    .make  = &make_Memory
};

#endif
