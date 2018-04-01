#include "private.h"

ListObject* concat_List(ListObject* this, ListObject* other, MemoryObject* mem) {
    ListObject* newl = Memory.make(mem, &new_List);
    List.extend(newl, this);
    List.extend(newl, other);
    return newl;
}
