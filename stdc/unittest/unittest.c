#include <stdlib.h>
// malloc

#include "print.h"
#include "unittest.h"
#include "private/unittest.h"

// === PUBLIC ===

_TestSuite* _initTestSuite(CStr fname, int failedExitCode, int maxlines) {
    reportFile(fname);
    _TestSuite* out = malloc(sizeof(_TestSuite));
    out->failed = 0;
    out->total = 0;
    out->failedExitCode = failedExitCode;

    out->maxlines = maxlines;
    out->linesCovered = malloc(sizeof(char)*maxlines);
    initLinesCovered(out);

    return out;
}

int _free_testSuite(_TestSuite* suite) {
    int exitcode;
    if (suite->failed > 0) {
        reportFailSuite(suite);
        exitcode = suite->failedExitCode;
    } else {
        reportGoodSuite(suite);
        exitcode = 0;
    }
    free(suite->linesCovered);
    free(suite);
    return exitcode;
}

_TestCase* _initTestCase(_TestSuite* suite, CStr casename) {
    reportCase(casename);
    _TestCase* testcase = malloc(sizeof(_TestCase));
    testcase->suite = suite;
    testcase->failed = 0;
    testcase->total = 0;
    return testcase;
}

void _free_testCase(_TestCase* testcase) {
    if (testcase->failed > 0) {
        reportFailCase(testcase);
    } else {
        reportGoodCase(testcase);
    }
    free(testcase);
}

void _expect(_TestCase* testcase, int boolean, CStr expr, int line) {
    updateTotal(testcase);
    if (!boolean) {
        reportFailAssert(testcase, expr, line);
        updateFail(testcase);
    }
}
