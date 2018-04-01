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

#endif
