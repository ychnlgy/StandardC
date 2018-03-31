#include "print.h"

#include <stdio.h>
// vprintf

#include <stdarg.h>
// va_list, va_start, va_end

CStr _ENDC = "\033[0m";
CStr _BOLD = "\033[1m";
CStr _RED = "\033[91m";
CStr _GREEN = "\033[92m";
CStr _BLUE = "\033[94m";
CStr _PURPLE = "\033[95m";

void printColor(CStr col, CStr msg, va_list args) {
    printf("%s", col);
    vprintf(msg, args);
    printf("%s", _ENDC);
}

void boldify(CStr col, CStr msg, va_list args) {
    printf("%s", _BOLD);
    printColor(col, msg, args);
    printf("%s", _ENDC);
}

void printRed(CStr msg, ...) {
    va_list args;
    va_start(args, msg);
    boldify(_RED, msg, args);
    va_end(args);
}

void printGreen(CStr msg, ...) {
    va_list args;
    va_start(args, msg);
    boldify(_GREEN, msg, args);
    va_end(args);
}

void printBold(CStr msg, ...) {
    va_list args;
    va_start(args, msg);
    printColor(_BOLD, msg, args);
    va_end(args);
}

void printPurple(CStr msg, ...) {
    va_list args;
    va_start(args, msg);
    boldify(_PURPLE, msg, args);
    va_end(args);
}

void printBlue(CStr msg, ...) {
    va_list args;
    va_start(args, msg);
    boldify(_BLUE, msg, args);
    va_end(args);
}
