#ifdef STDC_FILESYS_OS_PRIVATE

static int  chmod_Os        (CStr, CStr);

// Helpers
typedef void (*_ChPermissionFn)(mode_t*, mode_t);

static void             rmPermission    (mode_t*, mode_t);
static void             addPermission   (mode_t*, mode_t);
static int              chPermission    (CStr, _ChPermissionFn, mode_t);
static _ChPermissionFn  getSetFn        (char);
static mode_t           getMode         (CStr, int); 

#endif
