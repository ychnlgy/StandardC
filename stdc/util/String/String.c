#include "stdc/lib.h"
#include "String_protected.h"
#include "String_private.h"

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

long _String_getFormattedSize(StringObject* this, va_list args) {
    return vsnprintf(
        NULL,
        0,
        this->cstr,
        args
    );
}

char* _String_getFormattedCStr(StringObject* this, va_list args, long size) {
    char* cstr = malloc(sizeof(char)*(++size));
    vsnprintf(
        cstr,
        size,
        this->cstr,
        args
    );
    return cstr;
}

// === METHODS ===

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

bool equals_String(StringObject* this, StringObject* other) {
    return strcmp(this->cstr, other->cstr) == 0;
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

