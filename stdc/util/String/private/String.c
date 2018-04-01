#ifdef STDC_UTIL_STRING_PRIVATE

#include <string.h>
// strlen

#include <stdarg.h>
// va_list, va_start, va_end

static void set_String(StringObject* this, CStr cstr) {
    free(this->cstr);
    this->size = strlen(cstr);
    this->cstr = copyCStr(cstr, this->size);
}

static StringObject* copy_String(StringObject* this) {
    StringObject* copy = new_String();
    copy->size = this->size;
    copy->cstr = copyCStr(this->cstr, this->size);
    return copy;
}

static long size_String(StringObject* this) {
    return this->size;
}

static CStr cstr_String(StringObject* this) {
    return this->cstr;
}

static StringObject* format_String(StringObject* this, ...) {
    va_list args;
    
    StringObject* s = new_String();
    
    va_start(args, this);
    long size = getFormattedSize(this, args);
    va_end(args);
    
    // I don't know how to test this in a portable way.
    // if (size < 0) // encoding error
    //    return NULL;
    
    s->size = size;
    
    va_start(args, this);
    s->cstr = getFormattedCStr(this, args, size);
    va_end(args);
    
    return s;
}

#endif

