#include "print.h"
#include "unittest.h"

#include <stdio.h>
// printf

#include <stdlib.h>
// malloc

#include <assert.h>

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

// === PRIVATE ===

void reportFile(CStr fname) {
    printBold("[*] << %s:\n", fname);
}

void reportFailSuite(_TestSuite* suite) {
    printRed(
        "[!] >> %d/%d assertions failed.\n",
        suite->failed, 
        suite->total
    );
}

void reportGoodSuite(_TestSuite* suite) {
    printGreen(
        "[!] >> All %d assertions passed.\n",
        suite->total
    );
}

void reportCase(CStr casename) {
    printBold("\t+");
    printf(" %s:", casename);
}

void reportFailCase(_TestCase* testcase) {
    printRed(
        "\n\t\t[!] >> %d/%d failed.\n",
        testcase->failed,
        testcase->total
    );
}

void reportGoodCase(_TestCase* testcase) {
    printGreen(
        " %d passed.\n",
        testcase->total
    );
}

int lineAlreadyCovered(_TestCase* testcase, int line) {
    assert(line < testcase->suite->maxlines);
    return testcase->suite->linesCovered[line];
}

void markCoveredLine(_TestCase* testcase, int line) {
    assert(line < testcase->suite->maxlines);
    testcase->suite->linesCovered[line] = 1;
}

void reportFailAssert(_TestCase* testcase, CStr expr, int line) {
    if (!lineAlreadyCovered(testcase, line)) {
        printRed(
            "\n\t\tLine %d: %s",
            line,
            expr
        );
        markCoveredLine(testcase, line);
    }
}

void updateTotal(_TestCase* testcase) {
    testcase->total++;
    testcase->suite->total++;
}

void updateFail(_TestCase* testcase) {
    testcase->failed++;
    testcase->suite->failed++;
}

void initLinesCovered(_TestSuite* suite) {
    int i;
    for (i=0; i<suite->maxlines; i++)
        suite->linesCovered[i] = 0;
}

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
