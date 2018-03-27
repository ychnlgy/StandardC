#include "ArrayList.h"
#include "gc.h"
#include "algorithm.h"

#include <stdlib.h> 
// malloc

#include <stddef.h> 
// NULL

#include <assert.h>

#define MIN_CAPACITY 16
#define RESIZE_FACTOR 2

// === PRIVATE METHODS ===

struct ArrayList {
    int typesize;
    int len;
    int capacity;
    char* data;
};

void del_ArrayList(void* this) {
    free(((ArrayList*) this)->data);
}

void resize_ArrayList(ArrayList* this, int n) {
    char* data = malloc(n*this->typesize);
    int len = min(this->len, n);
    for (int i=0; i<len*this->typesize; i++)
        data[i] = this->data[i];
    free(this->data);
    this->len = len;
    this->capacity = n;
    this->data = data;
}

void setup_ArrayList(ArrayList* this, int typesize, int len) {
    this->typesize = typesize;
    this->len = len;
    this->capacity = max(len, MIN_CAPACITY);
    this->data = malloc(this->capacity*typesize);
}

// === PUBLIC METHODS ===

void* new_ArrayList() {
    return new(sizeof(ArrayList), &del_ArrayList);
}

void init_ArrayList(ArrayList* this, int typesize) {
    setup_ArrayList(this, typesize, 0);
}

void initall_ArrayList(ArrayList* this, int typesize, int len, void* value) {
    setup_ArrayList(this, typesize, len);
    char* data = (char*) value;
    for (int j=0; j<len; j++)
        for (int i=0; i<typesize; i++)
            this->data[j*typesize+i] = data[i];
}

void initarray_ArrayList(ArrayList* this, int typesize, int len, void* arr) {
    setup_ArrayList(this, typesize, len);
    char* data = (char*) arr;
    for (int i=0; i<typesize*len; i++)
        this->data[i] = data[i];
}

void push_ArrayList(ArrayList* this, void* entry) {
    assert(this->len <= this->capacity);
    if (this->len == this->capacity)
        resize_ArrayList(this, this->capacity*RESIZE_FACTOR);
    setitem_ArrayList(this, this->len++, entry);
}

void* pop_ArrayList(ArrayList* this) {
    if (this->len == 0)
        return NULL;
    return getitem_ArrayList(this, --this->len);
}

int len_ArrayList(ArrayList* this) {
    return this->len;
}

void* getitem_ArrayList(ArrayList* this, int i) {
    return this->data+i*this->typesize;
}

void setitem_ArrayList(ArrayList* this, int i, void* entry) {
    assert(i < this->len);
    char* data = (char*) entry;
    int start = i*this->typesize;
    for (int i=0; i<this->typesize; i++)
        this->data[start+i] = data[i];
}

void* at_ArrayList(ArrayList* this, int i) {
    if (i < this->len)
        return getitem_ArrayList(this, i);
    else
        return NULL;
}

void foreach_ArrayList(ArrayList* this, void(*fn)(void*)) {
    for (int i=0; i<this->len; i++)
        fn(getitem_ArrayList(this, i));
}

