#ifndef STDC_FILESYS_PATH_PATH
#define STDC_FILESYS_PATH_PATH

#include "stdc/lib.h"

typedef struct PathObject PathObject;

typedef struct {
    Ptr     (*new)  ();
    void    (*init) (PathObject*);
    void    (*del)  (Ptr);
    
    

} PathVtable;

extern PathVtable Path;

#endif
