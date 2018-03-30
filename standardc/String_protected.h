#ifndef STANDARDC_STRING_PROTECTED
#define STANDARDC_STRING_PROTECTED

#include "String.h"

String* copy_String(void*);
int equals_String(void*, void*);
int len_String(void*);
void init_String(void*, CStr);

struct StringFields {
    int len;
    char* cstr;
};

#endif
