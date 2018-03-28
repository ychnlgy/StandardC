#ifndef STANDARDC_STRING
#define STANDARDC_STRING

#include "bool.h"

typedef const char* CStr;
typedef struct StringFields StringFields;
typedef struct StringVtable StringVtable;

typedef struct String String;

void* new_String();

struct String {
    StringFields* fields;
    StringVtable* vtable;
    
    void        (*init)     (void*, CStr);
    String*     (*copy)     (void*);
    bool        (*equals)   (void*, void*);
    int         (*len)      (void*);
};

#endif
