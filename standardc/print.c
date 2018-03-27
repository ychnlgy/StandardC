#include "print.h"

#include <stdio.h>
// printf

CStr ENDC = "\033[0m";
CStr BOLD = "\033[1m";
CStr RED = "\033[91m";
CStr GREEN = "\033[92m";
CStr BLUE = "\033[94m";
CStr PURPLE = "\033[95m";

void printColor(CStr col, CStr msg) {
    printf("%s%s%s", col, msg, ENDC);
}

void printRed(CStr msg) {
    printColor(RED, msg);
}

void printGreen(CStr msg) {
    printColor(GREEN, msg);
}

void printBold(CStr msg) {
    printColor(BOLD, msg);
}

void printPurple(CStr msg) {
    printColor(PURPLE, msg);
}

void printBlue(CStr msg) {
    printColor(BLUE, msg);
}
