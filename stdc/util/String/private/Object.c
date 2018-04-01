#ifdef STDC_UTIL_STRING_PRIVATE

#include <string.h>
// strcmp

static void del_String(Ptr this) {
    free(((StringObject*) this)->cstr);
}

static Ptr new_String() {
    StringObject* this = new(sizeof(StringObject), &del_String);
    init_String(this);
    return this;
}

static void init_String(StringObject* this) {
    this->size = 0;
    this->cstr = NULL;
}

static bool equals_String(StringObject* this, StringObject* other) {
    return strcmp(this->cstr, other->cstr) == 0;
}

#endif
