#ifndef STDC_FILESYS_OS_PRIVATE
#define STDC_FILESYS_OS_PRIVATE

#include <sys/stat.h>

#ifdef _WIN32
    #include <direct.h>
    #define getcwd _getcwd
#else
    #include <unistd.h>
#endif

#include "stdc/lib.h"

#define BUFSIZE 1024

#include "cwd.h"
#include "path.h"

#include "cwd.c"
#include "path.c"

#endif
