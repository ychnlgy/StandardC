#ifndef STDC_MEMORY_GC_GC
#define STDC_MEMORY_GC_GC

#include "stdc/lib.h"

Ptr new(size_t, Destructor);
int incref(Ptr);
int decref(Ptr);

#endif
