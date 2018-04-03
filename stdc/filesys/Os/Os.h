#ifndef STDC_FILESYS_OS_OS
#define STDC_FILESYS_OS_OS

#include "stdc/lib.h"

typedef struct {
    char*   (*cwd)      (MemoryObject*);
    bool    (*canRead)  (CStr);
    bool    (*canWrite) (CStr);
    bool    (*isfile)   (CStr);
    bool    (*isdir)    (CStr);
} OsVtable;

extern OsVtable Os;

#endif

