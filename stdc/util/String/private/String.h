#ifndef STDC_UTIL_STRING_PRIVATE_STRING
#define STDC_UTIL_STRING_PRIVATE_STRING

#include "private.h"

void            set_String      (StringObject*, CStr);
StringObject*   copy_String     (StringObject*);
long            size_String     (StringObject*);
CStr            cstr_String     (StringObject*);
StringObject*   format_String   (StringObject*, ...);

#endif
