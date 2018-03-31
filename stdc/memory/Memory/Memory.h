#ifndef STDC_MEMORY_MEMORY_MEMORY
#define STDC_MEMORY_MEMORY_MEMORY

#include "stdc/lib.h"

Ptr new_Memory();
typedef struct Memory Memory;

typedef struct {
    void    (*track)    (Memory*, Ptr);
    Ptr     (*alloc)    (Memory*, size_t);
    Ptr     (*make)     (Memory*, Maker);
} MemoryVtable;

struct Memory {
    MemoryVtable*   _;
    List*           _scope;
};

#endif
