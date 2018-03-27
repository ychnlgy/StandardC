#include "Memory.h"
#include "ArrayList.h"

#include <stdlib.h> 
// malloc

// === PRIVATE METHODS ===

void free_ptr(void* ptr) {
    decref(*((void**) ptr));
}

// === PUBLIC METHODS ===

struct Memory {
    ArrayList* arr;
};

Memory* new_Memory() {
    Memory* this = malloc(sizeof(Memory));
    this->arr = new_ArrayList();
    init_ArrayList(this->arr, sizeof(void*));
    return this;
}

void free_Memory(Memory* this) {
    foreach_ArrayList(this->arr, &free_ptr);
    del(this->arr);
    free(this);
}

void track_Memory(Memory* this, void* ptr) {
    push_ArrayList(this->arr, ptr);
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
