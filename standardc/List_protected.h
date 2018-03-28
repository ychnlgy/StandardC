#ifndef STANDARDC_LIST_PROTECTED
#define STANDARDC_LIST_PROTECTED

#include "List.h"

struct ListFields {
    int typesize;
    int len;
    int capacity;
    char* data;
};

struct ListVtable {};

void del_List(void* ptr);
void* malloc_ListFields();

// Init
void init_List(void* this, int typesize);
void initall_List(void* this, int typesize, int len, void* value);
void initarray_List(void* this, int typesize, int len, void* array);

// Getters
int len_List(void* this);

// Modifiers
void push_List(void* this, void* item);
void* pop_List(void* this);

// Fast but unsafe operations (does not check range).
void* getitem_List(void* this, int i);
void setitem_List(void* this, int i, void* item);

// Slow but safe operations.(checks range).
void* at_List(void* this, int i);
bool set_List(void* this, int i, void* item);

// Iteration
void foreach_List(void* this, void(*fn)(void*));
//void* map_List(void*

#endif
