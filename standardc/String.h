#ifndef STANDARDC_STRING
#define STANDARDC_STRING

#include "bool.h"

typedef const char* CStr;

typedef struct String String;
typedef struct StringFields StringFields;

void* new_String();

struct String {
    StringFields* fields;
    
    void        (*init)     (String*, CStr);
    String*     (*copy)     (String*);
    bool        (*equals)   (String*, String*);
    int         (*len)      (String*);
};

#endif
