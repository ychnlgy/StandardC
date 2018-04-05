#ifndef STDC_FILESYS_FILE_PROTECTED
#define STDC_FILESYS_FILE_PROTECTED

#include "stdc/lib.h"

struct FileObject {
    PathObject* path;
    ListObject* list;
};

#endif
