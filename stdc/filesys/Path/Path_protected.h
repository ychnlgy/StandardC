#ifndef STDC_FILESYS_PATH_PROTECTED
#define STDC_FILESYS_PATH_PROTECTED

#include "stdc/lib.h"

struct PathObject {
    bool isAbs;
    StringObject* name;
    ListObject* list;
};

#endif
