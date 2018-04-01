#ifndef STDC_UTIL_LIST_PRIVATE_OBJECT
#define STDC_UTIL_LIST_PRIVATE_OBJECT

#include "private.h"

Ptr         new_List        ();
void        init_List       (ListObject*);
void        del_List        (Ptr);
bool        equals_List     (ListObject*, ListObject*);

#endif
