#ifdef STDC_UTIL_LIST_PRIVATE

#include <stdarg.h>
// va_arg, va_start, va_end, va_list

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

#endif
