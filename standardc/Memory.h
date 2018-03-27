#ifndef STANDARD_MEMORY
#define STANDARD_MEMORY

#include "gc.h"

typedef struct Memory Memory;

Memory* new_Memory();
void free_Memory(Memory* this);

// methods
void track_Memory(Memory* this, void* ptr);
void* alloc_Memory(Memory* this, int typesize, Destructor destructor);
void* make_Memory(Memory* this, void*(*maker)());

#endif
