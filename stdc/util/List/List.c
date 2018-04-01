#include <stdarg.h>
// va_arg, va_start, va_end, va_list

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

// Construction/destruction

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

void del_List(Ptr ptr) {
    ListObject this = *((ListObject*) ptr);
    long i;
    for (i=0; i<this.size; i++)
       decref(this.data[i]);
    free(this.data);
}

// Methods

ListObject* concat_List(ListObject* this, ListObject* other) {
    ListObject* newl = new_List();
    List.extend(newl, this);
    List.extend(newl, other);
    return newl;
}

// Object interface

bool equals_List(ListObject* this, ListObject* other) {
    if (this->size != other->size)
        return false;
    
    long i;
    for (i=0; i<this->size; i++)
        if (this->data[i] != other->data[i])
            return false;
    return true;
}

// Container interface

long size_List(ListObject* this) {
    return this->size;
}

void clear_List(ListObject* this) {
    del_List(this);
    init_List(this);
}

// Stack interface

void push_List(ListObject* this, Ptr entry) {
    if (this->size >= this->capacity)
       _List_resize(this, this->capacity*RESIZE_FACTOR);
    if (entry != NULL)
        incref(entry);
    this->data[this->size++] = entry;
}

void pushes_List(ListObject* this, long n, ...) {
    va_list args;
    va_start(args, n);
    
    while (n-- > 0)
        push_List(this, va_arg(args, Ptr));
    
    va_end(args);
}

Ptr pop_List(ListObject* this) {
    if (this->size <= 0)
        return NULL;
    Ptr out = this->data[this->size-1];
    this->data[--this->size] = NULL;
    return out;
}

Ptr back_List(ListObject* this) {
    return this->data[this->size-1];
}

void extend_List(ListObject* this, ListObject* other) {
    long reqsize = this->size + other->size;
    if (reqsize >= this->capacity)
        _List_resize(this, reqsize*RESIZE_FACTOR);
    this->size = reqsize;
    long i, j;
    for (
        i=this->size,   j=0;
        i<reqsize; 
        i++,            j++
    ) {
        Ptr ptr = other->data[j];
        if (ptr != NULL)
            incref(ptr);
        this->data[i] = ptr;
    }
}

// Accessor interface

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

ListObject* slice_List(ListObject* this, long i, long j, long step) {
    if (j < i)
        return NULL;
    if (i < 0 || j >= this->size)
        return NULL;
    
    ListObject* sublist = new_List();
    
    long d = j - i;
    if (d > MIN_CAPACITY)
        _List_resize(sublist, d*RESIZE_FACTOR);
    
    long k, p;
    for (k=i, p=0; k<j; k++, p++) {
        Ptr ptr = this->data[k];
        if (ptr != NULL)
            incref(ptr);
        sublist->data[p] = ptr;
    }
    sublist->size = d;
    return sublist;
}
