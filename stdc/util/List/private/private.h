#ifndef STDC_UTIL_LIST_PRIVATE
#define STDC_UTIL_LIST_PRIVATE

#define MIN_CAPACITY 10
#define RESIZE_FACTOR 2
#define PTR_SIZE sizeof(Ptr)

#include "stdc/lib.h"
#include "../protected.h"
#include "helpers.h"
#include "Object.h"
#include "Container.h"
#include "Accessor.h"
#include "Stack.h"
#include "List.h"

#include "helpers.c"
#include "Object.c"
#include "Container.c"
#include "Accessor.c"
#include "Stack.c"
#include "List.c"

#endif
