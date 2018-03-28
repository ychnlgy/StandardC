#ifndef STANDARD_STRING
#define STANDARD_STRING

typedef const char* CStr;

typedef struct String String;
typedef struct StringFields StringFields;

void* new_String();

struct String {
    StringFields* fields;
    
    void        (*init)     (String*, CStr);
    String*     (*copy)     (String*);
    int         (*equals)   (String*, String*);
    int         (*len)      (String*);
};

#endif
