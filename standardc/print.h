#ifndef STANDARDC_PRINT
#define STANDARDC_PRINT

typedef const char* CStr;

extern CStr ENDC;
extern CStr BOLD;
extern CStr RED;
extern CStr GREEN;
extern CStr BLUE;
extern CStr PURPLE;

void printRed(CStr, ...);
void printGreen(CStr, ...);
void printBold(CStr, ...);
void printBlue(CStr, ...);
void printPurple(CStr, ...);

#endif
