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

// Init
void init_ArrayList(ArrayList* this, int typesize);
void initall_ArrayList(ArrayList* this, int typesize, int len, void* value);
void initarray_ArrayList(ArrayList* this, int typesize, int len, void* array);

// Getters
int len_ArrayList(ArrayList* this);

// Modifiers
void push_ArrayList(ArrayList* this, void* item);
void* pop_ArrayList(ArrayList* this);

// Fast but unsafe operations (does not check range).
void* getitem_ArrayList(ArrayList* this, int i);
void setitem_ArrayList(ArrayList* this, int i, void* item);

// Slow but safe operations.(checks range).
void* at_ArrayList(ArrayList* this, int i);
void set_ArrayList(ArrayList* this, int i, void* item);

// Iteration
void foreach_ArrayList(ArrayList* this, void(*fn)(void*));
//ArrayList* map_ArrayList(ArrayList*

// === PRIVATE METHODS ===

struct ArrayListFields {
    int inited;
    int typesize;
    int len;
    int capacity;
    char* data;
};

void del_ArrayList(void* ptr) {
    ArrayList* this = ptr;
    if (this->fields->inited)
        free(this->fields->data);
    free(this->fields);
}

void resize_ArrayList(ArrayListFields* this, int n) {
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

void checkInited(ArrayListFields* this) {
    if (this->inited)
        free(this->data);
    this->inited = 1;
}

void setup_ArrayList(ArrayListFields* this, int typesize, int len) {
    checkInited(this);
    this->typesize = typesize;
    this->len = len;
    this->capacity = max(len, MIN_CAPACITY);
    this->data = malloc(this->capacity*typesize);
}

// === PUBLIC METHODS ===

void* new_ArrayList() {
    ArrayList* this = new(sizeof(ArrayList), &del_ArrayList);
    this->fields = malloc(sizeof(ArrayListFields));
    this->fields->inited = 0;
    
    this->init      = &init_ArrayList;
    this->initall   = &initall_ArrayList;
    this->initarray = &initarray_ArrayList;
    this->len       = &len_ArrayList;
    this->push      = &push_ArrayList;
    this->pop       = &pop_ArrayList;
    this->getitem   = &getitem_ArrayList;
    this->setitem   = &setitem_ArrayList;
    this->at        = &at_ArrayList;
    this->foreach   = &foreach_ArrayList;
    
    return this;
}

void init_ArrayList(ArrayList* this, int typesize) {
    setup_ArrayList(this->fields, typesize, 0);
}

void initall_ArrayList(ArrayList* this, int typesize, int len, void* value) {
    setup_ArrayList(this->fields, typesize, len);
    char* data = (char*) value;
    int j;
    for (j=0; j<len; j++) {
        int i;
        for (i=0; i<typesize; i++)
            this->fields->data[j*typesize+i] = data[i];
    }
}

void initarray_ArrayList(ArrayList* this, int typesize, int len, void* arr) {
    setup_ArrayList(this->fields, typesize, len);
    char* data = (char*) arr;
    int i;
    for (i=0; i<typesize*len; i++)
        this->fields->data[i] = data[i];
}

void push_ArrayList(ArrayList* this, void* entry) {
    assert(this->fields->len <= this->fields->capacity);
    if (this->fields->len == this->fields->capacity)
        resize_ArrayList(this->fields, this->fields->capacity*RESIZE_FACTOR);
    setitem_ArrayList(this, this->fields->len++, entry);
}

void* pop_ArrayList(ArrayList* this) {
    if (this->fields->len == 0)
        return NULL;
    return getitem_ArrayList(this, --this->fields->len);
}

int len_ArrayList(ArrayList* this) {
    return this->fields->len;
}

void* getitem_ArrayList(ArrayList* this, int i) {
    return this->fields->data+i*this->fields->typesize;
}

void setitem_ArrayList(ArrayList* this, int j, void* entry) {
    assert(j < this->fields->len);
    char* data = (char*) entry;
    int start = j*this->fields->typesize;
    int i;
    for (i=0; i<this->fields->typesize; i++)
        this->fields->data[start+i] = data[i];
}

void* at_ArrayList(ArrayList* this, int i) {
    if (i < this->fields->len && i >= 0)
        return getitem_ArrayList(this, i);
    else
        return NULL;
}

void foreach_ArrayList(ArrayList* this, void(*fn)(void*)) {
    int i;
    for (i=0; i<this->fields->len; i++)
        fn(getitem_ArrayList(this, i));
}

