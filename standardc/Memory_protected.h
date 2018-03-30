#ifndef STANDARDC_MEMORY_PROTECTED
#define STANDARDC_MEMORY_PROTECTED

#include "List.h"
#include "Memory.h"

struct MemoryFields {
    List* arr;
};

void track_Memory(void* this, void* ptr);
void* alloc_Memory(void* this, int typesize);
void* make_Memory(void* this, void*(*maker)());

#endif
