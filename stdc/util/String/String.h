#ifndef STDC_UTIL_STRING_STRING
#define STDC_UTIL_STRING_STRING

#include "stdc/lib.h"

Ptr new_String();
typedef struct String String;

typedef struct {
    void        (*set)      (String*, CStr);
    String*     (*copy)     (String*);
    bool        (*equals)   (String*, String*);

    // Getters
    long        (*size)     (String*);
    CStr        (*cstr)     (String*);

    // Useful methods
    String*     (*format)   (String*, ...);
    
} StringVtable;

struct String {
    StringVtable*   _;
    long            _size;
    char*           _cstr;
};

#endif
