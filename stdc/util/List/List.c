#include <stdarg.h>
// va_arg, va_start, va_end, va_list

#include "private.h"

ListVtable List = {

    // Construction/destruction
    .new        = &new_List,
    .init       = &init_List,
    .del        = &del_List,
    
    // Numeric
    .add        = &concat_List,
    
    // Object interface
    .equals     = &equals_List,
    .copy       = &copy_List,
    
    // Container interface
    .size       = &size_List,
    .clear      = &clear_List,
    .isEmpty    = &isEmpty_List,
    
    // Stack interface
    .push       = &push_List,
    .pushes     = &pushes_List,
    .pop        = &pop_List,
    .back       = &back_List,
    .extend     = &extend_List,
    
    // Accessor interface
    .getitem    = &getitem_List,
    .setitem    = &setitem_List,
    .at         = &at_List,
    .set        = &set_List,
    .slice      = &slice_List,
    
    // Iterable
    .filter     = &filter_List
};

// Helpers
static void resize(ListObject* this, size_t n) {
    Ptr* data = malloc(n*PTR_SIZE);
    long size = MIN(this->size, n);
    this->size = size;

    while (--size >= 0)
        data[size] = this->data[size];

    free(this->data);

    this->capacity = n;
    this->data = data;
}

static bool isWithin(ListObject* this, long i) {
    return i < this->size && this->size != 0;
}

static long fitWithin(ListObject* this, long i) {
    return MOD(i, this->size);
}

// Object
static Ptr new_List() {
    ListObject* this = new(sizeof(List), &del_List);
    init_List(this);
    return this;
}

static void init_List(ListObject* this) {
    this->size     = 0;
    this->capacity = MIN_CAPACITY;
    this->data     = malloc(MIN_CAPACITY*PTR_SIZE);
}

static void del_List(Ptr ptr) {
    ListObject this = *((ListObject*) ptr);
    long i;
    for (i=0; i<this.size; i++)
       decref(this.data[i]);
    free(this.data);
}

static bool equals_List(ListObject* this, ListObject* other) {
    if (this->size != other->size)
        return false;
    
    long i;
    for (i=0; i<this->size; i++)
        if (this->data[i] != other->data[i])
            return false;
    return true;
}

static ListObject* copy_List(ListObject* this, MemoryObject* mem) {
    ListObject* out = Memory.make(mem, &new_List);
    extend_List(out, this);
    return out;
}

// Container
static long size_List(ListObject* this) {
    return this->size;
}

static void clear_List(ListObject* this) {
    del_List(this);
    init_List(this);
}

static bool isEmpty_List(ListObject* this) {
    return this->size == 0;
}

// Accessor
static Ptr getitem_List(ListObject* this, long i) {
    return this->data[i];
}

static void setitem_List(ListObject* this, long i, Ptr entry) {
    Ptr original = this->data[i];
    this->data[i] = entry;
    incref(entry);
    decref(original);
}

static Ptr at_List(ListObject* this, long i) {
    if (isWithin(this, i))
        return this->data[fitWithin(this, i)];
    else
        return NULL;
}

static bool set_List(ListObject* this, long i, Ptr entry) {
    if (isWithin(this, i)) {
        setitem_List(this, fitWithin(this, i), entry);
       return true;
    } else {
        return false;
    }
}

static ListObject* slice_List(ListObject* this, MemoryObject* mem, long i, long j) {
    if (j < i || i < 0 || j > this->size)
        return NULL;
    
    ListObject* sublist = Memory.make(mem, &new_List);
    
    long d = j - i;
    if (d > MIN_CAPACITY)
        resize(sublist, d*RESIZE_FACTOR);
    
    long k, p;
    for (
        k=i, p=0;
        k<j; 
        k++, p++
    ) {
        Ptr ptr = this->data[k];
        incref(ptr);
        sublist->data[p] = ptr;
    }
    sublist->size = d;
    return sublist;
}

// Stack
static void push_List(ListObject* this, Ptr entry) {
    if (this->size >= this->capacity)
       resize(this, this->capacity*RESIZE_FACTOR);
    incref(entry);
    this->data[this->size++] = entry;
}

static void pushes_List(ListObject* this, long n, ...) {
    va_list args;
    va_start(args, n);
    
    while (n-- > 0)
        push_List(this, va_arg(args, Ptr));
    
    va_end(args);
}

Ptr pop_List(ListObject* this, MemoryObject* mem) {
    if (this->size <= 0)
        return NULL;
    Ptr out = this->data[--this->size];
    Memory.track(mem, out);
    return out;
}

Ptr back_List(ListObject* this) {
    return this->data[this->size-1];
}

static void extend_List(ListObject* this, ListObject* other) {
    long reqsize = this->size + other->size;
    if (reqsize >= this->capacity)
        resize(this, reqsize*RESIZE_FACTOR);
    
    long i, j;
    for (
        i=this->size,   j=0;
        i<reqsize; 
        i++,            j++
    ) {
        Ptr ptr = other->data[j];
        incref(ptr);
        this->data[i] = ptr;
    }
    
    this->size = reqsize;
}

// Numeric
static ListObject* concat_List(ListObject* this, ListObject* other, MemoryObject* mem) {
    ListObject* newl = Memory.make(mem, &new_List);
    List.extend(newl, this);
    List.extend(newl, other);
    return newl;
}

// Iterable
static ListObject* filter_List(ListObject* this, FilterFunc fn, MemoryObject* mem) {
    ListObject* out = Memory.make(mem, List.new);
    
    long i;
    for (i=0; i<this->size; i++) {
        Ptr p = this->data[i];
        if (fn(p))
            push_List(out, p);
    }
    
    return out;
}
