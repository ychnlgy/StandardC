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
    StringObject*   (*slice)        (StringObject*, MemoryObject*, long, long);
    long            (*index)        (StringObject*, StringObject*);
    
    // Methods
    StringObject*   (*format)       (StringObject*, MemoryObject*, ...);
    bool            (*startswith)   (StringObject*, StringObject*);
    bool            (*endswith)     (StringObject*, StringObject*);
    

    // Useful methods
    
    
    // TODO: implement
//    StringObject*     (*rstrip)       (StringObject*, MemoryObject*);
//    StringObject*     (*lstrip)       (StringObject*, MemoryObject*);
//    StringObject*     (*strip)        (StringObject*, MemoryObject*);
//    List*       (*split)        (StringObject*, char, MemoryObject*);
//    List*       (*splitstr)     (StringObject*, StringObject*, MemoryObject*);
   
//    
//    long        (*hash)         (StringObject*);


    
} StringVtable;

extern StringVtable String;

#endif
