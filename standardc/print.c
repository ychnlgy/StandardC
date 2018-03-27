#include "print.h"

#include <stdio.h>
// vprintf

#include <stdarg.h>
// va_list, va_start, va_end

CStr ENDC = "\033[0m";
CStr BOLD = "\033[1m";
CStr RED = "\033[91m";
CStr GREEN = "\033[92m";
CStr BLUE = "\033[94m";
CStr PURPLE = "\033[95m";

void printColor(CStr col, CStr msg, va_list args) {
    printf("%s", col);
    vprintf(msg, args);
    printf("%s", ENDC);
}

void boldify(CStr col, CStr msg, va_list args) {
    printf("%s", BOLD);
    printColor(col, msg, args);
    printf("%s", ENDC);
}

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
