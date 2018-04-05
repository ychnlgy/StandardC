#ifndef STDC_MEMORY_MEMORY_PRIVATE
#define STDC_MEMORY_MEMORY_PRIVATE

#include "protected.h"

// Object
static Ptr     new_Memory      ();
static void    del_Memory      (Ptr);
static void    init_Memory     (MemoryObject*);

// Memory
static void    track_Memory    (MemoryObject*, Ptr);
static Ptr     alloc_Memory    (MemoryObject*, size_t);
static Ptr     make_Memory     (MemoryObject*, Maker);

#endif
