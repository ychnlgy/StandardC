#ifndef STDC_FILESYS_OS_PRIVATE
#define STDC_FILESYS_OS_PRIVATE

#include <sys/types.h>

#include "stdc/lib.h"

// Helpers
typedef void (*_ChPermissionFn)(mode_t*, mode_t);

static void             rmPermission    (mode_t*, mode_t);
static void             addPermission   (mode_t*, mode_t);
static int              chPermission    (CStr, _ChPermissionFn, mode_t);
static _ChPermissionFn  getSetFn        (char);
static mode_t           getMode         (CStr, int); 

// Implemented
static char* cwd_Os(MemoryObject*);
static bool readable_Os  (CStr);
static bool writable_Os (CStr);
static bool isfile_Os   (CStr);
static bool isdir_Os    (CStr);
static ListObject* listdir_Os(CStr, MemoryObject*);
static int  chmod_Os        (CStr, CStr);
static long size_Os(CStr);

#endif
