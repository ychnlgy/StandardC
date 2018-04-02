#ifdef STDC_UTIL_STRING_PRIVATE

#include <stdarg.h>
// va_list, va_start, va_end

static StringObject* format_String(StringObject* this, MemoryObject* mem, ...) {
    va_list args;
    
    StringObject* s = Memory.make(mem, &new_String);
    
    va_start(args, mem);
    long size = getFormattedSize(this, args);
    va_end(args);
    
    // I don't know how to test this in a portable way.
    // if (size < 0) // encoding error
    //    return NULL;
    
    s->size = size;
    
    va_start(args, mem);
    s->cstr = getFormattedCStr(this, args, size);
    s->hash = calculateHash(s);
    va_end(args);
    
    return s;
}

static bool startswith_String(StringObject* this, StringObject* substring) {
    if (substring->size > this->size)
        return false;
    return match(this, substring, 0);
}

static bool endswith_String(StringObject* this, StringObject* substring) {
    if (substring->size > this->size)
        return false;
    return match(this, substring, this->size-substring->size);
}

#endif

