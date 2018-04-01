#include <string.h>
// strlen

#include <stdarg.h>
// va_list, va_start, va_end

#include "private.h"

void set_String(StringObject* this, CStr cstr) {
    free(this->cstr);
    this->size = strlen(cstr);
    this->cstr = _String_copyCStr(cstr, this->size);
}

StringObject* copy_String(StringObject* this) {
    StringObject* copy = new_String();
    copy->size = this->size;
    copy->cstr = _String_copyCStr(this->cstr, this->size);
    return copy;
}

long size_String(StringObject* this) {
    return this->size;
}

CStr cstr_String(StringObject* this) {
    return this->cstr;
}

StringObject* format_String(StringObject* this, ...) {
    va_list args;
    
    StringObject* s = new_String();
    
    va_start(args, this);
    long size = _String_getFormattedSize(this, args);
    va_end(args);
    
    // I don't know how to test this in a portable way.
    // if (size < 0) // encoding error
    //    return NULL;
    
    s->size = size;
    
    va_start(args, this);
    s->cstr = _String_getFormattedCStr(this, args, size);
    va_end(args);
    
    return s;
}

