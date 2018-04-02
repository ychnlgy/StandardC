#ifdef STDC_UTIL_STRING_PRIVATE

static Ptr              new_String      ();
static void             del_String      (Ptr);
static void             init_String     (StringObject*);

static bool             equals_String   (StringObject*, StringObject*);
static CStr             cstr_String     (StringObject*);
static StringObject*    copy_String     (StringObject*, MemoryObject*);

#endif
