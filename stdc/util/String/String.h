#ifndef STDC_UTIL_STRING_STRING
#define STDC_UTIL_STRING_STRING

#include "stdc/lib.h"

typedef struct StringObject StringObject;

typedef struct {

    // Construction/destruction
    Ptr             (*new)          ();
    void            (*init)         (StringObject*);
    void            (*del)          (Ptr);
    
    // Object interface
    bool            (*equals)       (StringObject*, StringObject*);
    
    // Getters
    long            (*size)         (StringObject*);
    CStr            (*cstr)         (StringObject*);
    
    // Methods
    void            (*set)          (StringObject*, CStr);
    StringObject*   (*copy)         (StringObject*, MemoryObject*);
    StringObject*   (*format)       (StringObject*, MemoryObject*, ...);
    
    

    // Useful methods
    
    
    // TODO: implement
//    String*     (*rstrip)       (String*);
//    String*     (*lstrip)       (String*);
//    String*     (*strip)        (String*);
//    List*       (*split)        (String*, char);
//    List*       (*splitstr)     (String*, String*);
//    bool        (*beginswith)   (String*, String*);
//    bool        (*endswith)     (String*, String*);
//    bool        (*contains)     (String*, String*);
//    long        (*hash)         (String*);

//    char*       (*at)           (String*, long);
//    bool        (*set)          (String*, long, char);
//    char*       (*getitem)      (String*, long);
//    void        (*setitem)      (String*, long, char);
//    String*     (*slice)        (String*, MemoryObject*, long, long);
    
} StringVtable;

extern StringVtable String;

#endif
