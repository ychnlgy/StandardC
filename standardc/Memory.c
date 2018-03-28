#include "Memory.h"
#include "List.h"

#include <stdlib.h> 
// malloc

void track_Memory(Memory* this, void* ptr);
void* alloc_Memory(Memory* this, int typesize, Destructor destructor);
void* make_Memory(Memory* this, void*(*maker)());

// === PRIVATE METHODS ===

void free_ptr(void* ptrptr) {
    decref(ptrptr);
}

// === PUBLIC METHODS ===

struct MemoryFields {
    List* arr;
};

void del_Memory(void* ptr) {
    Memory* this = ptr;
    this->fields->arr->foreach(this->fields->arr, &free_ptr);
    del(&this->fields->arr);
    free(this->fields);
}

void* new_Memory() {
    Memory* this = new(sizeof(Memory), &del_Memory);
    this->fields = malloc(sizeof(MemoryFields));
    this->fields->arr = new_List();
    this->fields->arr->init(this->fields->arr, sizeof(void*));
    
    this->track = &track_Memory;
    this->alloc = &alloc_Memory;
    this->make  = &make_Memory;
    return this;
}

void track_Memory(Memory* this, void* ptr) {
    this->fields->arr->push(this->fields->arr, ptr);
}

void* alloc_Memory(Memory* this, int typesize, Destructor destructor) {
    void* out = new(typesize, destructor);
    track_Memory(this, &out);
    return out;
}

void* make_Memory(Memory* this, void*(*maker)()) {
    void* out = maker();
    track_Memory(this, &out);
    return out;
}
