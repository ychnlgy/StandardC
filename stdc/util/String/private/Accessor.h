#ifdef STDC_UTIL_STRING_PRIVATE

static void             set_String      (StringObject*, CStr);
static char*            getitem_String  (StringObject*, long);
static char*            at_String       (StringObject*, long);
static StringObject*    slice_String    (StringObject*, long, long, MemoryObject*);
static long             index_String    (StringObject*, StringObject*);

#endif
