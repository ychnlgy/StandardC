#ifndef STDC_FILESYS_OS_OS
#define STDC_FILESYS_OS_OS

#include "stdc/lib.h"

typedef struct {
    // cwd
    char*       (*cwd)          (MemoryObject*);
    
    // path
    bool        (*readable)     (CStr);
    bool        (*writable)     (CStr);
    bool        (*isfile)       (CStr);
    bool        (*isdir)        (CStr);
    
    // listdir
    ListObject* (*listdir)      (CStr);
    
    // chmod
    int         (*chmod)        (CStr, CStr);
    
} OsVtable;

extern OsVtable Os;

#endif

