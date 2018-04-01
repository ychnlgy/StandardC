#include "stdc/lib.h"
#include "List_protected.h"
#include "List_private.h"

#define MIN_CAPACITY 10
#define RESIZE_FACTOR 2
#define PTR_SIZE sizeof(Ptr)

// === HELPERS ===

void _List_resize(ListObject* this, size_t n) {
    Ptr* data = malloc(n*PTR_SIZE);
    long size = MIN(this->size, n);

    long i;
    for (i=0; i<size; i++)
        data[i] = this->data[i];
    for (i=size; i<n; i++)
        data[i] = NULL;

    free(this->data);

    this->size = size;
    this->capacity = n;
    this->data = data;
}

bool _List_isWithin(ListObject* this, long i) {
    return i < this->size && this->size != 0;
}

long _List_fitWithin(ListObject* this, long i) {
    return MOD(i, this->size);
}

// === METHODS ===

void del_List(Ptr ptr) {
    ListObject this = *((ListObject*) ptr);
    long i;
    for (i=0; i<this.size; i++)
       decref(this.data[i]);
    free(this.data);
}

Ptr new_List() {
    ListObject* this = new(sizeof(List), &del_List);
    init_List(this);
    return this;
}

void init_List(ListObject* this) {
    this->size     = 0;
    this->capacity = MIN_CAPACITY;
    this->data     = malloc(MIN_CAPACITY*PTR_SIZE);

    long i;
    for (i=0; i<MIN_CAPACITY; i++)
        this->data[i] = NULL;
}

void push_List(ListObject* this, Ptr entry) {
    if (this->size >= this->capacity)
       _List_resize(this, this->capacity*RESIZE_FACTOR);
    setitem_List(this, this->size++, entry);
}

Ptr pop_List(ListObject* this) {
    if (this->size <= 0)
        return NULL;
    Ptr out = this->data[this->size-1];
    this->data[--this->size] = NULL;
    return out;
}

long size_List(ListObject* this) {
    return this->size;
}

Ptr getitem_List(ListObject* this, long i) {
    return this->data[i];
}

void setitem_List(ListObject* this, long i, Ptr entry) {
    Ptr original = this->data[i];
    this->data[i] = entry;
    if (entry != NULL)
        incref(entry); 
    if (original != NULL)
        decref(original);
}

Ptr at_List(ListObject* this, long i) {
    if (_List_isWithin(this, i))
        return this->data[_List_fitWithin(this, i)];
    else
        return NULL;
}

bool set_List(ListObject* this, long i, Ptr entry) {
    if (_List_isWithin(this, i)) {
        setitem_List(this, _List_fitWithin(this, i), entry);
       return true;
    } else {
        return false;
    }
}

