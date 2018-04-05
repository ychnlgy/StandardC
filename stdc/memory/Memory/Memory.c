#include "private.h"

MemoryVtable Memory = {

    // Construction/destruction
    .new   = &new_Memory,
    .init  = &init_Memory,
    .del   = &del_Memory,
    
    // Methods
    .track = &track_Memory,
    .alloc = &alloc_Memory,
    .make  = &make_Memory

};

// Object
static Ptr new_Memory() {
    MemoryObject* this = new(sizeof(Memory), &del_Memory);
    init_Memory(this);
    return this;
}

static void init_Memory(MemoryObject* this) {
    this->scope = List.new();
}

static void del_Memory(Ptr this) {
    ListObject* scope = ((MemoryObject*) this)->scope;
    long i;
    for (i=0; i<List.size(scope); i++)
        decref(List.getitem(scope, i));
    decref(scope);
}

// Memory
static void track_Memory(MemoryObject* this, Ptr ptr) {
    if (ptr != NULL)
        List.push(this->scope, ptr);
}

static Ptr alloc_Memory(MemoryObject* this, size_t typesize) {
    Ptr ptr = new(typesize, NULL);
    track_Memory(this, ptr);
    return ptr;
}

static Ptr make_Memory(MemoryObject* this, Maker maker) {
    Ptr ptr = maker();
    track_Memory(this, ptr);
    return ptr;
}
