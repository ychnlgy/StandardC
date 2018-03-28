#ifndef STANDARDC_LIST_PROTECTED
#define STANDARDC_LIST_PROTECTED

#include "List.h"

struct ListFields {
    int inited;
    int typesize;
    int len;
    int capacity;
    char* data;
};

void del_List(void* ptr);

// Init
void init_List(List* this, int typesize);
void initall_List(List* this, int typesize, int len, void* value);
void initarray_List(List* this, int typesize, int len, void* array);

// Getters
int len_List(List* this);

// Modifiers
void push_List(List* this, void* item);
void* pop_List(List* this);

// Fast but unsafe operations (does not check range).
void* getitem_List(List* this, int i);
void setitem_List(List* this, int i, void* item);

// Slow but safe operations.(checks range).
void* at_List(List* this, int i);
bool set_List(List* this, int i, void* item);

// Iteration
void foreach_List(List* this, void(*fn)(void*));
//List* map_List(List*

#endif
