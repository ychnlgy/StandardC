#ifndef STDC_UTIL_STRING_STRING
#define STDC_UTIL_STRING_STRING

#include "stdc/lib.h"

typedef struct StringObject StringObject;

typedef struct {

    // Construction/destruction
    Ptr             (*new)          ();
    void            (*init)         (StringObject*);
    void            (*del)          (Ptr);
    
    // Object
    CStr            (*cstr)         (StringObject*);
    bool            (*equals)       (StringObject*, StringObject*);
    StringObject*   (*copy)         (StringObject*, MemoryObject*);
    
    // Hashable
    long            (*hash)         (StringObject*);
    
    // Numeric
    StringObject*   (*add)          (StringObject*, StringObject*, MemoryObject*);
//    StringObject*   (*mult)         (StringObject*, MemoryObject*, long);
    
    // Container
    long            (*size)         (StringObject*);
    bool            (*contains)     (StringObject*, StringObject*);
    
    // Accessor
    void            (*set)          (StringObject*, CStr);
    char*           (*at)           (StringObject*, long);
    char*           (*getitem)      (StringObject*, long);
    StringObject*   (*slice)        (StringObject*, long, long, MemoryObject*);
    long            (*index)        (StringObject*, StringObject*);
    
    // Methods
    StringObject*   (*format)       (StringObject*, MemoryObject*, ...);
    bool            (*startswith)   (StringObject*, StringObject*);
    bool            (*endswith)     (StringObject*, StringObject*);
    StringObject*   (*rstrip)       (StringObject*, MemoryObject*);
    StringObject*   (*lstrip)       (StringObject*, MemoryObject*);
    StringObject*   (*strip)        (StringObject*, MemoryObject*);
    ListObject*     (*split)        (StringObject*, char, MemoryObject*);
    ListObject*     (*splitstr)     (StringObject*, StringObject*, MemoryObject*);

} StringVtable;

extern StringVtable String;

#endif
