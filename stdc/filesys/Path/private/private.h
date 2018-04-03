#ifndef STDC_FILESYS_PATH_PRIVATE
#define STDC_FILESYS_PATH_PRIVATE

static char PATH_SEP = '/';
static char BAD_SEP = '\\';
static const char* SKIP_PATH = ".";
static const char* BACK_PATH = "..";

#include "stdc/lib.h"
#include "../protected.h"

#include "helpers.h"
#include "Object.h"
#include "Numeric.h"
#include "Path.h"

#include "helpers.c"
#include "Object.c"
#include "Numeric.c"
#include "Path.c"

#endif
