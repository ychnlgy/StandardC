#include "RefList.h"
#include "List_protected.h"
#include "RefList_protected.h"

#include "gc.h"

#define PTR_SIZE sizeof(void*)

void del_RefList(void* ptr) {
    foreach_List((List*) ptr, &decref);
    del_List(ptr);
}

void* new_RefList() {
    RefList* this = new(sizeof(RefList), &del_RefList);
    this->fields = malloc(sizeof(ListFields));
    this->fields->inited = 0;
    
    // super methods
    this->len       = &len_List;
    this->pop       = &pop_List;
    this->getitem   = &getitem_List;
    this->at        = &at_List;
    this->foreach   = &foreach_List;
    
    // derived methods
    this->push      = &push_RefList;
    this->setitem   = &setitem_RefList;
    this->set       = &set_RefList;
    
    init_List((List*) this, PTR_SIZE);
    return this;
}

// Modifiers
void push_RefList(RefList* this, void* item) {
    incref(&item);
    push_List((List*) this, item);
}

// Fast but unsafe operations (does not check range).
void setitem_RefList(RefList* this, int i, void* item) {
    List* super = (List*) this;
    
    void* ptr = getitem_List(super, i);
    setitem_List(super, i, item);
    
    decref(&ptr);
    incref(&item);
}

// Slow but safe accessors (checks for range)
bool set_RefList(RefList* this, int i, void* item) {
    List* super = this;
    void* ptr = at_List(super, i);
    if (ptr == NULL)
        return false;
    
    setitem_List(super, i, item);
    
    decref(&ptr);
    incref(&item);
}

