#ifndef STDC_UTIL_STRING_STRING_PROTECTED
#define STDC_UTIL_STRING_STRING_PROTECTED

#include "stdc/lib.h"

void        del_String      (Ptr);
void        init_String     (String*);

void        set_String      (String*, CStr);
String*     copy_String     (String*);
bool        equals_String   (String*, String*);
long        size_String     (String*);
CStr        cstr_String     (String*);
String*     format_String   (String*, ...);

static StringVtable STRING_VTABLE = {
    .set        = &set_String,
    .copy       = &copy_String,
    .equals     = &equals_String,
    .size       = &size_String,
    .cstr       = &cstr_String,
    .format     = &format_String
};

#endif
