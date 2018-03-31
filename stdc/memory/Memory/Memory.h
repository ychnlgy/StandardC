#ifndef STDC_MEMORY_MEMORY_MEMORY
#define STDC_MEMORY_MEMORY_MEMORY

#include "stdc/lib.h"

typedef struct Memory Memory;

Ptr new_Memory();

struct Memory {
    List super;

    void    (*track)    (Memory*, Ptr);
    Ptr     (*alloc)    (Memory*, size_t);
    Ptr     (*make)     (Memory*, Maker);
};

#endif
