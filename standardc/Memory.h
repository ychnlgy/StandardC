#ifndef STANDARDC_MEMORY
#define STANDARDC_MEMORY

typedef struct MemoryFields MemoryFields;
typedef struct MemoryVtable MemoryVtable;

void* new_Memory();

typedef struct Memory {
    MemoryFields* fields;
    MemoryVtable* vtable;
    
    void    (*track)    (void*, void*);
    void*   (*alloc)    (void*, int);
    void*   (*make)     (void*, void*(*)());
} Memory;

#endif
