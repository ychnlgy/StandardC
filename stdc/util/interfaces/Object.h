// Interface

#ifndef STDC_UTIL_INTERFACES_OBJECT
#define STDC_UTIL_INTERFACES_OBJECT

#include "stdc/lib.h"

typedef struct Object Object;

typedef struct {
    bool    (*equals)   (Object*, Object*);
    String* (*repr)     (Object*);
} ObjectVtable;

struct Object {
    ObjectVtable* _;
};

#endif
