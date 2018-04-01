#include "stdc/lib.h"
#include "String_protected.h"

#include <string.h>
// strncpy, strlen, strcmp

#include <stdarg.h>
// va_list, va_start, va_end

#include <stdio.h>
// snprintf

// === HELPERS ===

char* _String_copyCStr(CStr src, int len) {
    char* cstrPtr = malloc(sizeof(char)*(len+1));
    strncpy(cstrPtr, src, len);
    cstrPtr[len] = '\0';
    return cstrPtr;
}

long _String_getFormattedSize(String* this, va_list args) {
    return vsnprintf(
        NULL,
        0,
        this->_cstr,
        args
    );
}

char* _String_getFormattedCStr(String* this, va_list args, long size) {
    char* cstr = malloc(sizeof(char)*(++size));
    vsnprintf(
        cstr,
        size,
        this->_cstr,
        args
    );
    return cstr;
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
    this->_cstr = _String_copyCStr(cstr, this->_size);
}

String* copy_String(String* this) {
    String* copy = new_String();
    copy->_size = this->_size;
    copy->_cstr = _String_copyCStr(this->_cstr, this->_size);
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

String* format_String(String* this, ...) {
    va_list args;
    
    String* s = new_String();
    
    va_start(args, this);
    long size = _String_getFormattedSize(this, args);
    va_end(args);
    
    // I don't know how to test this in a portable way.
    // if (size < 0) // encoding error
    //    return NULL;
    
    s->_size = size;
    
    va_start(args, this);
    s->_cstr = _String_getFormattedCStr(this, args, size);
    va_end(args);
    
    return s;
}

