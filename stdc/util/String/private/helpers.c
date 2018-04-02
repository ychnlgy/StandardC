#ifdef STDC_UTIL_STRING_PRIVATE

#include <string.h>
// strncpy

#include <stdio.h>
// vsnprintf

static char* copyCStr(CStr src, int len) {
    char* cstrPtr = malloc(sizeof(char)*(len+1));
    strncpy(cstrPtr, src, len);
    cstrPtr[len] = '\0';
    return cstrPtr;
}

static long getFormattedSize(StringObject* this, va_list args) {
    return vsnprintf(
        NULL,
        0,
        this->cstr,
        args
    );
}

static char* getFormattedCStr(StringObject* this, va_list args, long size) {
    char* cstr = malloc(sizeof(char)*(++size));
    vsnprintf(
        cstr,
        size,
        this->cstr,
        args
    );
    return cstr;
}

static bool isWithin(StringObject* this, long i) {
    return i < this->size && this->size != 0;
}

static long fitWithin(StringObject* this, long i) {
    return MOD(i, this->size);
}

static bool match(StringObject* this, StringObject* other, long i) {
    long k, p;
    for (
        k=i, p=0;
        p < other->size;
        k++, p++
    ) {
        if (this->cstr[k] != other->cstr[p])
            return false;
    }
    return true;
}

/*
 * White space characters (6) that Python checks for.
 */

static bool isWhiteSpace(char c) {
    switch (c) {
        case ' ':       // 1
        case '\t':      // 2
        case '\n':      // 3
        case '\r':      // 4
        case '\x0b':    // 5
        case '\x0c':    // 6
            return true;
        default:
            return false;
    }
}

static long countWhiteSpace(StringObject* this, long start, long step) {
    long i;
    long n = this->size + 1;
    for (i = start; --n > 0; i += step)
        if (!isWhiteSpace(this->cstr[i]))
            break;
    return i;
}

static ListObject* split(
    StringObject* this, 
    Ptr ptr, 
    long size, 
    bool (*fn)(StringObject*, StringObject*, long),
    MemoryObject* mem
) {
    ListObject* out = Memory.make(mem, List.new);
    long start = 0;
    long i;
    for (i=0; i<this->size-size+1; i++) {
        if (fn(this, ptr, i)) {
            List.push(out, slice_String(this, start, i, mem));
            start = i + size;
            i += size -1;
        }
    }
    if (start <= this->size)
        List.push(out, slice_String(this, start, this->size, mem));
    return out;
}

#endif
