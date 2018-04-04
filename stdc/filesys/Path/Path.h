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
    bool            (*equals)       (PathObject*, PathObject*);
    PathObject*     (*copy)         (PathObject*, MemoryObject*);
    
    // Numeric
    PathObject*     (*add)          (PathObject*, PathObject*, MemoryObject*);
    PathObject*     (*abs)          (PathObject*, MemoryObject*);
    PathObject*     (*norm)         (PathObject*, MemoryObject*);

    // Methods
    PathObject*     (*addcstr)      (PathObject*, CStr, MemoryObject*);
    bool            (*isfile)       (PathObject*);
    bool            (*isdir)        (PathObject*);
    ListObject*     (*listdir)      (PathObject*, MemoryObject*);
    void            (*setrel)       (PathObject*, CStr);
    void            (*setabs)       (PathObject*, CStr);
    void            (*setrelstr)    (PathObject*, StringObject*);
    void            (*setabsstr)    (PathObject*, StringObject*);
    PathObject*     (*dirname)      (PathObject*, MemoryObject*);
//    StringObject*   (*ext)          (PathObject*);
    StringObject*   (*basename)     (PathObject*);

} PathVtable;

extern PathVtable Path;

#endif
