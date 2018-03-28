#include "List.h"
#include "List_protected.h"

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

void resize_List(ListFields* this, int n) {
    char* data = malloc(n*this->typesize);
    int len = min(this->len, n);
    int i;
    for (i=0; i<len*this->typesize; i++)
        data[i] = this->data[i];
    free(this->data);
    this->len = len;
    this->capacity = n;
    this->data = data;
}

void checkInited(ListFields* this) {
    if (this->inited)
        free(this->data);
    this->inited = 1;
}

void setup_List(ListFields* this, int typesize, int len) {
    checkInited(this);
    this->typesize = typesize;
    this->len = len;
    this->capacity = max(len, MIN_CAPACITY);
    this->data = malloc(this->capacity*typesize);
}

// === PUBLIC METHODS ===

void del_List(void* ptr) {
    List* this = ptr;
    if (this->fields->inited)
        free(this->fields->data);
    free(this->fields);
}

void* new_List() {
    List* this = new(sizeof(List), &del_List);
    this->fields = malloc(sizeof(ListFields));
    this->fields->inited = 0;
    
    this->init      = &init_List;
    this->initall   = &initall_List;
    this->initarray = &initarray_List;
    this->len       = &len_List;
    this->push      = &push_List;
    this->pop       = &pop_List;
    this->getitem   = &getitem_List;
    this->setitem   = &setitem_List;
    this->at        = &at_List;
    this->set       = &set_List;
    this->foreach   = &foreach_List;
    
    return this;
}

void init_List(List* this, int typesize) {
    setup_List(this->fields, typesize, 0);
}

void initall_List(List* this, int typesize, int len, void* value) {
    setup_List(this->fields, typesize, len);
    char* data = (char*) value;
    int j;
    for (j=0; j<len; j++) {
        int i;
        for (i=0; i<typesize; i++)
            this->fields->data[j*typesize+i] = data[i];
    }
}

void initarray_List(List* this, int typesize, int len, void* arr) {
    setup_List(this->fields, typesize, len);
    char* data = (char*) arr;
    int i;
    for (i=0; i<typesize*len; i++)
        this->fields->data[i] = data[i];
}

void push_List(List* this, void* entry) {
    assert(this->fields->len <= this->fields->capacity);
    if (this->fields->len == this->fields->capacity)
        resize_List(this->fields, this->fields->capacity*RESIZE_FACTOR);
    setitem_List(this, this->fields->len++, entry);
}

void* pop_List(List* this) {
    if (this->fields->len == 0)
        return NULL;
    return getitem_List(this, --this->fields->len);
}

int len_List(List* this) {
    return this->fields->len;
}

void* getitem_List(List* this, int i) {
    return this->fields->data+i*this->fields->typesize;
}

void setitem_List(List* this, int j, void* entry) {
    char* data = (char*) entry;
    int start = j*this->fields->typesize;
    int i;
    for (i=0; i<this->fields->typesize; i++)
        this->fields->data[start+i] = data[i];
}

int isWithinArray(List* this, int i) {
    return i < this->fields->len && i >= 0;
}

void* at_List(List* this, int i) {
    if (isWithinArray(this, i))
        return getitem_List(this, i);
    else
        return NULL;
}

bool set_List(List* this, int i, void* entry) {
    if (isWithinArray(this, i)) {
        setitem_List(this, i, entry);
        return true;
    } else {
        return false;
    }
}

void foreach_List(List* this, void(*fn)(void*)) {
    int i;
    for (i=0; i<this->fields->len; i++)
        fn(getitem_List(this, i));
}

