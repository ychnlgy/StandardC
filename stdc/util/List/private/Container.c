#include "private.h"

long size_List(ListObject* this) {
    return this->size;
}

void clear_List(ListObject* this) {
    del_List(this);
    init_List(this);
}
