#include "private.h"

Ptr getitem_List(ListObject* this, long i) {
    return this->data[i];
}

void setitem_List(ListObject* this, long i, Ptr entry) {
    Ptr original = this->data[i];
    this->data[i] = entry;
    incref(entry);
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

ListObject* slice_List(ListObject* this, MemoryObject* mem, long i, long j) {
    if (j < i)
        return NULL;
    if (i < 0 || j > this->size)
        return NULL;
    
    ListObject* sublist = Memory.make(mem, &new_List);
    
    long d = j - i;
    if (d > MIN_CAPACITY)
        _List_resize(sublist, d*RESIZE_FACTOR);
    
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
