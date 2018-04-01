#ifndef STDC_UNITTEST_PRIVATE
#define STDC_UNITTEST_PRIVATE

struct _TestSuite {
    int failedExitCode;
    int failed;
    int total;

    int maxlines;
    char* linesCovered;
};

struct _TestCase {
    _TestSuite* suite;
    int failed;
    int total;
};

#include "unittest.c"

#endif
