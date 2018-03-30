#include "Memory.h"
#include "Memory_protected.h"

#include "gc.h"

#include <stdlib.h> 
// malloc

// === PUBLIC METHODS ===

void del_Memory(void* ptr) {
    Memory* this = ptr;
    this->fields->arr->foreach(this->fields->arr, &decref);
    del(&this->fields->arr);
    free(this->fields);
}

void* new_Memory() {
    Memory* this = new(sizeof(Memory), &del_Memory);
    this->fields = malloc(sizeof(MemoryFields));
    this->fields->arr = new_List();
    this->fields->arr->constructors->init(this->fields->arr, sizeof(void*));
    
    this->track = &track_Memory;
    this->alloc = &alloc_Memory;
    this->make  = &make_Memory;
    return this;
}

void track_Memory(void* _this, void* ptr) {
    if (ptr != NULL) {
        Memory* this = _this;
        this->fields->arr->push(this->fields->arr, ptr);
    }
}

void* alloc_Memory(void* this, int typesize) {
    void* out = new(typesize, &destroy_nothing);
    track_Memory(this, &out);
    return out;
}

void* make_Memory(void* this, void*(*maker)()) {
    void* out = maker();
    track_Memory(this, &out);
    return out;
}
