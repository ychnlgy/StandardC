#ifndef STANDARD_MEMORY
#define STANDARD_MEMORY

#include "gc.h"

typedef struct Memory Memory;
typedef struct MemoryFields MemoryFields;

void* new_Memory();

struct Memory {
    MemoryFields* fields;
    
    void    (*track)    (Memory*, void*);
    void*   (*alloc)    (Memory*, int, Destructor);
    void*   (*make)     (Memory*, void*(*)());
};

#endif
