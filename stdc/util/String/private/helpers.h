#ifdef STDC_UTIL_STRING_PRIVATE

#include <stdarg.h>
// va_list

static char* copyCStr(CStr, int);
static long  getFormattedSize(StringObject*, va_list);
static char* getFormattedCStr(StringObject*, va_list, long);

#endif
