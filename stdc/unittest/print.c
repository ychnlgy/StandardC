#include <stdarg.h>
// va_list, va_start, va_end

#include "print.h"

#include <stdio.h>
// vprintf

// Helpers

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

// Implementation

void printRed(CStr msg, ...) {
    va_list args;
    va_start(args, msg);
    boldify(RED, msg, args);
    va_end(args);
}

void printGreen(CStr msg, ...) {
    va_list args;
    va_start(args, msg);
    boldify(GREEN, msg, args);
    va_end(args);
}

void printBold(CStr msg, ...) {
    va_list args;
    va_start(args, msg);
    printColor(BOLD, msg, args);
    va_end(args);
}

void printPurple(CStr msg, ...) {
    va_list args;
    va_start(args, msg);
    boldify(PURPLE, msg, args);
    va_end(args);
}

void printBlue(CStr msg, ...) {
    va_list args;
    va_start(args, msg);
    boldify(BLUE, msg, args);
    va_end(args);
}
