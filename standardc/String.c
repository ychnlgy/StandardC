#include "String.h"
#include "String_protected.h"

#include <stdlib.h> 
// malloc, free

#include <string.h>
// strlen, strncpy, strcmp

#include "gc.h"

// === CONCRETE ===

void del_String(void* ptr) {
    String* this = ptr;
    free(this->fields->cstr);
    free(this->fields);
}

void* new_String() {
    String* this = new(sizeof(String), &del_String);
    this->fields = malloc(sizeof(StringFields));
    
    this->init      = &init_String;
    this->copy      = &copy_String;
    this->equals    = &equals_String;
    this->len       = &len_String;
    
    this->fields->cstr = NULL;
    return this;
}

char* copy_Cstr(const char* src, int len) {
    char* cstrPtr = malloc(sizeof(char)*(len+1));
    strncpy(cstrPtr, src, len);
    cstrPtr[len] = '\0';
    return cstrPtr;
}

void init_String(void* _this, CStr cstr) {
    String* this = _this;
    free(this->fields->cstr);
    this->fields->len = strlen(cstr);
    this->fields->cstr = copy_Cstr(cstr, this->fields->len);
}

String* copy_String(void* _this) {
    String* this = _this;
    String* copy = new_String();
    copy->fields->len = this->fields->len;
    copy->fields->cstr = copy_Cstr(this->fields->cstr, this->fields->len);
    return copy;
}

bool equals_String(void* this, void* other) {
    
    return strcmp(
        ((String*) this)->fields->cstr, 
        ((String*) other)->fields->cstr
    ) == 0;
}

int len_String(void* this) {
    return ((String*) this)->fields->len;
}

