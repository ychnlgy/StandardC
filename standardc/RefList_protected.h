#ifndef STANDARDC_REFLIST_PROTECTED
#define STANDARDC_REFLIST_PROTECTED

#include "RefList.h"

void del_RefList(void* ptr);

// Modifiers
void push_RefList(void* this, void* item);

// Fast but unsafe operations (does not check range).
void setitem_RefList(void* this, int i, void* item);

// Slow but safe accessors (checks for range)
bool set_RefList(void* this, int i, void* item);

#endif
