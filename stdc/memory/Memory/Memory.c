#include "stdc/lib.h"
#include "Memory_protected.h"

// === PUBLIC METHODS ===

void del_Memory(Ptr this) {
    List* _scope = ((Memory*) this)->_scope;
    long i;
    for (i=0; i<_scope->_->size(_scope); i++)
        decref(_scope->_->getitem(_scope, i));
    decref(_scope);
}

void init_Memory(Memory* this) {
    this->_      = &MEMORY_VTABLE;
    this->_scope = new_List();
}

void* new_Memory() {
    Memory* this = new(sizeof(Memory), &del_Memory);
    init_Memory(this);
    return this;
}

void track_Memory(Memory* this, Ptr ptr) {
    if (ptr != NULL)
        this->_scope->_->push(this->_scope, ptr);
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
