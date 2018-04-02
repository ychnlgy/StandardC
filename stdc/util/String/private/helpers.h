#ifdef STDC_UTIL_STRING_PRIVATE

#include <stdarg.h>
// va_list

static char* copyCStr           (CStr, int);
static long  getFormattedSize   (StringObject*, va_list);
static char* getFormattedCStr   (StringObject*, va_list, long);
static bool  isWithin           (StringObject*, long);
static long  fitWithin          (StringObject*, long);
static bool  match              (StringObject*, StringObject*, long);
static bool  matchChar          (StringObject*, StringObject*, long);
static bool  isWhiteSpace       (char);
static long  countWhiteSpace    (StringObject*, long, long);
static char* getCStrFromList    (ListObject*, char*, long, long);
static long  getStringSizeOfList(ListObject*, long);
static StringObject* join(char*, long, ListObject*, MemoryObject*);

static ListObject* split(
    StringObject*, 
    Ptr, 
    long, 
    bool (*)(StringObject*, StringObject*, long),
    MemoryObject*
);

#endif
