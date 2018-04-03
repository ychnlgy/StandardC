#ifndef STDC_FILESYS_OS_OS
#define STDC_FILESYS_OS_OS

#include "stdc/lib.h"

typedef struct {
    CStr (*cwd)(MemoryObject*);
} OsVtable;

extern OsVtable Os;

#endif

