#include "stdc/lib.h"
#include "String_protected.h"

#include <string.h>
// strncpy, strlen, strcmp

// === HELPERS ===

char* _copy_CStr(CStr src, int len) {
    char* cstrPtr = malloc(sizeof(char)*(len+1));
    strncpy(cstrPtr, src, len);
    cstrPtr[len] = '\0';
    return cstrPtr;
}

// === METHODS ===

void del_String(Ptr this) {
    free(((String*) this)->_cstr);
}

Ptr new_String() {
    String* this = new(sizeof(String), &del_String);
    init_String(this);
    return this;
}

void init_String(String* this) {
    this->_ = &STRING_VTABLE;
    this->_size = 0;
    this->_cstr = NULL;
}

void set_String(String* this, CStr cstr) {
    free(this->_cstr);
    this->_size = strlen(cstr);
    this->_cstr = _copy_CStr(cstr, this->_size);
}

String* copy_String(String* this) {
    String* copy = new_String();
    copy->_size = this->_size;
    copy->_cstr = _copy_CStr(this->_cstr, this->_size);
    return copy;
}

bool equals_String(String* this, String* other) {
    return strcmp(this->_cstr, other->_cstr) == 0;
}

long size_String(String* this) {
    return this->_size;
}

CStr cstr_String(String* this) {
    return this->_cstr;
}

