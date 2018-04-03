#ifndef STDC_FILESYS_OS_PRIVATE
#define STDC_FILESYS_OS_PRIVATE

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#ifdef _WIN32
    #include <direct.h>
    #define getcwd _getcwd
#else
    #include <unistd.h>
#endif

#include "stdc/lib.h"

static int BUFSIZE = 1024;
static CStr SKIP_PATH = ".";
static CStr BACK_PATH = "..";

#include "cwd.h"
#include "path.h"
#include "listdir.h"
#include "chmod.h"

#include "cwd.c"
#include "path.c"
#include "listdir.c"
#include "chmod.c"

#endif
