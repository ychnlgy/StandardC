#include "private.h"

Ptr new_Memory() {
    MemoryObject* this = new(sizeof(Memory), &del_Memory);
    init_Memory(this);
    return this;
}

void init_Memory(MemoryObject* this) {
    this->scope = List.new();
}

void del_Memory(Ptr this) {
    ListObject* scope = ((MemoryObject*) this)->scope;
    long i;
    for (i=0; i<List.size(scope); i++)
        decref(List.getitem(scope, i));
    decref(scope);
}
