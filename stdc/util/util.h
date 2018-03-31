#ifndef STDC_UTIL_UTIL
#define STDC_UTIL_UTIL

#define MAX(a, b) \
    (a > b? a : b)

#define MIN(a, b) \
    (a < b? a : b)

#define LEN(arr) \
    (sizeof(arr)/sizeof(arr[0]))

#define MOD(a, b) \
    (((a % b) + b) % b)

#endif
