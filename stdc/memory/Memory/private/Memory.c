#include "private.h"

void track_Memory(MemoryObject* this, Ptr ptr) {
    if (ptr != NULL)
        List.push(this->scope, ptr);
}

Ptr alloc_Memory(MemoryObject* this, size_t typesize) {
    Ptr ptr = new(typesize, NULL);
    track_Memory(this, ptr);
    return ptr;
}

Ptr make_Memory(MemoryObject* this, Maker maker) {
    Ptr ptr = maker();
    track_Memory(this, ptr);
    return ptr;
}
