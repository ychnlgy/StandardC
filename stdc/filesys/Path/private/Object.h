#ifdef STDC_FILESYS_PATH_PRIVATE

static Ptr              new_Path     ();
static void             init_Path    (PathObject*);
static void             del_Path     (Ptr);

static CStr             cstr_Path   (PathObject*);
static StringObject*    str_Path    (PathObject*);
static void             set_Path    (PathObject*, CStr);

#endif
