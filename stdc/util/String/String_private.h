#ifndef STDC_UTIL_STRING_STRING_PRIVATE
#define STDC_UTIL_STRING_STRING_PRIVATE

#include "stdc/lib.h"

Ptr             new_String      ();
void            del_String      (Ptr);
void            init_String     (StringObject*);

void            set_String      (StringObject*, CStr);
StringObject*   copy_String     (StringObject*);
bool            equals_String   (StringObject*, StringObject*);
long            size_String     (StringObject*);
CStr            cstr_String     (StringObject*);
StringObject*   format_String   (StringObject*, ...);

StringVtable String = {

    // Construction/destruction
    .new        = &new_String,
    .init       = &init_String,
    .del        = &del_String,

    // Methods
    .set        = &set_String,
    .copy       = &copy_String,
    .equals     = &equals_String,
    .size       = &size_String,
    .cstr       = &cstr_String,
    .format     = &format_String

};

#endif
