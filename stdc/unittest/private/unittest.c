#ifdef STDC_UNITTEST_PRIVATE

#include <assert.h>

#include <stdio.h>
// printf

static void reportFile(CStr fname) {
    printBold("[*] << %s:\n", fname);
}

static void reportFailSuite(_TestSuite* suite) {
    printRed(
        "[!] >> %d/%d assertions failed.\n",
        suite->failed, 
        suite->total
    );
}

static void reportGoodSuite(_TestSuite* suite) {
    printGreen(
        "[!] >> All %d assertions passed.\n",
        suite->total
    );
}

static void reportCase(CStr casename) {
    printBold("\t+");
    printf(" %s:", casename);
}

static void reportFailCase(_TestCase* testcase) {
    printRed(
        "\n\t\t[!] >> %d/%d failed.\n",
        testcase->failed,
        testcase->total
    );
}

static void reportGoodCase(_TestCase* testcase) {
    printGreen(
        " %d passed.\n",
        testcase->total
    );
}

static int lineAlreadyCovered(_TestCase* testcase, int line) {
    assert(line < testcase->suite->maxlines);
    return testcase->suite->linesCovered[line];
}

static void markCoveredLine(_TestCase* testcase, int line) {
    assert(line < testcase->suite->maxlines);
    testcase->suite->linesCovered[line] = 1;
}

static void reportFailAssert(_TestCase* testcase, CStr expr, int line) {
    if (!lineAlreadyCovered(testcase, line)) {
        printRed(
            "\n\t\tLine %d: %s",
            line,
            expr
        );
        markCoveredLine(testcase, line);
    }
}

static void updateTotal(_TestCase* testcase) {
    testcase->total++;
    testcase->suite->total++;
}

static void updateFail(_TestCase* testcase) {
    testcase->failed++;
    testcase->suite->failed++;
}

static void initLinesCovered(_TestSuite* suite) {
    int i;
    for (i=0; i<suite->maxlines; i++)
        suite->linesCovered[i] = 0;
}

#endif
