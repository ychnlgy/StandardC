#include "stdc/lib.h"
#include "List_protected.h"

#define MIN_CAPACITY 10
#define RESIZE_FACTOR 2
#define PTR_SIZE sizeof(Ptr)

// === HELPERS ===

void _resize_List(List* this, size_t n) {
    Ptr* data = malloc(n*PTR_SIZE);
    long size = MIN(this->_size, n);

    long i;
    for (i=0; i<size; i++)
        data[i] = this->_data[i];
    for (i=size; i<n; i++)
        data[i] = NULL;

    free(this->_data);

    this->_size = size;
    this->_capacity = n;
    this->_data = data;
}

bool _isWithinList(List* this, long i) {
    return i < this->_size && this->_size != 0;
}

long _fitWithinList(List* this, long i) {
    return MOD(i, this->_size);
}

// === METHODS ===

void del_List(Ptr ptr) {
    List this = *((List*) ptr);
    long i;
    for (i=0; i<this._size; i++)
       decref(this._data[i]);
    free(this._data);
}

Ptr new_List() {
    List* this = new(sizeof(List), &del_List);
    init_List(this);
    return this;
}

void init_List(List* this) {
    this->_size = 0;
    this->_capacity = MIN_CAPACITY;
    this->_data = malloc(MIN_CAPACITY*PTR_SIZE);

    long i;
    for (i=0; i<MIN_CAPACITY; i++)
        this->_data[i] = NULL;

    this->size      = &size_List;
    this->push      = &push_List;
    this->pop       = &pop_List;
    this->getitem   = &getitem_List;
    this->setitem   = &setitem_List;
    this->at        = &at_List;
    this->set       = &set_List;
}

void push_List(List* this, Ptr entry) {
    if (this->_size >= this->_capacity)
       _resize_List(this, this->_capacity*RESIZE_FACTOR);
    setitem_List(this, this->_size++, entry);
}

Ptr pop_List(List* this) {
    if (this->_size <= 0)
        return NULL;
    Ptr out = this->_data[this->_size-1];
    this->_data[--this->_size] = NULL;
    return out;
}

long size_List(List* this) {
    return this->_size;
}

Ptr getitem_List(List* this, long i) {
    return this->_data[i];
}

void setitem_List(List* this, long i, Ptr entry) {
    Ptr original = this->_data[i];
    this->_data[i] = entry;
    if (entry != NULL)
        incref(entry); 
    if (original != NULL)
        decref(original);
}

Ptr at_List(List* this, long i) {
    if (_isWithinList(this, i))
        return this->_data[_fitWithinList(this, i)];
    else
        return NULL;
}

bool set_List(List* this, long i, Ptr entry) {
    if (_isWithinList(this, i)) {
        setitem_List(this, _fitWithinList(this, i), entry);
       return true;
    } else {
        return false;
    }
}

