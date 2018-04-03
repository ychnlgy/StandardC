#ifndef STDC_FILESYS_OS_PRIVATE
#define STDC_FILESYS_OS_PRIVATE

#ifdef _WIN32
    #include <direct.h>
    #define getcwd _getcwd
#else
    #include <unistd.h>
#endif

#include "stdc/lib.h"

#define BUFSIZE 1024

#include "cwd.h"

#include "cwd.c"

#endif
