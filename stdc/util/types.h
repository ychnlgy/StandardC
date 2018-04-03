#ifndef STDC_UTIL_TYPES
#define STDC_UTIL_TYPES

typedef void* Ptr;
typedef const char* CStr;

typedef int bool;
#define true 1
#define false 0

// Function types
typedef void    (*Destructor)   (Ptr);
typedef Ptr     (*Maker)        ();
typedef bool    (*FilterFunc)   (Ptr);

#endif
