#ifndef STDC_UTIL_OBJECT_OBJECT
#define STDC_UTIL_OBJECT_OBJECT

#include "stdc/lib.h"

Ptr new_Object();
typedef struct Object Object;

typedef struct {
    bool        (*equals)   (Object*, Object*);
    String*     (*repr)     (Object*);
} ObjectVtable;

struct Object {
    ObjectVtable*   _;
};

#endif
