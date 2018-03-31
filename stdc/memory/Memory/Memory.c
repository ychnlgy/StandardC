#include "stdc/lib.h"
#include "Memory_protected.h"

// === PUBLIC METHODS ===

void del_Memory(Ptr this) {
    List* scope = ((Memory*) this)->scope;
    long i;
    for (i=0; i<scope->size(scope); i++)
        decref(scope->getitem(scope, i));
    decref(scope);
}

void init_Memory(Memory* this) {
    this->scope = new_List();

    this->track     = &track_Memory;
    this->alloc     = &alloc_Memory;
    this->make      = &make_Memory;
}

void* new_Memory() {
    Memory* this = new(sizeof(Memory), &del_Memory);
    init_Memory(this);
    return this;
}

void track_Memory(Memory* this, Ptr ptr) {
    if (ptr != NULL)
        this->scope->push(this->scope, ptr);
}

Ptr alloc_Memory(Memory* this, size_t typesize) {
    Ptr ptr = new(typesize, NULL);
    track_Memory(this, ptr);
    return ptr;
}

Ptr make_Memory(Memory* this, Maker maker) {
    Ptr ptr = maker();
    track_Memory(this, ptr);
    return ptr;
}
