#ifndef STANDARD_STRING
#define STANDARD_STRING

#include <stddef.h> 
// size_t

typedef const char* CStr;

typedef struct String String;

// === METHODS ===

String* new_String(CStr);
String* copy_String(String*);
int equals_String(String*, String*);
size_t len_String(String*);

#endif
