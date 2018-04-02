#ifndef STDC_FILESYS_PATH_PATH
#define STDC_FILESYS_PATH_PATH

#include "stdc/lib.h"

typedef struct PathObject PathObject;

typedef struct {
    Ptr     (*new)  ();
    void    (*init) (PathObject*);
    void    (*del)  (Ptr);
    
    // Object
    CStr            (*cstr)         (PathObject*);
    StringObject*   (*str)          (PathObject*);
    void            (*set)          (PathObject*, CStr);
    
    // Numeric
    PathObject*     (*add)          (PathObject*, PathObject*, MemoryObject*);
    PathObject*     (*abs)          (PathObject*, MemoryObject*);
    PathObject*     (*norm)         (PathObject*, MemoryObject*);

    // Methods
    bool            (*isfile)       (PathObject*);
    bool            (*isdir)        (PathObject*);
    ListObject*     (*listdir)      (PathObject*, MemoryObject*);

} PathVtable;

extern PathVtable Path;

#endif
