#ifndef STANDARDC_REFLIST
#define STANDARDC_REFLIST

#include "List.h"

void* new_RefList();

typedef struct RefList {
    List super;
} RefList;

#endif
