#ifndef STDC_MEMORY_MEMORY_PRIVATE_MEMORY
#define STDC_MEMORY_MEMORY_PRIVATE_MEMORY

#include "private.h"

void    track_Memory    (MemoryObject*, Ptr);
Ptr     alloc_Memory    (MemoryObject*, size_t);
Ptr     make_Memory     (MemoryObject*, Maker);

#endif
