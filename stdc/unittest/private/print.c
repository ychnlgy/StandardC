#ifdef STDC_UNITTEST_PRINT_PRIVATE

#include <stdio.h>
// vprintf

static CStr ENDC = "\033[0m";
static CStr BOLD = "\033[1m";
static CStr RED = "\033[91m";
static CStr GREEN = "\033[92m";
static CStr BLUE = "\033[94m";
static CStr PURPLE = "\033[95m";

static void printColor(CStr col, CStr msg, va_list args) {
    printf("%s", col);
    vprintf(msg, args);
    printf("%s", ENDC);
}

static void boldify(CStr col, CStr msg, va_list args) {
    printf("%s", BOLD);
    printColor(col, msg, args);
    printf("%s", ENDC);
}

#endif
