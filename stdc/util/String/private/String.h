#ifdef STDC_UTIL_STRING_PRIVATE

static bool             eqCStr_String       (StringObject*, CStr);
static StringObject*    format_String       (StringObject*, MemoryObject*, ...);
static bool             startswith_String   (StringObject*, StringObject*);
static bool             endswith_String     (StringObject*, StringObject*);
static StringObject*    rstrip_String       (StringObject*, MemoryObject*);
static StringObject*    lstrip_String       (StringObject*, MemoryObject*);
static StringObject*    strip_String        (StringObject*, MemoryObject*);
static ListObject*      split_String        (StringObject*, char, MemoryObject*);
static ListObject*      splitstr_String     (StringObject*, StringObject*, MemoryObject*);
static StringObject*    replace_String      (StringObject*, char, char, MemoryObject*);
static StringObject*    replacestr_String   (StringObject*, StringObject*, StringObject*, MemoryObject*);
static StringObject*    join_String         (char, ListObject*, MemoryObject*);
static StringObject*    joinstr_String      (StringObject*, ListObject*, MemoryObject*);

#endif
