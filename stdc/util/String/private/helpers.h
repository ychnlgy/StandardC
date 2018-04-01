#ifndef STDC_UTIL_STRING_PRIVATE_HELPERS
#define STDC_UTIL_STRING_PRIVATE_HELPERS

#include <stdarg.h>
// va_list

#include "private.h"

char* _String_copyCStr(CStr, int);
long  _String_getFormattedSize(StringObject*, va_list);
char* _String_getFormattedCStr(StringObject*, va_list, long);

#endif
