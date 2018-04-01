#include <string.h>
// strcmp

#include "private.h"

void del_String(Ptr this) {
    free(((StringObject*) this)->cstr);
}

Ptr new_String() {
    StringObject* this = new(sizeof(StringObject), &del_String);
    init_String(this);
    return this;
}

void init_String(StringObject* this) {
    this->size = 0;
    this->cstr = NULL;
}

bool equals_String(StringObject* this, StringObject* other) {
    return strcmp(this->cstr, other->cstr) == 0;
}
