#ifndef STDC_UTIL_STRING_PRIVATE_OBJECT
#define STDC_UTIL_STRING_PRIVATE_OBJECT

#include "private.h"

Ptr  new_String    ();
void del_String    (Ptr);
void init_String   (StringObject*);
bool equals_String (StringObject*, StringObject*);

#endif
