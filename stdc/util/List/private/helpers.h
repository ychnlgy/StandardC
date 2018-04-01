#ifndef STDC_UTIL_LIST_PRIVATE_HELPERS
#define STDC_UTIL_LIST_PRIVATE_HELPERS

#include "private.h"

void _List_resize   (ListObject*, size_t);
bool _List_isWithin (ListObject*, long);
long _List_fitWithin(ListObject*, long);

#endif
