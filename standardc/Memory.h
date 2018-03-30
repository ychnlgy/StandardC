#ifndef STANDARDC_MEMORY
#define STANDARDC_MEMORY

typedef struct MemoryFields MemoryFields;

void* new_Memory();

typedef struct Memory {
    MemoryFields* fields;
    
    void    (*track)    (void*, void*);
    void*   (*alloc)    (void*, int);
    void*   (*make)     (void*, void*(*)());
} Memory;

#endif
