#include "stdc/lib.h"
#include "Memory_private.h"

void del_Memory(Ptr this) {
    ListObject* scope = ((MemoryObject*) this)->scope;
    long i;
    for (i=0; i<List.size(scope); i++)
        decref(List.getitem(scope, i));
    decref(scope);
}

void init_Memory(MemoryObject* this) {
    this->scope = List.new();
}

void* new_Memory() {
    MemoryObject* this = new(sizeof(Memory), &del_Memory);
    init_Memory(this);
    return this;
}

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
