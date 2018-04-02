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

#endif
