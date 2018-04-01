#include <stdarg.h>
// va_list, va_start, va_end

#include "print.h"
#include "private/print.h"

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
