#include "String.h"

#include <stdlib.h> 
// malloc, free

#include <string.h>
// strlen, strncpy

#include "gc.h"

struct String {
    size_t len;
    char* cstr;
};

char* copy_Cstr(const char* src, size_t len) {
    char* cstrPtr = malloc(sizeof(char)*(len+1));
    strncpy(cstrPtr, src, len);
    cstrPtr[len] = '\0';
    return cstrPtr;
}

void del_String(void* ptr) {
    free(((String*) ptr)->cstr);
}

String* new_String(CStr cstr) {
    String* s = new(sizeof(String), &del_String);
    s->len = strlen(cstr);
    s->cstr = copy_Cstr(cstr, s->len);
    return s;
}

String* copy_String(String* s) {
    String* copy = new(sizeof(String), &del_String);
    copy->len = s->len;
    copy->cstr = copy_Cstr(s->cstr, s->len);
    return copy;
}

int equals_String(String* s1, String* s2) {
    return strcmp(s1->cstr, s2->cstr) == 0;
}

size_t len_String(String* s) {
    return s->len;
}

