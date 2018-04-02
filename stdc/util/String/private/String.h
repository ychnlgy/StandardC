#ifdef STDC_UTIL_STRING_PRIVATE

static StringObject*    format_String       (StringObject*, MemoryObject*, ...);
static bool             startswith_String   (StringObject*, StringObject*);
static bool             endswith_String     (StringObject*, StringObject*);
static StringObject*    rstrip_String       (StringObject*, MemoryObject*);
static StringObject*    lstrip_String       (StringObject*, MemoryObject*);
static StringObject*    strip_String        (StringObject*, MemoryObject*);
static ListObject*      split_String        (StringObject*, char, MemoryObject*);
static ListObject*      splitstr_String     (StringObject*, StringObject*, MemoryObject*);

#endif
