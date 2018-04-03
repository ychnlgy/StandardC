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
    this->hash = calculateHash(this);
}

static bool equals_String(StringObject* this, StringObject* other) {
    return compareCStr(this->size == 0, other->size == 0, this->cstr, other->cstr);
}

static CStr cstr_String(StringObject* this) {
    return this->cstr;
}

static StringObject* copy_String(StringObject* this, MemoryObject* mem) {
    StringObject* copy = Memory.make(mem, &new_String);
    copy->size = this->size;
    copy->cstr = copyCStr(this->cstr, this->size);
    copy->hash = this->hash;
    return copy;
}

#endif
