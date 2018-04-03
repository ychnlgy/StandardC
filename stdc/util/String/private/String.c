#ifdef STDC_UTIL_STRING_PRIVATE

#include <stdarg.h>
// va_list, va_start, va_end

#include <assert.h>

static bool eqCStr_String(StringObject* this, CStr cstr) {
    return compareCStr(this->size == 0, cstr == NULL, this->cstr, cstr);
}

static StringObject* format_String(StringObject* this, MemoryObject* mem, ...) {
    va_list args;
    
    StringObject* s = Memory.make(mem, &new_String);
    
    va_start(args, mem);
    long size = getFormattedSize(this, args);
    va_end(args);
    
    // I don't know how to test this in a portable way.
    // if (size < 0) // encoding error
    //    return NULL;
    assert(size >= 0);
    
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

static StringObject* rstrip_String(StringObject* this, MemoryObject* mem) {
    long end = countWhiteSpace(this, this->size-1, -1);
    return slice_String(this, 0, end+1, mem);
}

static StringObject* lstrip_String(StringObject* this, MemoryObject* mem) {
    long start = countWhiteSpace(this, 0, 1);
    return slice_String(this, start, this->size, mem);
}

static StringObject* strip_String(StringObject* this, MemoryObject* mem) {
    long start = countWhiteSpace(this, 0, 1);
    if (start == this->size)
        return Memory.make(mem, &new_String);
    
    long end = countWhiteSpace(this, this->size-1, -1);
    return slice_String(this, start, end+1, mem);
}

static ListObject* split_String(StringObject* this, char delim, MemoryObject* mem) {
    return split(this, &delim, 1, &matchChar, mem);
}

static ListObject* splitstr_String(StringObject* this, StringObject* substr, MemoryObject* mem) {
    if (substr->size == 0)
        return NULL;
    else
        return split(this, substr, substr->size, &match, mem);
}

static StringObject* replace_String(StringObject* this, char oldc, char newc, MemoryObject* mem) {
    ListObject* parts = split_String(this, oldc, mem);
    return join_String(newc, parts, mem);
}

static StringObject* replacestr_String(StringObject* this, StringObject* oldSubstr, StringObject* newSubstr, MemoryObject* mem) {
    if (oldSubstr->size == 0)
        return NULL;
    ListObject* parts = splitstr_String(this, oldSubstr, mem);
    return joinstr_String(newSubstr, parts, mem);
}

static StringObject* join_String(char c, ListObject* liststr, MemoryObject* mem) {
    return join(&c, 1, liststr, mem);
}

static StringObject* joinstr_String(StringObject* this, ListObject* liststr, MemoryObject* mem) {
    return join(this->cstr, this->size, liststr, mem);
}

#endif

