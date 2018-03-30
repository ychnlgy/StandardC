#include "RefList.h"
#include "List_protected.h"
#include "RefList_protected.h"

#include "gc.h"

#include <stdlib.h>
// malloc

#define PTR_SIZE sizeof(void*)

void del_RefList(void* ptr) {
    foreach_List(ptr, &decref);
    del_List(ptr);
}

void* new_RefList() {
    RefList* this = new(sizeof(RefList), &del_RefList);
    build_List((List*) this);
    
    // override methods
    this->super.push      = &push_RefList;
    this->super.setitem   = &setitem_RefList;
    this->super.set       = &set_RefList;
    
    init_List(this, PTR_SIZE);
    return this;
}

// Modifiers
void push_RefList(void* this, void* item) {
    incref(item);
    push_List(this, item);
}

// Fast but unsafe operations (does not check range).
void setitem_RefList(void* this, int i, void* item) {
    void* ptr = getitem_List(this, i);
    setitem_List(this, i, item);
    
    decref(ptr);
    incref(item);
}

// Slow but safe accessors (checks for range)
bool set_RefList(void* this, int i, void* item) {
    void* ptr = at_List(this, i);
    if (ptr == NULL)
        return false;
    
    setitem_RefList(this, i, item);
    return true;
}

