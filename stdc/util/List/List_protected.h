#ifndef STDC_UTIL_LIST_LIST_PROTECTED
#define STDC_UTIL_LIST_LIST_PROTECTED

#include "stdc/lib.h"

struct ListObject {
    long size;
    long capacity;
    Ptr* data;
};

#endif
