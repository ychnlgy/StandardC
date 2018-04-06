#ifndef STDC_UTIL_STRING_PRIVATE
#define STDC_UTIL_STRING_PRIVATE

#include <stdarg.h>
// va_list

#include "String_protected.h"

// Helpers
static bool             compareCStr         (bool, bool, CStr, CStr);
static char*            copyCStr            (CStr, int);
static long             getFormattedSize    (StringObject*, va_list);
static char*            getFormattedCStr    (StringObject*, va_list, long);
static bool             isWithin            (StringObject*, long);
static long             fitWithin           (StringObject*, long);
static bool             match               (StringObject*, StringObject*, long);
static bool             matchChar           (StringObject*, StringObject*, long);
static bool             isWhiteSpace        (char);
static long             countWhiteSpace     (StringObject*, long, long);
static char*            getCStrFromList     (ListObject*, char*, long, long);
static long             getStringSizeOfList (ListObject*, long);
static StringObject*    join                (char*, long, ListObject*, MemoryObject*);
static ListObject*      split               (StringObject*, Ptr, long, bool (*)(StringObject*, StringObject*, long), MemoryObject*);
static long             calculateHash       (StringObject*);

// Object
static Ptr              new_String          ();
static void             del_String          (Ptr);
static void             init_String         (StringObject*);

static bool             equals_String       (StringObject*, StringObject*);
static CStr             cstr_String         (StringObject*);
static StringObject*    copy_String         (StringObject*, MemoryObject*);

// Hashable
static long             hash_String         (StringObject*);

// Numeric
static StringObject*    add_String          (StringObject*, StringObject*, MemoryObject*);

// String
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
static StringObject*    merge_String        (ListObject*, MemoryObject*);
static void             toupper_String      (StringObject*);

// Container
static long             size_String         (StringObject*);
static bool             contains_String     (StringObject*, StringObject*);

// Accessor
static void             set_String      (StringObject*, CStr);
static char*            getitem_String  (StringObject*, long);
static char*            at_String       (StringObject*, long);
static StringObject*    slice_String    (StringObject*, long, long, MemoryObject*);
static long             index_String    (StringObject*, StringObject*);

#endif
