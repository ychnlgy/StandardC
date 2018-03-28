#include "String.h"

#include <stdlib.h> 
// malloc, free

#include <string.h>
// strlen, strncpy, strcmp

#include "gc.h"

// === SIGNATURES ===

String* copy_String(String*);
int equals_String(String*, String*);
int len_String(String*);
void init_String(String*, CStr);

struct StringFields {
    int inited;
    int len;
    char* cstr;
};

// === CONCRETE ===

void del_String(void* ptr) {
    String* this = ptr;
    if (this->fields->inited)
        free(this->fields->cstr);
    free(this->fields);
}

void* new_String() {
    String* this = new(sizeof(String), &del_String);
    this->fields = malloc(sizeof(StringFields));
    this->fields->inited = 0;
    
    this->init      = &init_String;
    this->copy      = &copy_String;
    this->equals    = &equals_String;
    this->len       = &len_String;
    return this;
}

void checkInited(String* this) {
    if (this->fields->inited)
        free(this->fields->cstr);
    this->fields->inited = 1;
}

char* copy_Cstr(const char* src, int len) {
    char* cstrPtr = malloc(sizeof(char)*(len+1));
    strncpy(cstrPtr, src, len);
    cstrPtr[len] = '\0';
    return cstrPtr;
}

void init_String(String* this, CStr cstr) {
    checkInited(this);
    this->fields->len = strlen(cstr);
    this->fields->cstr = copy_Cstr(cstr, this->fields->len);
}

String* copy_String(String* this) {
    String* copy = new_String();
    copy->fields->inited = 1;
    copy->fields->len = this->fields->len;
    copy->fields->cstr = copy_Cstr(this->fields->cstr, this->fields->len);
    return copy;
}

bool equals_String(String* this, String* other) {
    return strcmp(this->fields->cstr, other->fields->cstr) == 0;
}

int len_String(String* this) {
    return this->fields->len;
}

